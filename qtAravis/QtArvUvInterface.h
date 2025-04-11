// QtArvUvInterface.h - Header for Qt USB3Vision Interface
#pragma once

#include <QObject>
#include <QString>
#include <QHash>
#include <QMutex>
#include <QByteArray>
#include "QtArvDevice.h"

class QtArvUvInterface : public QObject {
    Q_OBJECT

public:
    static QtArvUvInterface* instance();
    static void destroy();

    void updateDeviceList();
    QStringList availableDeviceIds() const;
    QtArvDevice* openDevice(const QString& deviceId, QString& error);

private:
    explicit QtArvUvInterface(QObject* parent = nullptr);
    ~QtArvUvInterface();

    struct DeviceInfo {
        QString id;
        QString name;
        QString fullName;
        QString manufacturer;
        QString product;
        QString serialNumber;
        QString guid;
    };

    static QtArvUvInterface* s_instance;
    static QMutex s_mutex;

    QHash<QString, DeviceInfo> m_devices;

    void discover();
    bool matchUsb3VisionProtocols(void* rawDevice);
    DeviceInfo createDeviceInfoFromUsb(void* rawDevice);
};
