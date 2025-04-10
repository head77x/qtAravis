// QtArvGvspPacketUtil.cpp - Packet encoding for GVSP
#include "QtArvGvspPacketUtil.h"
#include <QDataStream>
#include <QDebug>

namespace QtArvGvspPacketUtil {

    static constexpr uint32_t PAYLOAD_TYPE_IMAGE = 0x00000001;

    QByteArray createLeaderPacket(uint16_t frameId, uint32_t packetId, const ImageLeaderInfo& info) {
        QByteArray packet;
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);

        s << uint16_t(0)  // packet_type reserved
            << uint16_t(frameId)
            << uint32_t(packetId | (uint32_t(ContentType::Leader) << 24));

        s << uint16_t(0); // flags
        s << uint16_t(PAYLOAD_TYPE_IMAGE);
        s << uint32_t(info.timestamp >> 32);
        s << uint32_t(info.timestamp & 0xFFFFFFFF);
        s << info.pixelFormat;
        s << info.width << info.height;
        s << info.xOffset << info.yOffset;
        s << info.xPadding << info.yPadding;

        return packet;
    }

    QByteArray createPayloadPacket(uint16_t frameId, uint32_t packetId, const QByteArray& data) {
        QByteArray packet;
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);

        s << uint16_t(0)
            << uint16_t(frameId)
            << uint32_t(packetId | (uint32_t(ContentType::Payload) << 24));

        packet.append(data);
        return packet;
    }

    QByteArray createTrailerPacket(uint16_t frameId, uint32_t packetId) {
        QByteArray packet;
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);

        s << uint16_t(0)
            << uint16_t(frameId)
            << uint32_t(packetId | (uint32_t(ContentType::Trailer) << 24));

        s << uint32_t(PAYLOAD_TYPE_IMAGE); // payload type
        s << uint32_t(0); // data0

        return packet;
    }

    QString toDebugString(const QByteArray& packet) {
        if (packet.size() < 8) return "[GVSP] Invalid packet";

        QDataStream s(packet);
        s.setByteOrder(QDataStream::BigEndian);

        uint16_t type, frameId;
        uint32_t infos;
        s >> type >> frameId >> infos;

        uint32_t packetId = infos & 0xFFFFFF;
        ContentType ct = ContentType((infos >> 24) & 0xFF);

        return QString("[GVSP] FrameID=%1 PacketID=%2 Type=%3 Bytes=%4")
            .arg(frameId)
            .arg(packetId)
            .arg(int(ct))
            .arg(packet.size());
    }

} // namespace QtArvGvspPacketUtil
