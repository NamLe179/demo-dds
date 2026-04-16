// publisher/main.cpp
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <csignal>
#include <QDebug>
#include "PublisherApp.h"

static PublisherApp* g_app = nullptr;

static void signalHandler(int) {
    if (g_app) g_app->stop();
    QCoreApplication::quit();
}

namespace {

void configureStatisticsProfilesEnv()
{
    if (qEnvironmentVariableIsSet("FASTDDS_DEFAULT_PROFILES_FILE")) {
        qInfo() << "[Publisher] FASTDDS_DEFAULT_PROFILES_FILE is already set:" 
                << qEnvironmentVariable("FASTDDS_DEFAULT_PROFILES_FILE");
        return;
    }

#ifdef FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE
    const QString profile_path = QStringLiteral(FASTDDS_STATISTICS_DEFAULT_PROFILES_FILE);
    if (QFileInfo::exists(profile_path)) {
        qputenv("FASTDDS_DEFAULT_PROFILES_FILE", QFile::encodeName(profile_path));
        qInfo() << "[Publisher] Using statistics profile:" << profile_path;
    } else {
        qWarning() << "[Publisher] Statistics profile not found, using Fast DDS defaults:" << profile_path;
    }
#endif
}

}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("dds_publisher");

    configureStatisticsProfilesEnv();

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

    // Delay 500ms để subscriber kịp match
    QTimer::singleShot(500, &publisher, &PublisherApp::start);

    return app.exec();
}