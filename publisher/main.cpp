#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QDebug>
#include <csignal>

#include "PublisherApp.h"

static PublisherApp* g_app = nullptr;

static void signalHandler(int)
{
    if (g_app) g_app->stop();
    QCoreApplication::quit();
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("dds_publisher_rti");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption({{"d", "domain"}, "DDS Domain ID (default: 0)", "id", "0"});
    parser.process(app);

    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);

    PublisherApp publisher;
    g_app = &publisher;

    if (!publisher.init(parser.value("domain").toInt())) {
        qCritical() << "Khởi tạo publisher thất bại";
        return 1;
    }

    // Delay 500ms để subscriber kịp match trước khi gửi frame đầu tiên
    QTimer::singleShot(500, &publisher, &PublisherApp::start);

    return app.exec();
}