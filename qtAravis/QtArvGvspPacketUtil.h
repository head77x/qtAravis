#pragma once

#include <QString>
#include <QByteArray>
#include <cstdint>

namespace QtArvGvspPacketUtil {

    enum class ContentType : uint8_t {
        Leader = 0x01,
        Payload = 0x02,
        Trailer = 0x03,
        Multipart = 0x05
    };

    struct ImageLeaderInfo {
        uint64_t timestamp;
        uint32_t width;
        uint32_t height;
        uint32_t xOffset;
        uint32_t yOffset;
        uint32_t xPadding;
        uint32_t yPadding;
        uint32_t pixelFormat;
    };

    QByteArray createLeaderPacket(uint16_t frameId, uint32_t packetId, const ImageLeaderInfo& info);
    QByteArray createPayloadPacket(uint16_t frameId, uint32_t packetId, const QByteArray& data);
    QByteArray createTrailerPacket(uint16_t frameId, uint32_t packetId);

    QString toDebugString(const QByteArray& packet);

} // namespace QtArvGvspPacketUtil
