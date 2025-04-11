// QtArvUvInterface.cpp - Implementation for USB3Vision Interface logic
#include "QtArvUvInterface.h"
#include "QtArvUvDevice.h"
#include <QDebug>

QtArvUvInterface* QtArvUvInterface::s_instance = nullptr;
QMutex QtArvUvInterface::s_mutex;

QtArvUvInterface* QtArvUvInterface::instance() {
    QMutexLocker locker(&s_mutex);
    if (!s_instance)
        s_instance = new QtArvUvInterface();
    return s_instance;
}

void QtArvUvInterface::destroy() {
    QMutexLocker locker(&s_mutex);
    delete s_instance;
    s_instance = nullptr;
}

QtArvUvInterface::QtArvUvInterface(QObject* parent)
    : QObject(parent) {
    updateDeviceList();
}

QtArvUvInterface::~QtArvUvInterface() {
    m_devices.clear();
}

void QtArvUvInterface::updateDeviceList() {
    m_devices.clear();
    discover();
}

QStringList QtArvUvInterface::availableDeviceIds() const {
    return m_devices.keys();
}

QtArvDevice* QtArvUvInterface::openDevice(const QString& deviceId, QString& error) {
    if (!m_devices.contains(deviceId)) {
        error = "Device not found: " + deviceId;
        return nullptr;
    }
    auto* dev = new QtArvUvDevice();
    if (!dev->open(deviceId)) {
        error = "Failed to open device: " + deviceId;
        delete dev;
        return nullptr;
    }
    return dev;
}

void QtArvUvInterface::discover() {
    // TODO: 실제 USB 장치 스캔 및 필터링 로직 필요
    DeviceInfo dev;
    dev.id = "usb3vision-001";
    dev.name = "Demo USB3Vision Device";
    dev.fullName = "USB3 Vision Demo Device 001";
    dev.manufacturer = "QtVision Inc.";
    dev.product = "QtArv Camera";
    dev.serialNumber = "000123456";
    dev.guid = "ABCDEF123456";

    m_devices.insert(dev.id, dev);
    qDebug() << "[QtArvUvInterface] Discovered" << dev.fullName;
}

bool QtArvUvInterface::matchUsb3VisionProtocols(void* /*rawDevice*/) {
    // TODO: 실제 USB 장치에서 descriptor 읽어서 USB3Vision 여부 판단
    return true;
}

QtArvUvInterface::DeviceInfo QtArvUvInterface::createDeviceInfoFromUsb(void* /*rawDevice*/) {
    DeviceInfo info;
    // TODO: USB 장치에서 정보 추출하여 채우기
    info.id = "usb3vision-XXX";
    info.name = "Unknown USB3Vision Device";
    return info;
}
