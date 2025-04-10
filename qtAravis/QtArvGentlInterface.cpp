// QtArvGentlInterface.cpp - Implements GenTL interface for device discovery
#include "QtArvGentlInterface.h"
#include "QtArvGentlDevice.h"
#include <QDebug>

// Hypothetical GenTL C API
extern "C" {
    void gentl_discover_devices();
    int gentl_get_device_count();
    const char* gentl_get_device_id(int index);
    const char* gentl_get_device_info(int index, const char* key);
}

QtArvGentlInterface* QtArvGentlInterface::m_instance = nullptr;
QMutex QtArvGentlInterface::m_mutex;

QtArvGentlInterface::QtArvGentlInterface(QObject* parent) : QObject(parent) {}
QtArvGentlInterface::~QtArvGentlInterface() {}

QtArvGentlInterface* QtArvGentlInterface::instance() {
    QMutexLocker locker(&m_mutex);
    if (!m_instance)
        m_instance = new QtArvGentlInterface();
    return m_instance;
}

void QtArvGentlInterface::destroy() {
    QMutexLocker locker(&m_mutex);
    delete m_instance;
    m_instance = nullptr;
}

void QtArvGentlInterface::discover() {
    m_devices.clear();
    gentl_discover_devices();
    int count = gentl_get_device_count();

    for (int i = 0; i < count; ++i) {
        QString id = gentl_get_device_id(i);
        QMap<QString, QString> info;
        info["Vendor"] = gentl_get_device_info(i, "Vendor");
        info["Model"] = gentl_get_device_info(i, "Model");
        info["SerialNumber"] = gentl_get_device_info(i, "SerialNumber");
        m_devices[id] = info;
    }
}

QStringList QtArvGentlInterface::deviceList() {
    QMutexLocker locker(&m_mutex);
    discover();
    return m_devices.keys();
}

QtArvGentlDevice* QtArvGentlInterface::openDevice(const QString& deviceId) {
    QMutexLocker locker(&m_mutex);
    if (!m_devices.contains(deviceId)) discover();
    if (!m_devices.contains(deviceId)) return nullptr;

    auto* device = new QtArvGentlDevice();
    return device->open(deviceId) ? device : nullptr;
}
