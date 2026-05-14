#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <csignal>

#include "SubscriberApp.h"

static void signalHandler(int) { QCoreApplication::quit(); }

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("dds_subscriber_rti");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption({{"d", "domain"}, "DDS Domain ID (default: 0)", "id", "0"});
    parser.process(app);

    std::signal(SIGINT,  signalHandler);
    std::signal(SIGTERM, signalHandler);

    SubscriberApp subscriber;
    if (!subscriber.init(parser.value("domain").toInt())) {
        qCritical() << "Khởi tạo subscriber thất bại";
        return 1;
    }

    subscriber.start();
    return app.exec();
}