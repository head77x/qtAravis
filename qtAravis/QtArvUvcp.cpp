// QtArvUvcp.cpp - Qt C++ port of arvuvcp.c (USB3Vision Control Protocol)
#include "QtArvUvcp.h"
#include <QString>
#include <QByteArray>
#include <QDebug>

namespace QtArvUvcp {

    QByteArray newReadMemoryCmd(quint64 address, quint32 size, quint16 packetId) {
        QByteArray packet;
        packet.resize(24); // 8 (header) + 16 (infos)

        QDataStream stream(&packet, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);

        stream << (quint32)0x43505541; // Magic 'ARVP' LE
        stream << (quint16)0x0001;      // Flags
        stream << (quint16)0x0080;      // READ_MEMORY_CMD
        stream << (quint16)16;          // Info size
        stream << packetId;            // Packet ID
        stream << address;             // Address
        stream << (quint64)0;          // Reserved / unknown
        stream << (quint16)size;       // Read size

        return packet;
    }

    QByteArray newWriteMemoryCmd(quint64 address, const QByteArray& data, quint16 packetId) {
        QByteArray packet;
        packet.resize(24 + data.size());

        QDataStream stream(&packet, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);

        stream << (quint32)0x43505541; // Magic
        stream << (quint16)0x0001;      // Flags
        stream << (quint16)0x0082;      // WRITE_MEMORY_CMD
        stream << (quint16)(16 + data.size()); // Info + data
        stream << packetId;
        stream << address;
        stream << data;

        return packet;
    }

    QString commandToString(quint16 command) {
        switch (command) {
        case 0x0080: return "READ_MEMORY_CMD";
        case 0x0081: return "READ_MEMORY_ACK";
        case 0x0082: return "WRITE_MEMORY_CMD";
        case 0x0083: return "WRITE_MEMORY_ACK";
        default: return QString("UNKNOWN_COMMAND_%1").arg(command);
        }
    }

    QString packetToString(const QByteArray& packet) {
        if (packet.size() < 8) return "Invalid packet";
        QDataStream stream(packet);
        stream.setByteOrder(QDataStream::LittleEndian);

        quint32 magic;
        quint16 flags, command, size, id;
        stream >> magic >> flags >> command >> size >> id;

        QString out;
        out += QString("magic        = 0x%1\n").arg(magic, 8, 16, QLatin1Char('0'));
        out += QString("flags        = 0x%1\n").arg(flags, 4, 16, QLatin1Char('0'));
        out += QString("command      = %1\n").arg(commandToString(command));
        out += QString("size         = %1\n").arg(size);
        out += QString("id           = %1\n").arg(id);

        if (packet.size() >= 24 && command == 0x0080) {
            quint64 address;
            stream >> address;
            out += QString("address      = 0x%1\n").arg(address, 16, 16, QLatin1Char('0'));
        }

        return out;
    }

    void debugPacket(const QByteArray& packet) {
        qDebug().noquote() << packetToString(packet);
    }

} // namespace QtArvUvcp
