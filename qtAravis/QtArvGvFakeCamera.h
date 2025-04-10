#pragma once

#include <QObject>
#include <QString>
#include <QThread>
#include <QByteArray>
#include <QHostAddress>

class QtArvFakeCamera;

class QtArvGvFakeCamera : public QObject {
    Q_OBJECT
public:
    explicit QtArvGvFakeCamera(const QString& interfaceName = "127.0.0.1",
        const QString& serialNumber = "GV01",
        const QString& genicamFile = QString(),
        QObject* parent = nullptr);
    ~QtArvGvFakeCamera();

    bool isRunning() const;
    QtArvFakeCamera* fakeCamera() const;

private:
    void start();
    void stop();

    QString m_interfaceName;
    QString m_serialNumber;
    QString m_genicamFile;

    QtArvFakeCamera* m_camera = nullptr;
    bool m_running = false;

    QThread* m_streamThread = nullptr;
};
