// QtArvFakeInterface.cpp - Singleton interface for managing fake devices
#include "QtArvFakeInterface.h"
#include "QtArvFakeDevice.h"
#include <QDebug>

QtArvFakeInterface* QtArvFakeInterface::s_instance = nullptr;

QtArvFakeInterface* QtArvFakeInterface::instance() {
    if (!s_instance) {
        s_instance = new QtArvFakeInterface();
    }
    return s_instance;
}

void QtArvFakeInterface::destroyInstance() {
    delete s_instance;
    s_instance = nullptr;
}

QtArvFakeInterface::QtArvFakeInterface(QObject* parent)
    : QObject(parent) {
    QtArvDeviceInfo info;
    info.deviceId = "FakeDevice-001";
    info.serial = "F001";
    info.model = "QtFakeCam";
    info.protocol = "FakeGVSP";
    m_devices.append(info);
}

QtArvFakeInterface::~QtArvFakeInterface() {
    qDebug() << "[QtArvFakeInterface] Destroyed.";
}

QList<QtArvDeviceInfo> QtArvFakeInterface::listDevices() const {
    return m_devices;
}

QtArvFakeDevice* QtArvFakeInterface::openDevice(const QString& deviceId) {
    for (const auto& dev : m_devices) {
        if (dev.deviceId == deviceId) {
            return new QtArvFakeDevice(dev.serial);
        }
    }
    return nullptr;
}
