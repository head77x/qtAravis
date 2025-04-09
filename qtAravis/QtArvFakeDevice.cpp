// QtArvFakeDevice.cpp - Implementation of fake device based on fake camera
#include "QtArvFakeDevice.h"
#include "QtArvFakeCamera.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvFakeDevice::QtArvFakeDevice(const QString& serialNumber, QObject* parent)
    : QObject(parent), m_serial(serialNumber) {

    if (m_serial.isEmpty()) {
        qCritical() << "[QtArvFakeDevice] Error: Cannot create device without serial number.";
        return;
    }

    m_camera = new QtArvFakeCamera(this);
    // TODO: Load GenICam XML for m_camera
    m_genicam = new QtArvGenicam(this); // Placeholder

    qDebug() << "[QtArvFakeDevice] Device created with serial:" << m_serial;
}

QtArvFakeDevice::~QtArvFakeDevice() {
    delete m_genicam;
    delete m_camera;
}

QtArvStream* QtArvFakeDevice::createStream() {
    // TODO: Implement QtArvFakeStream support
    return nullptr;
}

QByteArray QtArvFakeDevice::getGenicamXml() const {
    // TODO: Call m_camera->getGenicamXml();
    return QByteArray();
}

QtArvGenicam* QtArvFakeDevice::getGenicam() const {
    return m_genicam;
}

QByteArray QtArvFakeDevice::readMemory(quint64 address, int size) const {
    return m_camera ? m_camera->readMemory(address, size) : QByteArray();
}

bool QtArvFakeDevice::writeMemory(quint64 address, const QByteArray& data) {
    Q_UNUSED(address);
    Q_UNUSED(data);
    // TODO: Implement write support
    return true;
}

quint32 QtArvFakeDevice::readRegister(quint64 address) const {
    QByteArray mem = readMemory(address, sizeof(quint32));
    if (mem.size() == sizeof(quint32)) {
        quint32 val;
        memcpy(&val, mem.constData(), sizeof(quint32));
        return val;
    }
    return 0;
}

bool QtArvFakeDevice::writeRegister(quint64 address, quint32 value) {
    QByteArray data(reinterpret_cast<const char*>(&value), sizeof(quint32));
    return writeMemory(address, data);
}

QtArvFakeCamera* QtArvFakeDevice::camera() const {
    return m_camera;
}
