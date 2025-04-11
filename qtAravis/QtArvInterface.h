#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>

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

class QtArvInterface : public QObject {
    Q_OBJECT
public:
    explicit QtArvInterface(QObject* parent = nullptr);
    virtual ~QtArvInterface();

    virtual void updateDeviceList() = 0;
    virtual QObject* openDevice(const QString& deviceId = QString()) = 0;

    int deviceCount() const;
    QString deviceId(int index) const;
    QString physicalId(int index) const;
    QString address(int index) const;
    QString vendor(int index) const;
    QString manufacturerInfo(int index) const;
    QString model(int index) const;
    QString serial(int index) const;
    QString protocol(int index) const;

protected:
    QList<QtArvDeviceInfo> m_devices;
};
