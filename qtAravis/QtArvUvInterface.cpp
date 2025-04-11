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
    // TODO: ���� USB ��ġ ��ĵ �� ���͸� ���� �ʿ�
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
    // TODO: ���� USB ��ġ���� descriptor �о USB3Vision ���� �Ǵ�
    return true;
}

QtArvUvInterface::DeviceInfo QtArvUvInterface::createDeviceInfoFromUsb(void* /*rawDevice*/) {
    DeviceInfo info;
    // TODO: USB ��ġ���� ���� �����Ͽ� ä���
    info.id = "usb3vision-XXX";
    info.name = "Unknown USB3Vision Device";
    return info;
}
