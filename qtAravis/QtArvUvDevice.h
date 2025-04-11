// QtArvUvDevice.h - Qt C++ port of arvuvdevice.c
#pragma once

#include <QObject>
#include <QByteArray>
#include <QString>

class QtArvUvDevice : public QObject {
    Q_OBJECT
public:
    explicit QtArvUvDevice(QObject* parent = nullptr);
    ~QtArvUvDevice();

    bool open(const QString& devicePath);
    void close();

    bool readMemory(quint64 address, QByteArray& outData, QString& error);
    bool writeMemory(quint64 address, const QByteArray& data, QString& error);

    QString getDevicePath() const;

private:
    QString devicePath;
    bool isOpen = false;

    bool sendControlTransfer(const QByteArray& request, QByteArray& response, QString& error);
};
