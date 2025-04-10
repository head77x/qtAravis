#pragma once

#include <QObject>
#include <QString>
#include <QMap>
#include <QStringList>
#include <QMutex>

class QtArvGentlSystem;
class QtArvGentlDevice;

class QtArvGentlInterface : public QObject {
    Q_OBJECT
public:
    static QtArvGentlInterface* instance();  // Singleton
    static void destroy();

    QStringList deviceList();
    QtArvGentlDevice* openDevice(const QString& deviceId);

private:
    explicit QtArvGentlInterface(QObject* parent = nullptr);
    ~QtArvGentlInterface();

    void discover();

    static QtArvGentlInterface* m_instance;
    static QMutex m_mutex;

    QMap<QString, QMap<QString, QString>> m_devices;  // deviceId -> {vendor, model, serial}
};
