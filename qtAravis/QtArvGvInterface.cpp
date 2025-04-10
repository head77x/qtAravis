// QtArvGvInterface.cpp - Simplified GVCP Interface manager for Qt
#include "QtArvGvInterface.h"
#include "QtArvGvDevice.h"
#include <QDebug>
#include <QUdpSocket>
#include <QHostInfo>

QtArvGvInterface* QtArvGvInterface::m_instance = nullptr;
QMutex QtArvGvInterface::m_mutex;

QtArvGvInterface::QtArvGvInterface(QObject* parent)
    : QObject(parent) {
}

QtArvGvInterface::~QtArvGvInterface() {}

QtArvGvInterface* QtArvGvInterface::instance() {
    QMutexLocker locker(&m_mutex);
    if (!m_instance)
        m_instance = new QtArvGvInterface();
    return m_instance;
}

void QtArvGvInterface::destroy() {
    QMutexLocker locker(&m_mutex);
    delete m_instance;
    m_instance = nullptr;
}

QStringList QtArvGvInterface::discoverDeviceIds() {
    m_devices.clear();
    if (!sendDiscovery()) return {};
    parseDiscovery();
    return m_devices.keys();
}

QtArvGvDevice* QtArvGvInterface::openDevice(const QString& idOrAddress) {
    if (!m_devices.contains(idOrAddress)) {
        QHostAddress addr(idOrAddress);
        if (!addr.isNull()) {
            return new QtArvGvDevice(); // pass addr later
        }
        return nullptr;
    }
    QHostAddress addr = m_devices.value(idOrAddress);
    return new QtArvGvDevice(); // pass addr later
}

bool QtArvGvInterface::sendDiscovery() {
    QUdpSocket socket;
    socket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    QByteArray discoveryPacket;
    discoveryPacket.resize(36); // fake GVCP discovery packet
    discoveryPacket.fill(0);

    qint64 sent = socket.writeDatagram(discoveryPacket,
        QHostAddress::Broadcast,
        3956);
    return sent > 0;
}

void QtArvGvInterface::parseDiscovery() {
    // This is a placeholder. A real implementation would
    // receive datagrams and parse GVCP ACKs
    m_devices.insert("FakeCam-ModelX-001", QHostAddress("192.168.1.2"));
    m_devices.insert("FakeCam-ModelX-002", QHostAddress("192.168.1.3"));
}
    