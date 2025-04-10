#pragma once

#include <QByteArray>
#include <QString>

class QtArvGvcpPacket {
public:
    QtArvGvcpPacket();
    QtArvGvcpPacket(const QByteArray& raw);

    bool isValid() const;
    quint16 command() const;
    quint16 id() const;
    QByteArray payload() const;

    QString toString() const;

private:
    QByteArray m_raw;
};
