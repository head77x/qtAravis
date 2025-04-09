// QtArvFakeInterface.h
#pragma once

#include <QObject>
#include <QList>
#include <QString>

class QtArvFakeDevice;

struct QtArvDeviceInfo {
    QString deviceId;
    QString physicalId;
    QString address;
    QString vendor;
    QString manufacturerInfo;
    QString model;
    QString serial;
    QString protocol;
};

class QtArvFakeInterface : public QObject {
    Q_OBJECT

public:
    static QtArvFakeInterface* instance();
    static void destroyInstance();

    QList<QtArvDeviceInfo> listDevices() const;
    QtArvFakeDevice* openDevice(const QString& deviceId);

private:
    explicit QtArvFakeInterface(QObject* parent = nullptr);
    ~QtArvFakeInterface();

    static QtArvFakeInterface* s_instance;
};
