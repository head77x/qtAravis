// QtGentlDevice.h - Header for GenTL-like device access using Aravis Qt wrapper
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QMap>
#include <QVector>

class QtArvCamera;

class QtGentlDevice : public QObject {
    Q_OBJECT

public:
    explicit QtGentlDevice(QtArvCamera* camera, QObject* parent = nullptr);
    ~QtGentlDevice();

    QString deviceId() const;
    int streamCount() const;
    QString streamId(int index) const;

    bool isValid() const;
    QObject* remotePort();

private:
    QtArvCamera* m_camera;
};
