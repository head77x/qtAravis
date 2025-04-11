// QtGentlInterface.h - Qt wrapper for GenTL IF (Interface) layer
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QMap>

class QtArvInterface;

class QtGentlInterface : public QObject {
    Q_OBJECT

public:
    explicit QtGentlInterface(QtArvInterface* interface, QObject* parent = nullptr);
    ~QtGentlInterface();

    QString id() const;
    QString displayName() const;
    QString tlType() const;

    int deviceCount() const;
    QString deviceId(int index) const;

    bool updateDeviceList(bool* changed = nullptr);
    QVariant getDeviceInfo(const QString& deviceId, int infoType);

    QObject* openDevice(const QString& deviceId);

private:
    QtArvInterface* m_interface;
};
