#pragma once

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <atomic>
#include <memory>
#include <cmath>

#include <ndds/ndds_cpp.h>

// Generated type support
#include "ObjectState.h"
#include "ObjectStateSupport.h"

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
    // ── DDS setup ──────────────────────────────────────────────────────────
    bool setupParticipant(int domain_id);
    bool setupTopic();
    bool setupPublisher();
    bool setupWriter();
    void preAllocateSample();
    void simulateObjects(qint64 now_ns);
    static qint64 nowNs();

    // DDS entities
    DDSDomainParticipant*                  participant_{nullptr};
    DDSPublisher*                          publisher_{nullptr};
    DDSTopic*                              topic_{nullptr};
    ObjectStateMsg::ObjectStateDataWriter* writer_{nullptr};

    // Pre-allocated sample
    ObjectStateMsg::ObjectState sample_{};

    // Qt timers 
    QTimer*       publish_timer_{nullptr};
    QTimer*       stats_timer_{nullptr};
    QElapsedTimer perf_clock_;

    // Stats 
    std::atomic<uint64_t> frame_id_{0};
    std::atomic<uint64_t> frames_sent_{0};   
    std::atomic<uint64_t> write_failures_{0};
    std::atomic<uint64_t> total_write_time_us_{0};   // Tích lũy thời gian write mỗi frame
    double                last_frame_write_us_{0.0}; 

    // Constants 
    static constexpr int NUM_OBJECTS = 2000;
    static constexpr int PUBLISH_HZ  = 30;
    static constexpr int PUBLISH_MS  = 1000 / PUBLISH_HZ; // 33 ms

    static constexpr int BATCH_MAX_BYTES   = 128 * 1024;   // 128 KB
    static constexpr int BATCH_MAX_SAMPLES = NUM_OBJECTS;   // flush on count first
};