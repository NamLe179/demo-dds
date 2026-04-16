#pragma once

#include <QObject>
#include <QTimer>
#include <atomic>
#include <memory>
\
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
\
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.hpp>

// Generated
#include "ObjectState.hpp"
#include "ObjectStatePubSubTypes.hpp"

namespace fastdds  = eprosima::fastdds::dds;
namespace rtps = eprosima::fastdds::rtps;

class SubscriberApp;

// ReaderListener chạy trong FastDDS internal thread 
class ReaderListener : public fastdds::DataReaderListener {
public:
    explicit ReaderListener(SubscriberApp* owner) : owner_(owner) {}

    void on_data_available(fastdds::DataReader* reader) override;

    void on_subscription_matched(
        fastdds::DataReader*,
        const fastdds::SubscriptionMatchedStatus& info) override;

    void on_requested_deadline_missed(
        fastdds::DataReader*,
        const fastdds::RequestedDeadlineMissedStatus&) override;

    void on_sample_rejected(
        fastdds::DataReader*,
        const fastdds::SampleRejectedStatus& status) override;

private:
    SubscriberApp* owner_;
};

struct RxStats {
    std::atomic<uint64_t> frames_received{0};
    std::atomic<uint64_t> frames_dropped{0};
    std::atomic<uint64_t> drop_events{0};
    std::atomic<uint64_t> samples_rejected{0};
    std::atomic<uint64_t> objects_processed{0};
    std::atomic<int64_t>  last_latency_us{0};
    std::atomic<int64_t>  max_latency_us{0};
    std::atomic<uint64_t> last_frame_id{0};
};

class SubscriberApp : public QObject {
    Q_OBJECT

public:
    explicit SubscriberApp(QObject* parent = nullptr);
    ~SubscriberApp() override;

    bool init(int domain_id = 0);
    void start();

    // Gọi từ ReaderListener (FastDDS thread) 
    void processFrame(const ObjectStateMsg::ObjectStateBatch& batch,
                      int64_t recv_ns);

    // Public để ReaderListener dùng
    static int64_t nowNs();

    RxStats stats;

private slots:
    void onStatsTimer();

private:
    bool setupParticipant(int domain_id);
    bool setupTopic();
    bool setupSubscriber();
    bool setupReader();

    fastdds::DomainParticipant* participant_{nullptr};
    fastdds::Subscriber*         subscriber_{nullptr};
    fastdds::Topic*              topic_{nullptr};
    fastdds::DataReader*         reader_{nullptr};
    fastdds::TypeSupport          type_support_;

    ReaderListener listener_;
    QTimer*        stats_timer_{nullptr};
    std::atomic<int64_t> last_gap_log_ns_{0};

    static constexpr int    NUM_OBJECTS   = 2000;
    static constexpr size_t SHM_SEG_BYTES = 64ULL * 1024 * 1024;
    static constexpr int64_t GAP_LOG_INTERVAL_NS = 250'000'000; // 250ms
};
