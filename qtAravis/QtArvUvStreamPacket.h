// QtArvUvStreamPacket.h - Header for USB3Vision UVSP packet parsing
#pragma once

#include <QString>
#include <QByteArray>

class QtArvUvStreamPacket {
public:
    static QString packetToString(const QByteArray& packet);
    static void debugPacket(const QByteArray& packet);
};
