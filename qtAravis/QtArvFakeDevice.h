// QtArvFakeDevice.h - Simulated device that wraps a fake camera
#pragma once

#include <QObject>
#include <QString>
#include <QScopedPointer>

class QtArvFakeCamera;
class QtArvGenicam;
class QtArvStream;
class QtArvBuffer;

class QtArvFakeDevice : public QObject {
    Q_OBJECT

public:
    explicit QtArvFakeDevice(const QString& serialNumber, QObject* parent = nullptr);
    ~QtArvFakeDevice();

    QtArvStream* createStream();

    QByteArray getGenicamXml() const;
    QtArvGenicam* getGenicam() const;

    QByteArray readMemory(quint64 address, int size) const;
    bool writeMemory(quint64 address, const QByteArray& data);

    quint32 readRegister(quint64 address) const;
    bool writeRegister(quint64 address, quint32 value);

    QtArvFakeCamera* camera() const;

private:
    QString m_serial;
    QtArvFakeCamera* m_camera;
    QtArvGenicam* m_genicam;
};
