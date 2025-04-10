#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QMutex>

class QtArvGentlDevice : public QObject {
    Q_OBJECT
public:
    explicit QtArvGentlDevice(QObject* parent = nullptr);
    ~QtArvGentlDevice();

    bool open(const QString& deviceId);
    void close();

    QByteArray readMemory(quint64 address, quint64 size);
    bool writeMemory(quint64 address, const QByteArray& data);

    QByteArray readRegister(quint64 address, quint64 size);
    bool writeRegister(quint64 address, const QByteArray& data);

    QString genicamXml() const;

private:
    void* m_deviceHandle = nullptr;
    QByteArray m_xmlCache;
    QMutex m_lock;
};
