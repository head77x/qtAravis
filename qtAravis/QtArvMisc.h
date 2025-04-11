#pragma once

#include <QString>
#include <QByteArray>
#include <QtGlobal>

namespace QtArvMisc {

	quint64 currentTimestamp();
	QByteArray duplicateBuffer(const void* src, size_t size);
	quint32 qToHost32(const quint8* data);
	quint64 qToHost64(const quint8* data);
	void qToBytes32(quint32 val, quint8* out);
	void qToBytes64(quint64 val, quint8* out);
	QString formatHex(const QByteArray& data);

} // namespace QtArvMisc
