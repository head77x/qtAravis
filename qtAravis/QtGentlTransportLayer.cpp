#include "QtGentlTransportLayer.h"
#include "QtGentlInterface.h"
#include <QDebug>

QtGentlTransportLayer::QtGentlTransportLayer(QObject* parent)
    : QObject(parent), m_isOpen(false) {
    qDebug() << "[TL] Transport layer created";
}

QtGentlTransportLayer::~QtGentlTransportLayer() {
    close();
}

bool QtGentlTransportLayer::open() {
    if (m_isOpen) {
        qWarning() << "[TL] Already open";
        return false;
    }

    // Normally: disable GenTL Aravis if needed
    qDebug() << "[TL] Opening transport layer";
    m_isOpen = true;
    return true;
}

void QtGentlTransportLayer::close() {
    if (!m_isOpen) return;
    qDebug() << "[TL] Closing transport layer";
    m_isOpen = false;
}

int QtGentlTransportLayer::getNumInterfaces() const {
    if (!m_isOpen) return 0;
    // Simulate
    return 1;
}

QString QtGentlTransportLayer::getInterfaceId(int index) const {
    if (!m_isOpen || index != 0) return QString();
    return QString("QtAravisIF0");
}

QString QtGentlTransportLayer::getInterfaceInfo(const QString& ifaceId, int infoCmd) const {
    if (!m_isOpen) return QString();

    if (infoCmd == 0) return ifaceId;
    if (infoCmd == 1) return "QtAravisInterface Display";
    if (infoCmd == 2) return "QtAravis-TL";
    return QString();
}

QtGentlInterface* QtGentlTransportLayer::openInterface(const QString& ifaceId) {
    if (!m_isOpen || ifaceId.isEmpty()) return nullptr;
    return new QtGentlInterface(nullptr);  // placeholder for now
}

bool QtGentlTransportLayer::updateInterfaceList(bool* changed, quint64 timeout) {
    Q_UNUSED(timeout);
    if (!m_isOpen) return false;
    if (changed) *changed = true;
    return true;
}
