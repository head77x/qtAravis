// QtArvV4L2Device.h - Qt C++ wrapper for V4L2 device abstraction
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QScopedPointer>

#ifdef Q_OS_WIN
#include <QCamera>
#endif

class QtArvV4L2Device : public QObject {
    Q_OBJECT
public:
    explicit QtArvV4L2Device(const QString& deviceFile, QObject* parent = nullptr);
    ~QtArvV4L2Device();

    bool open();
    void close();

    QString deviceName() const;
    QString driverVersion() const;
    QString driverName() const;
    QString manufacturerInfo() const;

    QByteArray readMemory(quint64 address, int size);
    bool writeMemory(quint64 address, const QByteArray& data);

    QByteArray getGenicamXml() const;

private:
#ifdef Q_OS_LINUX
    int m_fd;
#endif

#ifdef Q_OS_WIN
    QCamera* m_camera;
#endif

    QString m_deviceFile;
    QString m_card;
    QString m_driver;
    QString m_version;
    QByteArray m_genicamXml;

    bool loadGenicamXml();
};
