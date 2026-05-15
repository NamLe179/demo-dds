#pragma once

#include <QObject>
#include <QTimer>
#include <atomic>
#include <unordered_map>
#include <memory>

#include <ndds/ndds_cpp.h>

// Generated type support
#include "ObjectState.h"
#include "ObjectStateSupport.h"

class SubscriberApp;

// ReaderListener — chạy trong Connext receive thread
class ReaderListener : public DDSDataReaderListener {
public:
    explicit ReaderListener(SubscriberApp* owner) : owner_(owner) {}

    void on_data_available(DDSDataReader* reader) override;

    void on_subscription_matched(
        DDSDataReader* reader,
        const DDS_SubscriptionMatchedStatus& status) override;

    void on_requested_deadline_missed(
        DDSDataReader* reader,
        const DDS_RequestedDeadlineMissedStatus& status) override;

    void on_sample_rejected(
        DDSDataReader* reader,
        const DDS_SampleRejectedStatus& status) override;

    void on_liveliness_changed(
        DDSDataReader* reader,
        const DDS_LivelinessChangedStatus& status) override;

private:
    SubscriberApp* owner_;
};

// Stats — tất cả atomic 
struct RxStats {
    // Frame-level stats (1 frame = 2000 samples với cùng frame_id)
    std::atomic<uint64_t> frames_received{0};
    std::atomic<uint64_t> frames_dropped{0};
    std::atomic<uint64_t> drop_events{0};

    // Sample-level stats
    std::atomic<uint64_t> samples_received{0};
    std::atomic<uint64_t> samples_rejected{0};

    // Latency (us)
    std::atomic<int64_t>  last_latency_us{0};
    std::atomic<int64_t>  max_latency_us{0};
    std::atomic<uint64_t> total_latency_us{0};       // Tích lũy latency
    std::atomic<uint64_t> latency_sample_count{0};   // Số samples đo latency

    // Tracking
    std::atomic<uint64_t> last_frame_id{0};

    // Callback stats
    std::atomic<uint64_t> cb_count{0};
    std::atomic<uint64_t> take_count{0};   // số lần take() trả RETCODE_OK
    std::atomic<uint64_t> no_data_count{0};
};

// SubscriberApp
class SubscriberApp : public QObject {
    Q_OBJECT

public:
    explicit SubscriberApp(QObject* parent = nullptr);
    ~SubscriberApp() override;

    bool init(int domain_id = 0);
    void start();

    // Gọi từ ReaderListener (Connext thread)
    void processDataAvailable(DDSDataReader* reader);
    static int64_t nowNs();

    RxStats stats;

private slots:
    void onStatsTimer();

private:
    bool setupParticipant(int domain_id);
    bool setupTopic();
    bool setupSubscriber();
    bool setupReader();

    // DDS entities 
    DDSDomainParticipant*                  participant_{nullptr};
    DDSSubscriber*                         subscriber_{nullptr};
    DDSTopic*                              topic_{nullptr};
    ObjectStateMsg::ObjectStateDataReader* reader_{nullptr};

    ReaderListener listener_;
    QTimer*        stats_timer_{nullptr};

    std::atomic<int64_t> last_gap_log_ns_{0};

    static constexpr int     NUM_OBJECTS         = 2000;
    static constexpr int64_t GAP_LOG_INTERVAL_NS = 250'000'000; // 250ms

    // Số sample tối đa lấy mỗi lần take() — lấy đủ 1 batch (2000) + buffer nhỏ
    static constexpr int MAX_TAKE_SAMPLES = 4096;
};