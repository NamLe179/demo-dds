#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QFile>
#include <csignal>
#include <QDebug>
#include "SubscriberApp.h"

static void signalHandler(int) { QCoreApplication::quit(); }

namespace {

void configureStatisticsProfilesEnv()
{
    if (qEnvironmentVariableIsSet("FASTDDS_DEFAULT_PROFILES_FILE")) {
        qInfo() << "[Subscriber] FASTDDS_DEFAULT_PROFILES_FILE is already set:"
                << qEnvironmentVariable("FASTDDS_DEFAULT_PROFILES_FILE");
        return;
    }

#ifdef FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE
    const QString profile_path = QStringLiteral(FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE);
    if (QFileInfo::exists(profile_path)) {
        qputenv("FASTDDS_DEFAULT_PROFILES_FILE", QFile::encodeName(profile_path));
        qInfo() << "[Subscriber] Using statistics profile:" << profile_path;
    } else {
        qWarning() << "[Subscriber] Statistics profile not found, using Fast DDS defaults:" << profile_path;
    }
#endif
}

}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("dds_subscriber");

    configureStatisticsProfilesEnv();

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