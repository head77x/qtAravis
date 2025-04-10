// QtArvGcPort.cpp - GenICam Port node for register/memory access
#include "QtArvGcPort.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGenicam.h"
#include "QtArvDevice.h"
#include "QtArvBuffer.h"
#include <QDebug>

QtArvGcPort::QtArvGcPort() {}
QtArvGcPort::~QtArvGcPort() {}

QString QtArvGcPort::nodeName() const {
    return "Port";
}

bool QtArvGcPort::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    if (prop->propertyType() == QtArvGcPropertyNodeType::ChunkID) {
        const_cast<QtArvGcPort*>(this)->m_chunkId = prop;
        return false;
    }
    if (prop->propertyType() == QtArvGcPropertyNodeType::EventID) {
        const_cast<QtArvGcPort*>(this)->m_eventId = prop;
        return false;
    }
    return QtArvGcFeatureNode::canAppendChild(child);
}

QByteArray QtArvGcPort::read(quint64 address, quint64 length) {
    if (m_chunkId) {
        auto* buffer = genicamContext()->currentBuffer();
        if (!buffer) return {};
        quint64 chunkId = m_chunkId->toUInt64();
        return buffer->readChunk(chunkId, address, length);
    }
    if (m_eventId) {
        auto* device = genicamContext()->device();
        if (!device) return {};
        quint64 eventId = m_eventId->toUInt64();
        return device->readEventData(eventId, address, length);
    }

    auto* device = genicamContext()->device();
    if (!device) return {};
    return device->readMemory(address, length, useLegacyEndian(length));
}

void QtArvGcPort::write(quint64 address, const QByteArray& data) {
    auto* device = genicamContext()->device();
    if (!device) return;
    device->writeMemory(address, data, useLegacyEndian(data.size()));
}

bool QtArvGcPort::useLegacyEndian(quint64 length) const {
    if (m_legacyChecked) return m_useLegacy;
    m_legacyChecked = true;

    auto* genicam = genicamContext();
    if (!genicam) return false;
    QString vendor = genicam->vendorName().toLower();
    QString model = genicam->modelName().toLower();

    if ((vendor.contains("basler") && model.contains("scout")) ||
        (vendor.contains("teledyne") && model.contains("spark")) ||
        (vendor.contains("avt"))) {
        m_useLegacy = (length == 2 || length == 4 || length == 8);
    }

    return m_useLegacy;
}
