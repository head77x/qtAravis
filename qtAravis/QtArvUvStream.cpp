// QtArvUvStream.cpp - Qt C++ port of USB3 Vision stream implementation

#include "QtArvUvStream.h"
#include "QtArvUvStreamPacket.h"
#include <QDebug>
#include <QTimer>
#include <QThread>

QtArvUvStream::QtArvUvStream(QObject* parent)
    : QObject(parent), m_streaming(false) {
}

QtArvUvStream::~QtArvUvStream() {
    stop();
}

void QtArvUvStream::start() {
    if (m_streaming) return;
    m_streaming = true;
    qDebug() << "[QtArvUvStream] Stream started";

    // Simulated streaming for now
    m_thread = QtConcurrent::run([this]() {
        while (m_streaming) {
            QByteArray dummyPacket = createDummyPacket();
            emit packetReceived(dummyPacket);
            QThread::msleep(50);
        }
    });
}

void QtArvUvStream::stop() {
    if (!m_streaming) return;
    m_streaming = false;
    qDebug() << "[QtArvUvStream] Stream stopped";
    m_thread.waitForFinished();
}

QByteArray QtArvUvStream::createDummyPacket() const {
    QByteArray packet;
    packet.resize(32);
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream << (quint32)0x03010001; // leader packet
    stream << (quint16)32;         // size
    stream << (quint64)qrand();    // frame id
    stream.skipRawData(18);        // fill rest with dummy
    return packet;
}
