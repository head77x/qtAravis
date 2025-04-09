// QtArvCamera.h - C++ wrapper for Aravis camera
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QList>
#include <QSize>
#include <QRect>
#include <QPoint>

class QtArvDevice;

class QtArvCamera : public QObject {
    Q_OBJECT

public:
    explicit QtArvCamera(QObject* parent = nullptr);
    virtual ~QtArvCamera();

    static QList<QString> enumerateAvailableDevices();
    static QString getDeviceId(int index);

    bool open(const QString& deviceId = QString());
    void close();

    bool isOpen() const;

    QString getId() const;
    QString getVendorName() const;
    QString getModelName() const;
    QString getDeviceVersion() const;
    QString getSerialNumber() const;

    QSize getSensorSize() const;
    QRect getRegion() const;

    bool setRegion(const QRect& region);
    bool setExposureTime(double usec);
    double getExposureTime() const;

    bool setGain(double gain);
    double getGain() const;

    bool startAcquisition();
    bool stopAcquisition();

    QVariant readFeature(const QString& name) const;
    bool writeFeature(const QString& name, const QVariant& value);

    bool triggerSoftware();

signals:
    void frameReady();
    void cameraDisconnected();

private:
    QtArvDevice* device = nullptr;
    QString id;
    QString vendor;
    QString model;
    QString version;
    QString serial;

    QSize sensorSize;
    QRect roi;

    bool opened = false;
};