// QtArvUvcp.h - Header for USB3 Vision Control Protocol utilities
#pragma once

#include <QString>
#include <QByteArray>

namespace QtArvUvcp {

	QByteArray newReadMemoryCmd(quint64 address, quint32 size, quint16 packetId);
	QByteArray newWriteMemoryCmd(quint64 address, const QByteArray& data, quint16 packetId);
	QString commandToString(quint16 command);
	QString packetToString(const QByteArray& packet);
	void debugPacket(const QByteArray& packet);

} // namespace QtArvUvcp
