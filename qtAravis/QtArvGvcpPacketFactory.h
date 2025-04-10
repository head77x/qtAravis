// QtArvGvcpPacketFactory.h - Factory for creating GVCP packets
#pragma once

#include <QtGlobal>
#include <QByteArray>
#include <QString>

namespace QtArvGvcpPacketFactory {

    QByteArray createReadMemoryCmd(quint16 id, quint64 address, quint16 size);
    QByteArray createWriteMemoryCmd(quint16 id, quint64 address, const QByteArray& data);
    QByteArray createReadRegisterCmd(quint16 id, quint32 address);
    QByteArray createWriteRegisterCmd(quint16 id, quint32 address, quint32 value);

    QString describeCommand(quint16 commandCode);
    QString describeAck(quint16 ackCode);

} // namespace QtArvGvcpPacketFactory
