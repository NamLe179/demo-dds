#pragma once

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <atomic>
#include <memory>
#include <cmath>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.hpp>

#include <fastdds/rtps/flowcontrol/FlowControllerDescriptor.hpp>

#include "ObjectState.hpp"
#include "ObjectStatePubSubTypes.hpp"

namespace fastdds  = eprosima::fastdds::dds;
namespace rtps = eprosima::fastdds::rtps;

class WriterListener : public fastdds::DataWriterListener {
public:
    void on_publication_matched(
        fastdds::DataWriter*,
        const fastdds::PublicationMatchedStatus& info) override;

    void on_offered_deadline_missed(
        fastdds::DataWriter*,
        const fastdds::OfferedDeadlineMissedStatus&) override;

    std::atomic<int> matched{0};
};

class PublisherApp : public QObject {
    Q_OBJECT

public:
    explicit PublisherApp(QObject* parent = nullptr);
    ~PublisherApp() override;

    bool init(int domain_id = 0);

public slots:
    void start();
    void stop();

private slots:
    void onTimerTick();
    void onStatsTimer();

private:
    bool setupParticipant(int domain_id);
    bool setupTopic();
    bool setupPublisher();
    bool setupWriter();
    void preAllocateData();
    void simulateObjects(qint64 now_ns);
    static qint64 nowNs();

    // DDS entities
    fastdds::DomainParticipant* participant_{nullptr};
    fastdds::Publisher*          publisher_{nullptr};
    fastdds::Topic*              topic_{nullptr};
    fastdds::DataWriter*         writer_{nullptr};
    fastdds::TypeSupport          type_support_;
    WriterListener            writer_listener_;

    // Pre-allocated batch
    ObjectStateMsg::ObjectStateBatch batch_;

    // Qt timers
    QTimer*       publish_timer_{nullptr};
    QTimer*       stats_timer_{nullptr};
    QElapsedTimer perf_clock_;

    // Stats
    std::atomic<uint64_t> frame_id_{0};
    std::atomic<int>      frames_sent_{0};
    std::atomic<uint64_t> write_failures_{0};
    std::atomic<uint64_t> possible_queue_events_{0};
    double                last_write_us_{0.0};

    static constexpr int    NUM_OBJECTS   = 2000;
    static constexpr int    PUBLISH_HZ    = 30;
    static constexpr int    PUBLISH_MS    = 1000 / PUBLISH_HZ;
    static constexpr size_t SHM_SEG_BYTES = 64ULL * 1024 * 1024; // 64MB
};
