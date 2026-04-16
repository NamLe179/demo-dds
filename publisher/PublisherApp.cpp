#include "PublisherApp.h"
#include <QDebug>
#include <chrono>
#include <cmath>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;

namespace {

const char* returnCodeToString(ReturnCode_t rc)
{
    if (rc == RETCODE_OK) return "RETCODE_OK";
    if (rc == RETCODE_ERROR) return "RETCODE_ERROR";
    if (rc == RETCODE_UNSUPPORTED) return "RETCODE_UNSUPPORTED";
    if (rc == RETCODE_BAD_PARAMETER) return "RETCODE_BAD_PARAMETER";
    if (rc == RETCODE_PRECONDITION_NOT_MET) return "RETCODE_PRECONDITION_NOT_MET";
    if (rc == RETCODE_OUT_OF_RESOURCES) return "RETCODE_OUT_OF_RESOURCES";
    if (rc == RETCODE_NOT_ENABLED) return "RETCODE_NOT_ENABLED";
    if (rc == RETCODE_IMMUTABLE_POLICY) return "RETCODE_IMMUTABLE_POLICY";
    if (rc == RETCODE_INCONSISTENT_POLICY) return "RETCODE_INCONSISTENT_POLICY";
    if (rc == RETCODE_ALREADY_DELETED) return "RETCODE_ALREADY_DELETED";
    if (rc == RETCODE_TIMEOUT) return "RETCODE_TIMEOUT";
    if (rc == RETCODE_NO_DATA) return "RETCODE_NO_DATA";
    if (rc == RETCODE_ILLEGAL_OPERATION) return "RETCODE_ILLEGAL_OPERATION";
    if (rc == RETCODE_NOT_ALLOWED_BY_SECURITY) return "RETCODE_NOT_ALLOWED_BY_SECURITY";
    return "RETCODE_UNKNOWN";
}

}

void WriterListener::on_publication_matched(
    DataWriter*,
    const PublicationMatchedStatus& info)
{
    matched.fetch_add(info.current_count_change, std::memory_order_relaxed);
    qInfo() << "[Publisher] Matched subscribers:" << matched.load();
}

void WriterListener::on_offered_deadline_missed(
    DataWriter*,
    const OfferedDeadlineMissedStatus&)
{
    qWarning() << "[Publisher] Deadline missed — writer chậm!";
}

PublisherApp::PublisherApp(QObject* parent)
    : QObject(parent)
{}

PublisherApp::~PublisherApp()
{
    stop();

    // Cleanup theo thứ tự ngược
    if (publisher_ && writer_)   publisher_->delete_datawriter(writer_);
    if (participant_ && publisher_) participant_->delete_publisher(publisher_);
    if (participant_ && topic_)  participant_->delete_topic(topic_);
    if (participant_)
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool PublisherApp::init(int domain_id)
{
    if (!setupParticipant(domain_id)) return false;
    if (!setupTopic())               return false;
    if (!setupPublisher())           return false;
    if (!setupWriter())              return false;

    preAllocateData();

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
            << "| Target:" << PUBLISH_HZ << "Hz";
    return true;
}

bool PublisherApp::setupParticipant(int domain_id)
{
    DomainParticipantQos pqos;
    pqos.name("HighFreqPublisher");

    // Hiển thị monitor cho chart view
    pqos.properties().properties().emplace_back(
        "fastdds.statistics",
        "HISTORY_LATENCY_TOPIC;PUBLICATION_THROUGHPUT_TOPIC;SUBSCRIPTION_THROUGHPUT_TOPIC"
    );

    // Shared Memory Transport
    auto shm = std::make_shared<SharedMemTransportDescriptor>();
    shm->segment_size(SHM_SEG_BYTES);
    shm->max_message_size(2 * 1024 * 1024); // 2MB >> 72KB/frame
    shm->port_queue_capacity(512);
    shm->healthy_check_timeout_ms(1000);

    pqos.transport().user_transports.push_back(shm);
    pqos.transport().use_builtin_transports = true; // tắt UDP/TCP khi chạy local để chắc chắn dùng shared memory, bật lên đẻ monitor bắt được

    // Flow Controller: đang để giới hạn 10MB
    auto fc = std::make_shared<FlowControllerDescriptor>();
    fc->name                = "high_freq_fc";
    fc->scheduler           = FlowControllerSchedulerPolicy::FIFO;
    fc->max_bytes_per_period = 10 * 1024 * 1024; // 10MB/period
    fc->period_ms           = static_cast<uint64_t>(PUBLISH_MS); // 33ms

    pqos.flow_controllers().push_back(fc);

    participant_ = DomainParticipantFactory::get_instance()
                       ->create_participant(domain_id, pqos);
    if (!participant_) {
        qCritical() << "[Publisher] Không tạo được DomainParticipant";
        return false;
    }
    return true;
}

bool PublisherApp::setupTopic()
{
    type_support_ = TypeSupport(new ObjectStateMsg::ObjectStateBatchPubSubType());
    if (type_support_.register_type(participant_) != RETCODE_OK) {
        qCritical() << "[Publisher] Không đăng ký được type";
        return false;
    }

    topic_ = participant_->create_topic(
        "ObjectStateBatch",
        type_support_.get_type_name(),
        TOPIC_QOS_DEFAULT);

    if (!topic_) {
        qCritical() << "[Publisher] Không tạo được Topic";
        return false;
    }
    return true;
}

bool PublisherApp::setupPublisher()
{
    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT);
    if (!publisher_) {
        qCritical() << "[Publisher] Không tạo được Publisher";
        return false;
    }
    return true;
}

bool PublisherApp::setupWriter()
{
    DataWriterQos wqos;

    // BEST_EFFORT: không retransmit, không ACK
    wqos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

    // KEEP_LAST depth=1: writer chỉ giữ frame mới nhất
    wqos.history().kind  = KEEP_LAST_HISTORY_QOS;
    wqos.history().depth = 1;

    wqos.resource_limits().max_samples              = 1;
    wqos.resource_limits().max_instances            = 1;
    wqos.resource_limits().max_samples_per_instance = 1;

    // ASYNC: write() return ngay, không block QTimer thread
    wqos.publish_mode().kind                 = ASYNCHRONOUS_PUBLISH_MODE;
    wqos.publish_mode().flow_controller_name = "high_freq_fc";

    // Deadline cảnh báo nếu không publish kịp 30Hz (+5ms margin)
    wqos.deadline().period = eprosima::fastdds::dds::Duration_t{
        0, static_cast<uint32_t>((PUBLISH_MS + 5) * 1'000'000u)
    };

    writer_ = publisher_->create_datawriter(topic_, wqos, &writer_listener_);
    if (!writer_) {
        qCritical() << "[Publisher] Không tạo được DataWriter";
        return false;
    }

    qInfo() << "[Publisher] DataWriter: BEST_EFFORT | KEEP_LAST(1) | ASYNC";
    return true;
}

// Pre-allocate: gọi 1 lần duy nhất — sau đó chỉ ghi đè giá trị
// Fixed array[2000] trong IDL: không cần resize, vùng nhớ đã cố định
void PublisherApp::preAllocateData()
{
    batch_.frame_id(0);
    batch_.timestamp_ns(0);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        auto& obj = batch_.objects()[i];
        obj.object_id(i);
        obj.pos_x(0.0f);  obj.pos_y(0.0f);  obj.pos_z(0.0f);
        obj.vel_x(0.0f);  obj.vel_y(0.0f);  obj.vel_z(0.0f);
        obj.heading(0.0f);
        obj.status(1);
    }

    qInfo() << "[Publisher] Pre-allocated" << NUM_OBJECTS
            << "objects — hot path không có malloc";
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

// Hot path — gọi mỗi 33ms — KHÔNG được có malloc/free
void PublisherApp::onTimerTick()
{
    const qint64 now_ns = nowNs();

    batch_.frame_id(frame_id_.fetch_add(1, std::memory_order_relaxed));
    batch_.timestamp_ns(now_ns);

    simulateObjects(now_ns);

    // write() với ASYNC mode: return ~0.4µs, không block
    const auto t0 = perf_clock_.nsecsElapsed();
    const ReturnCode_t rc = writer_->write(&batch_);
    const auto t1 = perf_clock_.nsecsElapsed();

    last_write_us_ = (t1 - t0) / 1000.0;

    if (rc == RETCODE_OK) {
        frames_sent_.fetch_add(1, std::memory_order_relaxed);
        return;
    }

    write_failures_.fetch_add(1, std::memory_order_relaxed);

    // FastDDS không expose trực tiếp bucket hết token
    // writer trả timeout/out-of-resources trong async mode => có thể là dấu hiệu backpressure.
    if (rc == RETCODE_OUT_OF_RESOURCES || rc == RETCODE_TIMEOUT) {
        const auto q = possible_queue_events_.fetch_add(1, std::memory_order_relaxed) + 1;
        qWarning().noquote()
            << QString("[Publisher] Backpressure suspected (flow-control queue/history đầy). rc=%1 | queueEvents=%2")
                   .arg(returnCodeToString(rc))
                   .arg(q);
    } else {
        qWarning().noquote()
            << QString("[Publisher] write() failed. rc=%1")
                   .arg(returnCodeToString(rc));
    }
}

void PublisherApp::simulateObjects(qint64 now_ns)
{
    const float t = static_cast<float>(now_ns) * 1e-9f;

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        auto& obj = batch_.objects()[i];

        const float phase  = static_cast<float>(i) * 0.1f;
        const float radius = 10.0f + (i % 100) * 0.5f;
        const float omega  = 0.5f  + (i % 10) * 0.05f;
        const float angle  = omega * t + phase;

        obj.pos_x(radius * std::cos(angle));
        obj.pos_y(radius * std::sin(angle));
        obj.pos_z(static_cast<float>(i % 10) * 0.1f);
        obj.vel_x(-radius * omega * std::sin(angle));
        obj.vel_y( radius * omega * std::cos(angle));
        obj.vel_z(0.0f);
        obj.heading(angle + static_cast<float>(M_PI_2));
        obj.status(1);
    }
}

void PublisherApp::onStatsTimer()
{
    const int sent    = frames_sent_.exchange(0, std::memory_order_relaxed);
    const int matched = writer_listener_.matched.load();
    const uint64_t failed = write_failures_.exchange(0, std::memory_order_relaxed);
    const uint64_t queue_events = possible_queue_events_.exchange(0, std::memory_order_relaxed);

    qInfo().noquote()
        << QString("[Publisher] FPS: %1 | write(): %2 µs | Subs: %3 | writeFail: %4 | queueEvt: %5 | ~%6 MB/s")
               .arg(sent)
               .arg(last_write_us_, 0, 'f', 2)
               .arg(matched)
               .arg(failed)
               .arg(queue_events)
               .arg(sent * NUM_OBJECTS * sizeof(ObjectStateMsg::ObjectState)
                        / 1024.0 / 1024.0, 0, 'f', 2);
}

qint64 PublisherApp::nowNs()
{
    using namespace std::chrono;
    return static_cast<qint64>(
        duration_cast<nanoseconds>(
            high_resolution_clock::now().time_since_epoch()).count());
}
