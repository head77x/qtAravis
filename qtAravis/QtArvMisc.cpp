// QtArvMisc.cpp - Utility functions converted from arvmisc.c
#include "QtArvMisc.h"
#include <QByteArray>
#include <QDebug>
#include <QDateTime>
#include <QtEndian>
#include <cstdlib>
#include <cstring>

namespace QtArvMisc {

    quint64 currentTimestamp() {
        // Returns milliseconds since Unix epoch
        return QDateTime::currentMSecsSinceEpoch();
    }

    QByteArray duplicateBuffer(const void* src, size_t size) {
        if (!src || size == 0) return QByteArray();
        return QByteArray(reinterpret_cast<const char*>(src), static_cast<int>(size));
    }

    quint32 qToHost32(const quint8* data) {
        return qFromBigEndian<quint32>(data);
    }

    quint64 qToHost64(const quint8* data) {
        return qFromBigEndian<quint64>(data);
    }

    void qToBytes32(quint32 val, quint8* out) {
        qToBigEndian(val, out);
    }

    void qToBytes64(quint64 val, quint8* out) {
        qToBigEndian(val, out);
    }

    QString formatHex(const QByteArray& data) {
        // Optimized hex formatting using preallocated string
        QString result;
        result.reserve(data.size() * 3);
        for (int i = 0; i < data.size(); ++i) {
            result += QString::number(static_cast<quint8>(data[i]), 16).rightJustified(2, '0').toUpper();
            if (i % 2 == 1) result += ' ';
        }
        return result.trimmed();
    }
    return hex.trimmed();
}

} // namespace QtArvMisc
