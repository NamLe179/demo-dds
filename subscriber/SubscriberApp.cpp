#include "SubscriberApp.h"
#include <QDebug>
#include <chrono>
#include <algorithm>

// ─────────────────────────────────────────────────────────────────────────────
// Cơ chế nhận dữ liệu:
//   - on_data_available gọi processDataAvailable() trong Connext thread
//   - take() với MAX_TAKE_SAMPLES=4096: có thể lấy nhiều hơn 1 batch/lần
//     nếu callback bị trễ (tránh accumulate)
//   - Sau mỗi take(), return_loan tránh giữ bộ nhớ Connext
//   - Frame reconstruction: dùng frame_id để detect drop và tính latency
//
// Về latency measurement:
//   - timestamp_ns trong sample = thời điểm publisher set (trước khi write)
//   - nowNs() trong on_data_available = thời điểm nhận được (sau unbatch+deliver)
//   - Latency = nowNs() - sample.timestamp_ns = end-to-end application latency
//     (bao gồm cả thời gian batch flush, network, deserialization)

// ReaderListener 

void ReaderListener::on_data_available(DDSDataReader* reader)
{
    owner_->stats.cb_count.fetch_add(1, std::memory_order_relaxed);
    owner_->processDataAvailable(reader);
}

void ReaderListener::on_subscription_matched(
    DDSDataReader*,
    const DDS_SubscriptionMatchedStatus& status)
{
    qInfo() << "[Subscriber] Publisher matched. current_count:" << status.current_count;
}

void ReaderListener::on_requested_deadline_missed(
    DDSDataReader*,
    const DDS_RequestedDeadlineMissedStatus& status)
{
    qWarning() << "[Subscriber] Deadline missed. total:" << status.total_count;
}

void ReaderListener::on_sample_rejected(
    DDSDataReader*,
    const DDS_SampleRejectedStatus& status)
{
    const int32_t delta = std::max<int32_t>(0, status.total_count_change);
    if (delta > 0) {
        owner_->stats.samples_rejected.fetch_add(
            static_cast<uint64_t>(delta), std::memory_order_relaxed);
    }
    qWarning() << "[Subscriber] Sample rejected. reason="
               << static_cast<int>(status.last_reason)
               << " total=" << status.total_count;
}

void ReaderListener::on_liveliness_changed(
    DDSDataReader*,
    const DDS_LivelinessChangedStatus& status)
{
    qInfo() << "[Subscriber] Liveliness changed. alive_count:" << status.alive_count;
}

// SubscriberApp 

SubscriberApp::SubscriberApp(QObject* parent)
    : QObject(parent)
    , listener_(this)
{}

SubscriberApp::~SubscriberApp()
{
    if (participant_) {
        participant_->delete_contained_entities();
        DDSDomainParticipantFactory::get_instance()
            ->delete_participant(participant_);
        participant_ = nullptr;
    }
    DDSDomainParticipantFactory::finalize_instance();
}

bool SubscriberApp::init(int domain_id)
{
    if (!setupParticipant(domain_id)) return false;
    if (!setupTopic())               return false;
    if (!setupSubscriber())          return false;
    if (!setupReader())              return false;

    stats_timer_ = new QTimer(this);
    stats_timer_->setInterval(1000);
    connect(stats_timer_, &QTimer::timeout, this, &SubscriberApp::onStatsTimer);

    qInfo() << "[Subscriber] Initialized. Domain:" << domain_id;
    return true;
}

void SubscriberApp::start()
{
    stats_timer_->start();
    qInfo() << "[Subscriber] Listening for ObjectState samples...";
}

bool SubscriberApp::setupParticipant(int domain_id)
{
    DDS_DomainParticipantQos pqos;
    DDSDomainParticipantFactory::get_instance()
        ->get_default_participant_qos(pqos);

    pqos.participant_name.name = DDS_String_dup("HighFreqPublisher");

    participant_ = DDSDomainParticipantFactory::get_instance()
                       ->create_participant(
                           domain_id,
                           pqos,
                           nullptr,
                           DDS_STATUS_MASK_NONE);

    if (!participant_) {
        qCritical() << "[Subscriber] Không tạo được DomainParticipant";
        return false;
    }
    return true;
}

bool SubscriberApp::setupTopic()
{
    DDS_ReturnCode_t rc =
        ObjectStateMsg::ObjectStateTypeSupport::register_type(
            participant_,
            ObjectStateMsg::ObjectStateTypeSupport::get_type_name());

    if (rc != DDS_RETCODE_OK) {
        qCritical() << "[Subscriber] Không đăng ký được type. rc=" << rc;
        return false;
    }

    // Tên topic phải khớp với publisher
    topic_ = participant_->create_topic(
        "ObjectStateTopic",
        ObjectStateMsg::ObjectStateTypeSupport::get_type_name(),
        DDS_TOPIC_QOS_DEFAULT,
        nullptr,
        DDS_STATUS_MASK_NONE);

    if (!topic_) {
        qCritical() << "[Subscriber] Không tạo được Topic";
        return false;
    }
    return true;
}

bool SubscriberApp::setupSubscriber()
{
    subscriber_ = participant_->create_subscriber(
        DDS_SUBSCRIBER_QOS_DEFAULT,
        nullptr,
        DDS_STATUS_MASK_NONE);

    if (!subscriber_) {
        qCritical() << "[Subscriber] Không tạo được Subscriber";
        return false;
    }
    return true;
}

bool SubscriberApp::setupReader()
{
    DDS_DataReaderQos rqos;
    subscriber_->get_default_datareader_qos(rqos);

    // Phải khớp với publisher
    rqos.reliability.kind = DDS_BEST_EFFORT_RELIABILITY_QOS;

    // object_id là @key, mỗi object_id là 1 DDS instance riêng biệt.
    // KEEP_LAST(1) chỉ giữ trạng thái mới nhất của mỗi object
    rqos.history.kind  = DDS_KEEP_LAST_HISTORY_QOS;
    rqos.history.depth = 1;

    rqos.resource_limits.max_samples              = NUM_OBJECTS; //cho phép tồn tại đồng thời 2000 instances
    rqos.resource_limits.max_instances            = NUM_OBJECTS;
    rqos.resource_limits.max_samples_per_instance = 1;

    // Deadline 33ms x 3
    rqos.deadline.period.sec     = 0;
    rqos.deadline.period.nanosec = 100 * 1000000u;

    DDSDataReader* base_reader = subscriber_->create_datareader(
        topic_,
        rqos,
        &listener_,
        DDS_DATA_AVAILABLE_STATUS
            | DDS_SUBSCRIPTION_MATCHED_STATUS
            | DDS_REQUESTED_DEADLINE_MISSED_STATUS
            | DDS_SAMPLE_REJECTED_STATUS
            | DDS_LIVELINESS_CHANGED_STATUS);

    if (!base_reader) {
        qCritical() << "[Subscriber] Không tạo được DataReader";
        return false;
    }

    reader_ = ObjectStateMsg::ObjectStateDataReader::narrow(base_reader);
    if (!reader_) {
        qCritical() << "[Subscriber] narrow() thất bại";
        return false;
    }

    qInfo() << "[Subscriber] DataReader: BEST_EFFORT | KEEP_LAST(1) per instance | max_instances=" << NUM_OBJECTS;
    return true;
}

// processDataAvailable — gọi từ Connext internal receive thread
//
// Dùng loan-based take() để tránh copy:
//   - ObjectStateSeq và DDS_SampleInfoSeq được Connext quản lý bộ nhớ
//   - Sau khi xử lý, return_loan() để giải phóng
void SubscriberApp::processDataAvailable(DDSDataReader* base_reader)
{
    const int64_t recv_ns = nowNs();

    ObjectStateMsg::ObjectStateDataReader* typed_reader =
        ObjectStateMsg::ObjectStateDataReader::narrow(base_reader);
    if (!typed_reader) return;

    // Loan-based sequence — zero-copy read
    ObjectStateMsg::ObjectStateSeq data_seq;
    DDS_SampleInfoSeq              info_seq;

    DDS_ReturnCode_t rc = typed_reader->take(
        data_seq,
        info_seq,
        MAX_TAKE_SAMPLES,
        DDS_ANY_SAMPLE_STATE,
        DDS_ANY_VIEW_STATE,
        DDS_ANY_INSTANCE_STATE);

    if (rc == DDS_RETCODE_NO_DATA) {
        stats.no_data_count.fetch_add(1, std::memory_order_relaxed);
        return;
    }

    if (rc != DDS_RETCODE_OK) {
        qWarning() << "[Subscriber] take() failed. rc=" << rc;
        return;
    }

    stats.take_count.fetch_add(1, std::memory_order_relaxed);

    const int n = data_seq.length();
    stats.samples_received.fetch_add(
        static_cast<uint64_t>(n), std::memory_order_relaxed);

    // Tính latency từ tất cả sample valid trong batch
    // (tất cả sample trong 1 frame có cùng timestamp_ns)
    bool latency_updated = false;

    // Tracking bounding box
    float min_x = 1e9f, max_x = -1e9f;
    float min_y = 1e9f, max_y = -1e9f;
    uint64_t current_frame_id = 0;

    for (int i = 0; i < n; ++i) {
        if (!info_seq[i].valid_data) continue;

        const ObjectStateMsg::ObjectState& obj = data_seq[i];

        // Latency — tích lũy từ tất cả valid samples
        const int64_t latency_us = (recv_ns - obj.timestamp_ns) / 1000;
        stats.last_latency_us.store(latency_us, std::memory_order_relaxed);
        stats.total_latency_us.fetch_add(static_cast<uint64_t>(latency_us), std::memory_order_relaxed);
        stats.latency_sample_count.fetch_add(1, std::memory_order_relaxed);

        if (latency_us > stats.max_latency_us.load(std::memory_order_relaxed))
            stats.max_latency_us.store(latency_us, std::memory_order_relaxed);

        if (!latency_updated) {
            current_frame_id = obj.frame_id;
            latency_updated = true;
        }

        // Bounding box của các object active
        if (obj.status != 0) {
            if (obj.pos_x < min_x) min_x = obj.pos_x;
            if (obj.pos_x > max_x) max_x = obj.pos_x;
            if (obj.pos_y < min_y) min_y = obj.pos_y;
            if (obj.pos_y > max_y) max_y = obj.pos_y;
        }
    }
    (void)min_x; (void)max_x; (void)min_y; (void)max_y;

    // Frame-level drop detection (dùng frame_id)
    if (latency_updated) {
        const uint64_t fid      = current_frame_id;
        const uint64_t last_fid = stats.last_frame_id.load(std::memory_order_relaxed);

        if (fid != last_fid) {
            if (last_fid > 0 && fid > last_fid + 1) {
                const uint64_t lost = fid - last_fid - 1;
                stats.frames_dropped.fetch_add(lost, std::memory_order_relaxed);
                stats.drop_events.fetch_add(1, std::memory_order_relaxed);

                const int64_t last_log = last_gap_log_ns_.load(std::memory_order_relaxed);
                if (recv_ns - last_log >= GAP_LOG_INTERVAL_NS) {
                    last_gap_log_ns_.store(recv_ns, std::memory_order_relaxed);
                    qWarning().noquote()
                        << QString("[Subscriber] Frame gap. last=%1 current=%2 lost=%3")
                               .arg(last_fid)
                               .arg(fid)
                               .arg(lost);
                }
            }

            stats.last_frame_id.store(fid, std::memory_order_relaxed);
            stats.frames_received.fetch_add(1, std::memory_order_relaxed);
        }
    }

    typed_reader->return_loan(data_seq, info_seq);
}

void SubscriberApp::onStatsTimer()
{
    const uint64_t frames   = stats.frames_received.exchange(0);
    const uint64_t dropped  = stats.frames_dropped.exchange(0);
    const uint64_t samples  = stats.samples_received.exchange(0);
    const uint64_t total_lat = stats.total_latency_us.exchange(0);
    const uint64_t lat_count = stats.latency_sample_count.exchange(0);
    const int64_t  maxlat   = stats.max_latency_us.load();

    // Tính trung bình latency
    const double avg_lat = lat_count > 0 ? static_cast<double>(total_lat) / lat_count : 0.0;

    // Throughput
    const double mbps = static_cast<double>(samples)
                        * sizeof(ObjectStateMsg::ObjectState)
                        / 1024.0 / 1024.0;

    qInfo().noquote()
        << QString("[Subscriber] FPS: %1 | Samples: %2 | Dropped frames: %3 "
                   "| Latency: %4µs (avg) | MaxLat: %5µs | ~%6 MB/s")
               .arg(frames)
               .arg(samples)
               .arg(dropped)
               .arg(avg_lat, 0, 'f', 2)
               .arg(maxlat)
               .arg(mbps, 0, 'f', 2);


}

int64_t SubscriberApp::nowNs()
{
    using namespace std::chrono;
    return static_cast<int64_t>(
        duration_cast<nanoseconds>(
            high_resolution_clock::now().time_since_epoch()).count());
}