// QtArvGentlDevice.cpp - Qt wrapper for GenTL device
#include "QtArvGentlDevice.h"
#include <QDebug>
#include <cstring>

// Hypothetical C functions from GenTL library
extern "C" {
    void* gentl_open_device(const char* id);
    void gentl_close_device(void* handle);
    bool gentl_read_memory(void* handle, quint64 addr, void* buffer, quint64 size);
    bool gentl_write_memory(void* handle, quint64 addr, const void* data, quint64 size);
    const char* gentl_get_xml(void* handle);
}

QtArvGentlDevice::QtArvGentlDevice(QObject* parent) : QObject(parent) {}
QtArvGentlDevice::~QtArvGentlDevice() {
    close();
}

bool QtArvGentlDevice::open(const QString& deviceId) {
    QMutexLocker locker(&m_lock);
    close();
    m_deviceHandle = gentl_open_device(deviceId.toUtf8().constData());
    if (!m_deviceHandle) {
        qWarning() << "[QtArvGentlDevice] Failed to open device:" << deviceId;
        return false;
    }
    const char* xml = gentl_get_xml(m_deviceHandle);
    if (xml) m_xmlCache = QByteArray(xml);
    return true;
}

void QtArvGentlDevice::close() {
    QMutexLocker locker(&m_lock);
    if (m_deviceHandle) {
        gentl_close_device(m_deviceHandle);
        m_deviceHandle = nullptr;
        m_xmlCache.clear();
    }
}

QByteArray QtArvGentlDevice::readMemory(quint64 address, quint64 size) {
    QMutexLocker locker(&m_lock);
    QByteArray result;
    result.resize(static_cast<int>(size));
    if (!m_deviceHandle || !gentl_read_memory(m_deviceHandle, address, result.data(), size)) {
        qWarning() << "[QtArvGentlDevice] Failed to read memory at" << address;
        result.clear();
    }
    return result;
}

bool QtArvGentlDevice::writeMemory(quint64 address, const QByteArray& data) {
    QMutexLocker locker(&m_lock);
    if (!m_deviceHandle || !gentl_write_memory(m_deviceHandle, address, data.constData(), data.size())) {
        qWarning() << "[QtArvGentlDevice] Failed to write memory at" << address;
        return false;
    }
    return true;
}

QByteArray QtArvGentlDevice::readRegister(quint64 address, quint64 size) {
    return readMemory(address, size);
}

bool QtArvGentlDevice::writeRegister(quint64 address, const QByteArray& data) {
    return writeMemory(address, data);
}

QString QtArvGentlDevice::genicamXml() const {
    return QString::fromUtf8(m_xmlCache);
}
