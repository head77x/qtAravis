// QtArvCamera.cpp - Implementation of QtArvCamera
#include "QtArvCamera.h"
#include "QtArvDevice.h"
#include <QDebug>

QtArvCamera::QtArvCamera(QObject* parent)
    : QObject(parent), device(nullptr), opened(false) {
    qDebug() << "[QtArvCamera] Constructed.";
}

QtArvCamera::~QtArvCamera() {
    close();
    qDebug() << "[QtArvCamera] Destroyed.";
}

QList<QString> QtArvCamera::enumerateAvailableDevices() {
    // TODO: Replace with actual discovery
    return { "DummyCamera0", "DummyCamera1" };
}

QString QtArvCamera::getDeviceId(int index) {
    auto list = enumerateAvailableDevices();
    if (index >= 0 && index < list.size())
        return list[index];
    return QString();
}

bool QtArvCamera::open(const QString& deviceId) {
    if (opened) return true;
    id = deviceId.isEmpty() ? getDeviceId(0) : deviceId;

    // TODO: Instantiate and initialize actual device
    device = new QtArvDevice(this);
    opened = true;
    qDebug() << "[QtArvCamera] Opened device" << id;
    return true;
}

void QtArvCamera::close() {
    if (device) {
        delete device;
        device = nullptr;
    }
    opened = false;
    qDebug() << "[QtArvCamera] Closed device.";
}

bool QtArvCamera::isOpen() const {
    return opened;
}

QString QtArvCamera::getId() const { return id; }
QString QtArvCamera::getVendorName() const { return vendor; }
QString QtArvCamera::getModelName() const { return model; }
QString QtArvCamera::getDeviceVersion() const { return version; }
QString QtArvCamera::getSerialNumber() const { return serial; }

QSize QtArvCamera::getSensorSize() const { return sensorSize; }
QRect QtArvCamera::getRegion() const { return roi; }

bool QtArvCamera::setRegion(const QRect& region) {
    roi = region;
    return true;
}

bool QtArvCamera::setExposureTime(double usec) {
    Q_UNUSED(usec)
        return true;
}

double QtArvCamera::getExposureTime() const {
    return 10000.0; // dummy value
}

bool QtArvCamera::setGain(double gain) {
    Q_UNUSED(gain)
        return true;
}

double QtArvCamera::getGain() const {
    return 1.0; // dummy
}

bool QtArvCamera::startAcquisition() {
    qDebug() << "[QtArvCamera] Starting acquisition...";
    // TODO: forward to device
    return true;
}

bool QtArvCamera::stopAcquisition() {
    qDebug() << "[QtArvCamera] Stopping acquisition...";
    // TODO: forward to device
    return true;
}

QVariant QtArvCamera::readFeature(const QString& name) const {
    Q_UNUSED(name)
        return QVariant();
}

bool QtArvCamera::writeFeature(const QString& name, const QVariant& value) {
    Q_UNUSED(name)
        Q_UNUSED(value)
        return false;
}

bool QtArvCamera::triggerSoftware() {
    qDebug() << "[QtArvCamera] Triggering software...";
    return true;
}