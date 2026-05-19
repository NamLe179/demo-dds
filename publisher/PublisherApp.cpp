#include "PublisherApp.h"
#include <QDebug>
#include <chrono>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// PublisherApp.cpp  —  RTI Connext DDS publisher
//
// Luồng publish mỗi frame:
//   1. simulateObjects() cập nhật 2000 vị trí
//   2. for i=0..1999: writer_->write(sample_)
//      - RTI Connext DataWriter nhận từng sample vào internal batch buffer
//      - Khi buffer đạt max_samples=2000 (hoặc max_data_bytes), transport
//        tự động flush → gửi 1 hoặc vài UDP packet chứa toàn bộ batch
//   3. Không flush() thủ công — Connext tự quản lý theo QoS
// ─────────────────────────────────────────────────────────────────────────────

PublisherApp::PublisherApp(QObject* parent)
    : QObject(parent)
{}

PublisherApp::~PublisherApp()
{
    stop();

    // Cleanup theo thứ tự ngược với tạo
    if (participant_) {
        // delete_contained_entities() xóa topic, publisher, writer
        participant_->delete_contained_entities();
        DDSDomainParticipantFactory::get_instance()
            ->delete_participant(participant_);
        participant_ = nullptr;
    }

    // Finalize factory (giải phóng thread nội bộ)
    DDSDomainParticipantFactory::finalize_instance();
}

bool PublisherApp::init(int domain_id)
{
    if (!setupParticipant(domain_id)) return false;
    if (!setupTopic())               return false;
    if (!setupPublisher())           return false;
    if (!setupWriter())              return false;

    preAllocateSample();

    publish_timer_ = new QTimer(this);
    publish_timer_->setTimerType(Qt::PreciseTimer);
    publish_timer_->setInterval(PUBLISH_MS);
    connect(publish_timer_, &QTimer::timeout, this, &PublisherApp::onTimerTick);

    stats_timer_ = new QTimer(this);
    stats_timer_->setInterval(1000);
    connect(stats_timer_, &QTimer::timeout, this, &PublisherApp::onStatsTimer);

    perf_clock_.start();
    qInfo() << "[Publisher] Ready. Domain:" << domain_id
            << "| Objects:" << NUM_OBJECTS
            << "| Target:" << PUBLISH_HZ << "Hz"
            << "| Batch max_samples:" << BATCH_MAX_SAMPLES;
    return true;
}

bool PublisherApp::setupParticipant(int domain_id)
{
    // Participant QoS — lấy default rồi chỉnh transport
    DDS_DomainParticipantQos pqos;
    DDSDomainParticipantFactory::get_instance()
        ->get_default_participant_qos(pqos);

    pqos.participant_name.name = DDS_String_dup("HighFreqPublisher");

    participant_ = DDSDomainParticipantFactory::get_instance()
                       ->create_participant(
                           domain_id,
                           pqos,
                           nullptr, // listener
                           DDS_STATUS_MASK_NONE);

    if (!participant_) {
        qCritical() << "[Publisher] Không tạo được DomainParticipant";
        return false;
    }
    return true;
}

bool PublisherApp::setupTopic()
{
    // Đăng ký type — rtiddsgen sinh ObjectStateTypeSupport
    DDS_ReturnCode_t rc =
        ObjectStateMsg::ObjectStateTypeSupport::register_type(
            participant_,
            ObjectStateMsg::ObjectStateTypeSupport::get_type_name());

    if (rc != DDS_RETCODE_OK) {
        qCritical() << "[Publisher] Không đăng ký được type. rc=" << rc;
        return false;
    }

    topic_ = participant_->create_topic(
        "ObjectStateTopic",
        ObjectStateMsg::ObjectStateTypeSupport::get_type_name(),
        DDS_TOPIC_QOS_DEFAULT,
        nullptr,
        DDS_STATUS_MASK_NONE);

    if (!topic_) {
        qCritical() << "[Publisher] Không tạo được Topic";
        return false;
    }
    return true;
}

bool PublisherApp::setupPublisher()
{
    publisher_ = participant_->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT,
        nullptr,
        DDS_STATUS_MASK_NONE);

    if (!publisher_) {
        qCritical() << "[Publisher] Không tạo được Publisher";
        return false;
    }
    return true;
}

bool PublisherApp::setupWriter()
{
    // DataWriter QoS 
    DDS_DataWriterQos wqos;
    publisher_->get_default_datawriter_qos(wqos);

    // BEST_EFFORT
    wqos.reliability.kind = DDS_BEST_EFFORT_RELIABILITY_QOS;

    // KEEP_LAST depth=1
    wqos.history.kind  = DDS_KEEP_LAST_HISTORY_QOS;
    wqos.history.depth = 1;

    // Resource limits — khớp với history depth
    // object_id là @key cần 2000 instances. Writer chỉ giữ KEEP_LAST(1) mỗi instance
    // max_samples = max_instances × max_samples_per_instance = 2000 × 1.
    wqos.resource_limits.max_samples              = NUM_OBJECTS * 10; // x10 test docker window
    wqos.resource_limits.max_instances            = NUM_OBJECTS;
    wqos.resource_limits.max_samples_per_instance = 10;

    // BATCH QoS
    wqos.batch.enable         = DDS_BOOLEAN_TRUE;
    wqos.batch.max_data_bytes = BATCH_MAX_BYTES;        // 128 KB -> 60 KB test cho docker window
    wqos.batch.max_samples    = BATCH_MAX_SAMPLES;      // 2000 samples 
    wqos.batch.max_flush_delay.sec     = 0;
    wqos.batch.max_flush_delay.nanosec = 35 * 1000000u; // 35 ms

    wqos.publish_mode.kind = DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS;

    // Flow controller
    DDS_FlowControllerProperty_t fc_prop;
    participant_->get_default_flowcontroller_property((fc_prop));

    fc_prop.scheduling_policy = DDS_EDF_FLOW_CONTROLLER_SCHED_POLICY;

    fc_prop.token_bucket.max_tokens = 200 * 1024; // 200 KB
    fc_prop.token_bucket.tokens_added_per_period = 70 * 1024; //70 KB thêm vào mỗi chu kỳ
    fc_prop.token_bucket.period.sec = 0;
    fc_prop.token_bucket.period.nanosec = 11 * 1000000; // Chu kỳ fill 11 ms

    participant_->create_flowcontroller("HighFreqFlowController", fc_prop);

    wqos.publish_mode.flow_controller_name = DDS_String_dup("HighFreqFlowController");

    //  Deadline 
    // BATCH + ASYNC, deadline được tính sau khi batch được flush
    wqos.deadline.period.sec     = 0;
    wqos.deadline.period.nanosec = (PUBLISH_MS + 10) * 1000000u; // 43ms

    DDSDataWriter* base_writer = publisher_->create_datawriter(
        topic_,
        wqos,
        nullptr, // listener — xử lý qua polling trong stats
        DDS_STATUS_MASK_NONE);

    if (!base_writer) {
        qCritical() << "[Publisher] Không tạo được DataWriter";
        return false;
    }

    // Narrow xuống typed writer
    writer_ = ObjectStateMsg::ObjectStateDataWriter::narrow(base_writer);
    if (!writer_) {
        qCritical() << "[Publisher] narrow() thất bại";
        return false;
    }

    qInfo() << "[Publisher] DataWriter: BEST_EFFORT | KEEP_LAST(1) | ASYNC"
            << "| BATCH max_samples=" << BATCH_MAX_SAMPLES
            << "max_data_bytes=" << BATCH_MAX_BYTES << "B"
            << "flush_delay=35ms";
    return true;
}

// Pre-allocate sample struct — gọi 1 lần duy nhất.
// Hot path chỉ ghi đè field values, không malloc.
void PublisherApp::preAllocateSample()
{
    // Zero-init tất cả fields
    sample_ = ObjectStateMsg::ObjectState{};
    sample_.status = 1;
    qInfo() << "[Publisher] Pre-allocated ObjectState sample — hot path malloc-free";
}

void PublisherApp::start()
{
    publish_timer_->start();
    stats_timer_->start();
    qInfo() << "[Publisher] Bắt đầu publish" << PUBLISH_HZ << "Hz";
}

void PublisherApp::stop()
{
    if (publish_timer_) publish_timer_->stop();
    if (stats_timer_)   stats_timer_->stop();
}

// ─────────────────────────────────────────────────────────────────────────────
// Hot path — gọi mỗi 33ms bởi Qt timer
// ─────────────────────────────────────────────────────────────────────────────
void PublisherApp::onTimerTick()
{
    const qint64  now_ns  = nowNs();
    frame_id_.fetch_add(1, std::memory_order_relaxed);

    const auto t0 = perf_clock_.nsecsElapsed();
    // Cập nhật vị trí tất cả objects
    simulateObjects(now_ns);

    const auto t1 = perf_clock_.nsecsElapsed();
    last_frame_write_us_ = (t1 - t0) / 1000.0;
    total_write_time_us_.fetch_add(static_cast<uint64_t>(last_frame_write_us_), std::memory_order_relaxed);

    frames_sent_.fetch_add(1, std::memory_order_relaxed);
}

// simulateObjects — cập nhật sample_ cho từng object rồi lập tức gọi write().
void PublisherApp::simulateObjects(qint64 now_ns)
{
    const float   t   = static_cast<float>(now_ns) * 1e-9f;
    const uint64_t fid = frame_id_.load(std::memory_order_relaxed);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        const float phase  = static_cast<float>(i) * 0.1f;
        const float radius = 10.0f + (i % 100) * 0.5f;
        const float omega  = 0.5f  + (i % 10) * 0.05f;
        const float angle  = omega * t + phase;

        sample_.frame_id     = fid;
        sample_.timestamp_ns = now_ns;
        sample_.object_id    = i;
        sample_.pos_x        = radius * std::cos(angle);
        sample_.pos_y        = radius * std::sin(angle);
        sample_.pos_z        = static_cast<float>(i % 10) * 0.1f;
        sample_.vel_x        = -radius * omega * std::sin(angle);
        sample_.vel_y        =  radius * omega * std::cos(angle);
        sample_.vel_z        = 0.0f;
        sample_.heading      = angle + static_cast<float>(M_PI_2);
        sample_.status       = 1;

        // write() ngay sau khi cập nhật object i — không đợi hết vòng lặp
        // Connext sẽ copy data vào batch buffer nội bộ.
        const DDS_ReturnCode_t rc = writer_->write(sample_, DDS_HANDLE_NIL);
        if (rc != DDS_RETCODE_OK) {
            write_failures_.fetch_add(1, std::memory_order_relaxed);
        }
    }
}

void PublisherApp::onStatsTimer()
{
    const uint64_t sent         = frames_sent_.exchange(0, std::memory_order_relaxed);
    const uint64_t failed       = write_failures_.exchange(0, std::memory_order_relaxed);
    const uint64_t total_write_us = total_write_time_us_.exchange(0, std::memory_order_relaxed);

    // Tính trung bình write time
    const double avg_write_us = sent > 0 ? static_cast<double>(total_write_us) / sent : 0.0;

    // Throughput: samples/s và MB/s
    const double samples_per_s = static_cast<double>(sent) * NUM_OBJECTS;
    const double mbps = samples_per_s * sizeof(ObjectStateMsg::ObjectState)
                        / 1024.0 / 1024.0;

    // Publication matched status
    DDS_PublicationMatchedStatus pub_status;
    if (writer_->get_publication_matched_status(pub_status) == DDS_RETCODE_OK) {
        qInfo().noquote()
            << QString("[Publisher] FPS: %1 | write(): %2 µs/frame (avg) | Subs: %3 | writeFail: %4 | ~%5 MB/s")
                   .arg(sent)
                   .arg(avg_write_us, 0, 'f', 2)
                   .arg(pub_status.current_count)
                   .arg(failed)
                   .arg(mbps, 0, 'f', 2);
    } else {
        qInfo().noquote()
            << QString("[Publisher] FPS: %1 | write(): %2 µs/frame (avg) | writeFail: %3 | ~%4 MB/s")
                   .arg(sent)
                   .arg(avg_write_us, 0, 'f', 2)
                   .arg(failed)
                   .arg(mbps, 0, 'f', 2);
    }
}

qint64 PublisherApp::nowNs()
{
    using namespace std::chrono;
    return static_cast<qint64>(
        duration_cast<nanoseconds>(
            high_resolution_clock::now().time_since_epoch()).count());
}