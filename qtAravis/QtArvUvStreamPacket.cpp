// QtArvUvStreamPacket.cpp - Packet parsing logic for USB3Vision stream (UVSP)

#include "QtArvUvStreamPacket.h"
#include <QByteArray>
#include <QDebug>
#include <QString>

QString QtArvUvStreamPacket::packetToString(const QByteArray& packet) {
    QString output;

    if (packet.size() < 8) return "Invalid packet";

    quint32 magic = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(packet.data()));
    quint16 size = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 4));
    quint64 frameId = qFromLittleEndian<quint64>(reinterpret_cast<const uchar*>(packet.data() + 8));

    output += QString("frame id     = %1\n").arg(frameId);

    if (magic == 0x03010001) {  // Leader packet
        output += "packet_type  = leader\n";
        output += QString("size         = %1\n").arg(size);

        if (packet.size() >= 32) {
            quint16 payloadType = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 16));
            output += QString("payload_type = %1\n").arg(payloadType == 1 ? "image" : "no data");

            quint32 pixelFormat = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(packet.data() + 18));
            quint16 width = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 22));
            quint16 height = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 24));
            quint16 xOffset = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 26));
            quint16 yOffset = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(packet.data() + 28));

            output += QString("pixel format = 0x%1\n").arg(pixelFormat, 8, 16, QLatin1Char('0'));
            output += QString("width        = %1\n").arg(width);
            output += QString("height       = %1\n").arg(height);
            output += QString("x_offset     = %1\n").arg(xOffset);
            output += QString("y_offset     = %1\n").arg(yOffset);
        }

    }
    else if (magic == 0x03010002) {  // Trailer packet
        output += "packet_type  = trailer\n";
        output += QString("size         = %1\n").arg(size);
        if (packet.size() >= 24) {
            quint64 payloadSize = qFromLittleEndian<quint64>(reinterpret_cast<const uchar*>(packet.data() + 16));
            output += QString("payload_size = %1\n").arg(payloadSize);
        }

    }
    else {
        output += "packet_type  = image\n";
    }

    return output;
}

void QtArvUvStreamPacket::debugPacket(const QByteArray& packet) {
    qDebug().noquote() << packetToString(packet);
}
