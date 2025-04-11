// QtArvV4L2Interface.cpp - Qt wrapper for V4L2 interface implementation
#include "QtArvV4L2Interface.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>

QtArvV4L2Interface* QtArvV4L2Interface::s_instance = nullptr;
QMutex QtArvV4L2Interface::s_mutex;

QtArvV4L2Interface* QtArvV4L2Interface::instance() {
    QMutexLocker locker(&s_mutex);
    if (!s_instance) {
        s_instance = new QtArvV4L2Interface();
    }
    return s_instance;
}

void QtArvV4L2Interface::destroy() {
    QMutexLocker locker(&s_mutex);
    delete s_instance;
    s_instance = nullptr;
}

QtArvV4L2Interface::QtArvV4L2Interface(QObject* parent)
    : QObject(parent) {
    refreshDeviceList();
}

QtArvV4L2Interface::~QtArvV4L2Interface() {
    m_deviceMap.clear();
}

void QtArvV4L2Interface::refreshDeviceList() {
    m_deviceMap.clear();

    QDir devDir("/dev");
    QStringList nameFilters;
    nameFilters << "video*";

    QFileInfoList deviceFiles = devDir.entryInfoList(nameFilters, QDir::System | QDir::Readable | QDir::Files);

    for (const QFileInfo& fileInfo : deviceFiles) {
        QString devPath = fileInfo.absoluteFilePath();
        QtArvV4L2Device temp(devPath);
        if (temp.open()) {
            QtArvV4L2DeviceInfo info;
            info.deviceFile = devPath;
            info.id = fileInfo.fileName();
            info.version = temp.driverVersion();
            info.bus = temp.driverName();
            m_deviceMap.insert(info.id, info);
            temp.close();
        }
    }
}

QStringList QtArvV4L2Interface::availableDevices() const {
    return m_deviceMap.keys();
}

QtArvV4L2Device* QtArvV4L2Interface::openDevice(const QString& deviceId, QString& error) {
    if (!m_deviceMap.contains(deviceId)) {
        error = "Device ID not found: " + deviceId;
        return nullptr;
    }
    const QtArvV4L2DeviceInfo& info = m_deviceMap.value(deviceId);
    QtArvV4L2Device* dev = new QtArvV4L2Device(info.deviceFile);
    if (!dev->open()) {
        error = "Failed to open V4L2 device: " + info.deviceFile;
        delete dev;
        return nullptr;
    }
    return dev;
}
