// QtArvInterface.cpp - Abstract camera interface implementation
#include "QtArvInterface.h"

QtArvInterface::QtArvInterface(QObject* parent)
    : QObject(parent) {
}

QtArvInterface::~QtArvInterface() {}

int QtArvInterface::deviceCount() const {
    return m_devices.size();
}

QString QtArvInterface::deviceId(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].deviceId : QString();
}

QString QtArvInterface::physicalId(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].physicalId : QString();
}

QString QtArvInterface::address(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].address : QString();
}

QString QtArvInterface::vendor(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].vendor : QString();
}

QString QtArvInterface::manufacturerInfo(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].manufacturerInfo : QString();
}

QString QtArvInterface::model(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].model : QString();
}

QString QtArvInterface::serial(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].serial : QString();
}

QString QtArvInterface::protocol(int index) const {
    return index >= 0 && index < m_devices.size() ? m_devices[index].protocol : QString();
}
