// QtGentlDevice.cpp - Implementation of GenTL-like camera abstraction using Qt
#include "QtGentlDevice.h"
#include "QtArvCamera.h"
#include <QDebug>

QtGentlDevice::QtGentlDevice(QtArvCamera* camera, QObject* parent)
    : QObject(parent), m_camera(camera) {
    qDebug() << "[QtGentlDevice] Initialized for camera:" << (camera ? camera->deviceId() : "nullptr");
}

QtGentlDevice::~QtGentlDevice() {
    qDebug() << "[QtGentlDevice] Destroyed";
}

QString QtGentlDevice::deviceId() const {
    return m_camera ? m_camera->deviceId() : QString();
}

int QtGentlDevice::streamCount() const {
    return m_camera ? m_camera->streamChannelCount() : 0;
}

QString QtGentlDevice::streamId(int index) const {
    if (!m_camera || index < 0 || index >= streamCount()) return QString();
    return QString::number(index);
}

bool QtGentlDevice::isValid() const {
    return m_camera != nullptr;
}

QObject* QtGentlDevice::remotePort() {
    return m_camera ? m_camera->devicePort() : nullptr;
}
