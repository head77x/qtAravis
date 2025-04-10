// QtArvGvDevice.h - Header for QtArvGvDevice
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>

class QtArvGvDevice : public QObject {
    Q_OBJECT

public:
    QtArvGvDevice();
    ~QtArvGvDevice();

    bool connectToDevice(const QString& ipAddress);
    QByteArray readMemory(quint64 address, quint16 size);
    bool writeMemory(quint64 address, const QByteArray& data);

private:
    // Add socket and protocol state here
};
