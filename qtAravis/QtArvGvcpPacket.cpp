// QtArvGvcpPacket.cpp - Raw GVCP packet parsing implementation
#include "QtArvGvcpPacket.h"
#include <QDataStream>
#include <QDebug>

QtArvGvcpPacket::QtArvGvcpPacket() {}

QtArvGvcpPacket::QtArvGvcpPacket(const QByteArray& raw)
    : m_raw(raw) {
}

bool QtArvGvcpPacket::isValid() const {
    return m_raw.size() >= 4;
}

quint16 QtArvGvcpPacket::command() const {
    if (!isValid()) return 0;
    QDataStream s(m_raw);
    s.setByteOrder(QDataStream::BigEndian);
    quint16 cmd;
    s >> cmd;
    return cmd;
}

quint16 QtArvGvcpPacket::id() const {
    if (!isValid()) return 0;
    QDataStream s(m_raw);
    s.setByteOrder(QDataStream::BigEndian);
    quint16 cmd, id;
    s >> cmd >> id;
    return id;
}

QByteArray QtArvGvcpPacket::payload() const {
    if (m_raw.size() <= 4) return {};
    return m_raw.mid(4);
}

QString QtArvGvcpPacket::toString() const {
    return QString("[GVCP] Cmd=0x%1, ID=0x%2, PayloadSize=%3")
        .arg(command(), 4, 16, QLatin1Char('0'))
        .arg(id(), 4, 16, QLatin1Char('0'))
        .arg(payload().size());
}
