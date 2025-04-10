// QtArvGvcpPacketFactory.cpp - Implements GVCP command packet construction
#include "QtArvGvcpPacketFactory.h"
#include <QDataStream>
#include <QDebug>

namespace QtArvGvcpPacketFactory {

    static constexpr quint16 GVCP_CMD_READMEM = 0x0080;
    static constexpr quint16 GVCP_CMD_WRITEMEM = 0x0082;
    static constexpr quint16 GVCP_CMD_READREG = 0x0084;
    static constexpr quint16 GVCP_CMD_WRITEREG = 0x0086;

    QByteArray createReadMemoryCmd(quint16 id, quint64 address, quint16 size) {
        QByteArray packet(12, 0);
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);
        s << GVCP_CMD_READMEM << id << quint32((address >> 32) & 0xFFFFFFFF) << quint32(address & 0xFFFFFFFF) << quint16(size);
        return packet;
    }

    QByteArray createWriteMemoryCmd(quint16 id, quint64 address, const QByteArray& data) {
        QByteArray packet;
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);
        s << GVCP_CMD_WRITEMEM << id;
        s << quint32((address >> 32) & 0xFFFFFFFF) << quint32(address & 0xFFFFFFFF);
        s << quint16(data.size());
        packet.append(data);
        return packet;
    }

    QByteArray createReadRegisterCmd(quint16 id, quint32 address) {
        QByteArray packet(8, 0);
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);
        s << GVCP_CMD_READREG << id << address;
        return packet;
    }

    QByteArray createWriteRegisterCmd(quint16 id, quint32 address, quint32 value) {
        QByteArray packet(12, 0);
        QDataStream s(&packet, QIODevice::WriteOnly);
        s.setByteOrder(QDataStream::BigEndian);
        s << GVCP_CMD_WRITEREG << id << address << value;
        return packet;
    }

    QString describeCommand(quint16 commandCode) {
        switch (commandCode) {
        case GVCP_CMD_READMEM: return "ReadMemory";
        case GVCP_CMD_WRITEMEM: return "WriteMemory";
        case GVCP_CMD_READREG: return "ReadRegister";
        case GVCP_CMD_WRITEREG: return "WriteRegister";
        default: return QString("Unknown (0x%1)").arg(commandCode, 4, 16, QLatin1Char('0'));
        }
    }

    QString describeAck(quint16 ackCode) {
        return QString("ACK for 0x%1").arg(ackCode, 4, 16, QLatin1Char('0'));
    }

} // namespace QtArvGvcpPacketFactory
