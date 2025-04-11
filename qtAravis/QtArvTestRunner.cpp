// QtArvTestRunner.cpp - Ported from arvtest.c
#include "QtArvTestRunner.h"
#include "QtArvSystem.h"
#include "QtArvDevice.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QTimer>

QtArvTestRunner::QtArvTestRunner(QObject* parent) : QObject(parent) {
    // 초기화 로직
}

void QtArvTestRunner::run() {
    QTextStream out(stdout);
    QtArvSystem::updateDeviceList();
    int deviceCount = QtArvSystem::getDeviceCount();

    out << "[TestRunner] Devices found: " << deviceCount << "\n";

    for (int i = 0; i < deviceCount; ++i) {
        QString id = QtArvSystem::getDeviceId(i);
        out << "\n[Device " << i << "] ID: " << id << "\n";

        QString error;
        QtArvDevice* device = QtArvSystem::openDevice(id, &error);
        if (!device) {
            out << "Failed to open device: " << error << "\n";
            continue;
        }

        out << "Running basic connectivity test...\n";
        if (device->ping()) {
            out << "Ping success.\n";
        }
        else {
            out << "Ping failed.\n";
        }

        // 기타 테스트 케이스 확장 예정

        delete device;
    }

    out << "\n[TestRunner] All tests complete.\n";
    QCoreApplication::exit(0);
}
