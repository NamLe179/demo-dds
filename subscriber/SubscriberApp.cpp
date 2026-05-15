#include "SubscriberApp.h"
#include <QDebug>
#include <chrono>
#include <algorithm>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;

// ReaderListener
void ReaderListener::on_data_available(DataReader* reader)
{
    const int64_t recv_ns = SubscriberApp::nowNs();

    // static: không malloc mỗi lần gọi — thread-safe vì listener của 1 reader chạy tuần tự trong 1 thread
    static ObjectStateMsg::ObjectStateBatch s_batch;
    SampleInfo info;

    // RETCODE_OK = có dữ liệu; RETCODE_NO_DATA = queue rỗng (bình thường)
    owner_->stats.cb_count.fetch_add(1, std::memory_order_relaxed);
    ReturnCode_t rc = reader->take_next_sample(&s_batch, &info);

    if (rc == RETCODE_OK && info.valid_data) {
        owner_->stats.valid_count.fetch_add(1, std::memory_order_relaxed);
        owner_->processFrame(s_batch, recv_ns);
    } else if (rc == RETCODE_NO_DATA) {
        owner_->stats.no_data_count.fetch_add(1, std::memory_order_relaxed);
    } else if (rc == RETCODE_OK) {
        owner_->stats.invalid_count.fetch_add(1, std::memory_order_relaxed);
    } else {
        owner_->stats.error_count.fetch_add(1, std::memory_order_relaxed);
    }
}

void ReaderListener::on_subscription_matched(
    DataReader*,
    const SubscriptionMatchedStatus& info)
{
    qInfo() << "[Subscriber] Publisher matched. Count:" << info.current_count;
}

void ReaderListener::on_requested_deadline_missed(
    DataReader*,
    const RequestedDeadlineMissedStatus& status)
{
    qWarning() << "[Subscriber] Deadline missed. Total:" << status.total_count;
}

void ReaderListener::on_sample_rejected(
    DataReader*,
    const SampleRejectedStatus& status)
{
    const int32_t delta = std::max<int32_t>(0, status.total_count_change);
    if (delta > 0) {
        owner_->stats.samples_rejected.fetch_add(
            static_cast<uint64_t>(delta), std::memory_order_relaxed);
    }

    qWarning() << "[Subscriber] Sample rejected. reason="
               << static_cast<int>(status.last_reason)
               << " total=" << status.total_count
               << " delta=" << status.total_count_change;
}

SubscriberApp::SubscriberApp(QObject* parent)
    : QObject(parent)
    , listener_(this)
{}

SubscriberApp::~SubscriberApp()
{
    if (subscriber_ && reader_)  subscriber_->delete_datareader(reader_);
    if (participant_ && subscriber_) participant_->delete_subscriber(subscriber_);
    if (participant_ && topic_)  participant_->delete_topic(topic_);
    if (participant_)
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
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
    qInfo() << "[Subscriber] Listening for ObjectStateBatch...";
}

bool SubscriberApp::setupParticipant(int domain_id)
{
    DomainParticipantQos pqos;
    pqos.name("HighFreqSubscriber");

    // Hiển thị monitor cho chart view
    pqos.properties().properties().emplace_back(
        "fastdds.statistics",
        "HISTORY_LATENCY_TOPIC;PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC;DATA_COUNT_TOPIC"
    );

    // UDP Transport (built-in)
    pqos.transport().use_builtin_transports = true;

    participant_ = DomainParticipantFactory::get_instance()
                       ->create_participant(domain_id, pqos);
    if (!participant_) {
        qCritical() << "[Subscriber] Không tạo được DomainParticipant";
        return false;
    }
    return true;
}

bool SubscriberApp::setupTopic()
{
    type_support_ = TypeSupport(new ObjectStateMsg::ObjectStateBatchPubSubType());
    if (type_support_.register_type(participant_) != RETCODE_OK) {
        qCritical() << "[Subscriber] Không đăng ký được type";
        return false;
    }

    topic_ = participant_->create_topic(
        "ObjectStateBatch",
        type_support_.get_type_name(),
        TOPIC_QOS_DEFAULT);

    if (!topic_) {
        qCritical() << "[Subscriber] Không tạo được Topic";
        return false;
    }
    return true;
}

bool SubscriberApp::setupSubscriber()
{
    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
    if (!subscriber_) {
        qCritical() << "[Subscriber] Không tạo được Subscriber";
        return false;
    }
    return true;
}

bool SubscriberApp::setupReader()
{
    DataReaderQos rqos;

    // Phải khớp với publisher
    rqos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

    // Chỉ giữ frame mới nhất
    rqos.history().kind  = KEEP_LAST_HISTORY_QOS;
    rqos.history().depth = 1;

    rqos.resource_limits().max_samples              = 1;
    rqos.resource_limits().max_instances            = 1;
    rqos.resource_limits().max_samples_per_instance = 1;

    // Deadline: cảnh báo nếu không nhận được sample trong 50ms
    rqos.deadline().period = Duration_t{0, 50'000'000u}; // 50ms

    reader_ = subscriber_->create_datareader(topic_, rqos, &listener_);
    if (!reader_) {
        qCritical() << "[Subscriber] Không tạo được DataReader";
        return false;
    }

    qInfo() << "[Subscriber] DataReader: BEST_EFFORT | KEEP_LAST(1)";
    return true;
}

// processFrame — gọi từ FastDDS thread mỗi ~33ms
void SubscriberApp::processFrame(
    const ObjectStateMsg::ObjectStateBatch& batch,
    int64_t recv_ns)
{
    // Latency
    const int64_t latency_us = (recv_ns - batch.timestamp_ns()) / 1000;
    total_latency_us_.fetch_add(static_cast<uint64_t>(latency_us), std::memory_order_relaxed);
    latency_sample_count_.fetch_add(1, std::memory_order_relaxed);
    if (latency_us > stats.max_latency_us.load(std::memory_order_relaxed))
        stats.max_latency_us.store(latency_us, std::memory_order_relaxed);

    // Frame drop detection
    const uint64_t fid      = batch.frame_id();
    const uint64_t last_fid = stats.last_frame_id.load(std::memory_order_relaxed);
    if (last_fid > 0 && fid > last_fid + 1) {
        const uint64_t lost = fid - last_fid - 1;
        stats.frames_dropped.fetch_add(lost, std::memory_order_relaxed);
        stats.drop_events.fetch_add(1, std::memory_order_relaxed);

        const int64_t last_log = last_gap_log_ns_.load(std::memory_order_relaxed);
        if (recv_ns - last_log >= GAP_LOG_INTERVAL_NS) {
            last_gap_log_ns_.store(recv_ns, std::memory_order_relaxed);
            qWarning().noquote()
                << QString("[Subscriber] Frame gap detected. last=%1 current=%2 lost=%3")
                       .arg(last_fid)
                       .arg(fid)
                       .arg(lost);
        }
    }
    stats.last_frame_id.store(fid, std::memory_order_relaxed);

    //  Xử lý dữ liệu: tính bounding box 
    float min_x = 1e9f, max_x = -1e9f;
    float min_y = 1e9f, max_y = -1e9f;

    const auto& objs = batch.objects();
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        if (objs[i].status() != 0) {
            const float x = objs[i].pos_x(), y = objs[i].pos_y();
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
        }
    }
    (void)min_x; (void)max_x; (void)min_y; (void)max_y;

    stats.frames_received.fetch_add(1, std::memory_order_relaxed);
    stats.objects_processed.fetch_add(static_cast<uint64_t>(NUM_OBJECTS),
                                      std::memory_order_relaxed);
}

void SubscriberApp::onStatsTimer()
{
    const uint64_t frames   = stats.frames_received.exchange(0);
    const uint64_t dropped  = stats.frames_dropped.exchange(0);  // Số frame bị drop do gap
    const uint64_t drop_evt = stats.drop_events.exchange(0);     // Số lần detect drop event
    const uint64_t rejected = stats.samples_rejected.exchange(0);
    const uint64_t objs     = stats.objects_processed.exchange(0);
    const int64_t  maxlat   = stats.max_latency_us.load();
    
    // Tính trung bình latency trong 1 giây
    const uint64_t total_lat = total_latency_us_.exchange(0);
    const uint64_t lat_count = latency_sample_count_.exchange(0);
    double avg_latency_us = (lat_count > 0) ? (double)total_lat / lat_count : 0.0;
    
    // Queue stats - clear để không tích lũy
    stats.cb_count.exchange(0);
    stats.valid_count.exchange(0);
    stats.no_data_count.exchange(0);
    stats.invalid_count.exchange(0);
    stats.error_count.exchange(0);
    stats.samples_rejected.exchange(0);

    qInfo().noquote()
        << QString("[Subscriber] FPS: %1 | Processed: %2 | FrameDrop: %3 (detected %4 times) | Rejected: %5 | Objects/s: %6 "
                   "| Latency_avg: %7µs | Latency_max: %8µs | ~%9 MB/s")
               .arg(frames)
               .arg(frames)
               .arg(dropped)      // Tổng số frame bị drop
               .arg(drop_evt)     // Số lần phát hiện drop event
               .arg(rejected)     // Số sample bị reject từ DDS
               .arg(objs)
               .arg(avg_latency_us, 0, 'f', 2)
               .arg(maxlat)
               .arg(frames * NUM_OBJECTS * sizeof(ObjectStateMsg::ObjectState)
                        / 1024.0 / 1024.0, 0, 'f', 2);
}

int64_t SubscriberApp::nowNs()
{
    using namespace std::chrono;
    return static_cast<int64_t>(
        duration_cast<nanoseconds>(
            high_resolution_clock::now().time_since_epoch()).count());
}
