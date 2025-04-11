// QtArvTool.cpp - Reimplementation of arv-tool command-line logic in Qt C++

#include "QtArvSystem.h"
#include "QtArvDevice.h"
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <iostream>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("QtArvTool");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("QtArvTool - Control and query GenICam devices");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("command", "The command to execute: features, control, network, etc.");
    parser.addPositionalArgument("parameters", "Command parameters.", "parameters...");

    parser.process(app);

    const QStringList args = parser.positionalArguments();
    if (args.isEmpty()) {
        QtArvSystem::updateDeviceList();
        int n = QtArvSystem::getDeviceCount();
        if (n == 0) {
            qWarning() << "No device found.";
            return 1;
        }
        for (int i = 0; i < n; ++i) {
            qDebug() << QtArvSystem::getDeviceId(i) << "(" << QtArvSystem::getDeviceAddress(i) << ")";
        }
        return 0;
    }

    QString command = args[0];
    QString deviceId = args.length() > 1 ? args[1] : "";

    QString error;
    QtArvDevice* device = QtArvSystem::openDevice(deviceId, &error);
    if (!device) {
        qWarning() << "Failed to open device:" << error;
        return 1;
    }

    if (command == "features") {
        const auto features = device->listAllFeatures();
        for (const auto& feature : features) {
            qDebug() << feature;
        }
    }
    else if (command == "control") {
        for (int i = 2; i < args.size(); ++i) {
            QString cmd = args[i];
            if (!device->executeControlCommand(cmd)) {
                qWarning() << "Control failed for" << cmd;
            }
        }
    }
    else if (command == "network") {
        for (int i = 2; i < args.size(); ++i) {
            QString cmd = args[i];
            if (!device->executeNetworkCommand(cmd)) {
                qWarning() << "Network command failed for" << cmd;
            }
        }
    }
    else {
        qWarning() << "Unknown command:" << command;
    }

    QtArvSystem::shutdown();
    return 0;
}
