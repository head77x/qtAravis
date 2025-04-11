// QtArvV4L2Interface.h - Qt wrapper for V4L2 interface management
#pragma once

#include <QObject>
#include <QString>
#include <QHash>
#include <QMutex>
#include "QtArvV4L2Device.h"

struct QtArvV4L2DeviceInfo {
    QString id;
    QString bus;
    QString deviceFile;
    QString version;
};

class QtArvV4L2Interface : public QObject {
    Q_OBJECT
public:
    static QtArvV4L2Interface* instance();
    static void destroy();

    void refreshDeviceList();
    QStringList availableDevices() const;
    QtArvV4L2Device* openDevice(const QString& deviceId, QString& error);

private:
    explicit QtArvV4L2Interface(QObject* parent = nullptr);
    ~QtArvV4L2Interface();

    static QtArvV4L2Interface* s_instance;
    static QMutex s_mutex;

    QHash<QString, QtArvV4L2DeviceInfo> m_deviceMap;
};
