// qtArvFakeGvCamera.cpp - CLI entry point for simulating GVSP camera

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <csignal>
#include <iostream>

#include "QtArvFakeDevice.h" // wraps QtArvFakeCamera
#include "QtArvDebug.h"

static bool cancel = false;

static void handleSigInt(int) {
    cancel = true;
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("qt-fake-gv-camera");

    QCommandLineParser parser;
    parser.setApplicationDescription("Simulated GigE Vision Fake Camera");
    parser.addHelpOption();

    QCommandLineOption interfaceOpt(QStringList() << "i" << "interface", "Listening interface address", "interface");
    QCommandLineOption serialOpt(QStringList() << "s" << "serial", "Fake camera serial number", "serial");
    QCommandLineOption genicamOpt(QStringList() << "g" << "genicam", "GenICam XML file path", "file");
    QCommandLineOption lossOpt(QStringList() << "r" << "gvsp-lost-ratio", "GVSP packet loss ratio (per thousand)", "ratio", "0");
    QCommandLineOption debugOpt(QStringList() << "d" << "debug", "Debug domains", "domains");

    parser.addOptions({ interfaceOpt, serialOpt, genicamOpt, lossOpt, debugOpt });
    parser.process(app);

    if (parser.isSet(debugOpt))
        QtArvDebug::setLevel("all", QtArvDebugLevel::Debug);

    QString serial = parser.value(serialOpt);
    QString genicamFile = parser.value(genicamOpt);
    double lossRatio = parser.value(lossOpt).toDouble();

    auto* device = new QtArvFakeDevice(serial);
    // TODO: Load genicam XML to device
    Q_UNUSED(genicamFile);

    QObject::connect(&app, &QCoreApplication::aboutToQuit, [=]() {
        std::cout << "Shutting down..." << std::endl;
    });

    std::signal(SIGINT, handleSigInt);

    QTimer loopTimer;
    QObject::connect(&loopTimer, &QTimer::timeout, [&]() {
        if (cancel) app.quit();
    });
    loopTimer.start(100);

    return app.exec();
}
