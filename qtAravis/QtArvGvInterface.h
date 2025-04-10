#pragma once

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QHostAddress>
#include <QMutex>

class QtArvGvDevice;

class QtArvGvInterface : public QObject {
    Q_OBJECT
public:
    static QtArvGvInterface* instance();
    static void destroy();

    QStringList discoverDeviceIds();
    QtArvGvDevice* openDevice(const QString& idOrAddress);

private:
    explicit QtArvGvInterface(QObject* parent = nullptr);
    ~QtArvGvInterface();

    bool sendDiscovery();
    void parseDiscovery();

    static QtArvGvInterface* m_instance;
    static QMutex m_mutex;

    QMap<QString, QHostAddress> m_devices; // ID ¡æ IP Address
};
