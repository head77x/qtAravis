// QtGentlInterface.cpp - Qt implementation of GenTL interface layer (IF)
#include "QtGentlInterface.h"
#include "QtArvInterface.h"
#include <QDebug>

QtGentlInterface::QtGentlInterface(QtArvInterface* interface, QObject* parent)
    : QObject(parent), m_interface(interface) {
    qDebug() << "[QtGentlInterface] Initialized";
}

QtGentlInterface::~QtGentlInterface() {
    qDebug() << "[QtGentlInterface] Destroyed";
}

QString QtGentlInterface::id() const {
    return m_interface ? m_interface->getId() : "";
}

QString QtGentlInterface::displayName() const {
    return m_interface ? m_interface->getDisplayName() : "";
}

QString QtGentlInterface::tlType() const {
    return m_interface ? m_interface->getTransportLayerType() : "";
}

int QtGentlInterface::deviceCount() const {
    return m_interface ? m_interface->deviceCount() : 0;
}

QString QtGentlInterface::deviceId(int index) const {
    return m_interface ? m_interface->getDeviceId(index) : "";
}

bool QtGentlInterface::updateDeviceList(bool* changed) {
    if (!m_interface) return false;
    if (changed) *changed = false; // TODO: determine change tracking
    m_interface->updateDeviceList();
    return true;
}

QVariant QtGentlInterface::getDeviceInfo(const QString& deviceId, int infoType) {
    if (!m_interface) return QVariant();
    return m_interface->getDeviceInfo(deviceId, infoType);
}

QObject* QtGentlInterface::openDevice(const QString& deviceId) {
    return m_interface ? m_interface->openDevice(deviceId) : nullptr;
}
