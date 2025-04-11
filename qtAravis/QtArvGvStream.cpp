// QtArvGvStream.cpp - Converted GVSP stream processor from arvgvstream.c
#include "QtArvGvStream.h"
#include <QUdpSocket>
#include <QTimer>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QMetaObject>

struct QtArvGvStream::StreamContext {
    QHostAddress address;
    quint16 port;
    QUdpSocket* socket = nullptr;
    QByteArray imageData;
    quint32 expectedPayloadSize = 0;
    QImage image;
};

QtArvGvStream::QtArvGvStream(QObject* parent) : QObject(parent) {
    // TODO: Initialize if needed
}

QtArvGvStream::~QtArvGvStream() {
    stopStreaming();
    for (auto* ctx : streamMap) {
        delete ctx->socket;
        delete ctx;
    }
    streamMap.clear();
}

bool QtArvGvStream::startStreaming() {
    if (isStreaming) return true;
    for (auto it = streamMap.begin(); it != streamMap.end(); ++it) {
        auto* ctx = it.value();
        ctx->socket = new QUdpSocket(this);
        if (!ctx->socket->bind(QHostAddress::AnyIPv4, ctx->port)) {
            qWarning() << "[QtArvGvStream] Failed to bind port" << ctx->port;
            return false;
        }
        connect(ctx->socket, &QUdpSocket::readyRead, this, [=]() {
            while (ctx->socket->hasPendingDatagrams()) {
                QByteArray datagram;
                datagram.resize(ctx->socket->pendingDatagramSize());
                ctx->socket->readDatagram(datagram.data(), datagram.size());
                processDatagram(ctx, datagram);
            }
        });
    }
    isStreaming = true;
    return true;
}

void QtArvGvStream::stopStreaming() {
    isStreaming = false;
    for (auto* ctx : streamMap) {
        if (ctx->socket) {
            ctx->socket->close();
            ctx->socket->deleteLater();
            ctx->socket = nullptr;
        }
    }
}

void QtArvGvStream::attachCamera(const QString& id, QLabel* label) {
    quint16 defaultPort = 3957; // Arbitrary GVSP port for demo
    if (!streamMap.contains(id)) {
        auto* ctx = new StreamContext();
        ctx->port = defaultPort;
        streamMap[id] = ctx;
    }
    labelMap[id] = label;
}

QStringList QtArvGvStream::availableStreams() const {
    return streamMap.keys();
}

quint16 QtArvGvStream::streamPort() const {
    return 3957; // Example default port
}

void QtArvGvStream::processDatagram(StreamContext* ctx, const QByteArray& datagram) {
    processPacket(ctx, datagram);
}

void QtArvGvStream::processPacket(StreamContext* ctx, const QByteArray& packet) {
    using namespace QtArvGvspPacketUtil;
    if (packet.size() < 8) return;

    uint32_t flags = (uint8_t)packet[7];
    switch (ContentType(flags)) {
    case ContentType::Leader:
        handleLeaderPacket(ctx, packet);
        break;
    case ContentType::Payload:
        handlePayloadPacket(ctx, packet);
        break;
    case ContentType::Trailer:
        handleTrailerPacket(ctx, packet);
        break;
    default:
        break;
    }
}

void QtArvGvStream::handleLeaderPacket(StreamContext* ctx, const QByteArray& packet) {
    ctx->imageData.clear();
    ctx->expectedPayloadSize = 640 * 480;  // Simulated resolution
    ctx->image = QImage(640, 480, QImage::Format_Grayscale8);
    qDebug() << "[GVSP] Leader packet received.";
}

void QtArvGvStream::handlePayloadPacket(StreamContext* ctx, const QByteArray& packet) {
    ctx->imageData.append(packet.mid(8));
    qDebug() << "[GVSP] Payload received:" << packet.size();
}

void QtArvGvStream::handleTrailerPacket(StreamContext* ctx, const QByteArray& packet) {
    if (ctx->imageData.size() >= ctx->expectedPayloadSize) {
        memcpy(ctx->image.bits(), ctx->imageData.constData(), qMin(int(ctx->imageData.size()), ctx->image.byteCount()));
        for (auto id : streamMap.keys()) {
            if (streamMap[id] == ctx && labelMap.contains(id)) {
                QMetaObject::invokeMethod(labelMap[id], [=]() {
                    labelMap[id]->setPixmap(QPixmap::fromImage(ctx->image));
                }, Qt::QueuedConnection);
                emit imageReceived(id, ctx->image);
            }
        }
    }
    ctx->imageData.clear();
    qDebug() << "[GVSP] Trailer received.";
}
