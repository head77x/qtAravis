#pragma once
// QtArvFakeCamera.h - Simulated fake camera (ported from Aravis)
#pragma once

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QElapsedTimer>

class QtArvBuffer;

class QtArvFakeCamera : public QObject {
    Q_OBJECT

public:
    explicit QtArvFakeCamera(QObject* parent = nullptr);
    ~QtArvFakeCamera();

    void setPixelFormat(const QString& format);
    void setFrameSize(int width, int height);
    void setPayloadSize(int size);
    void setFrameRate(double fps);

    int getPayloadSize() const;
    QByteArray readMemory(quint32 address, int size) const;

    void startTriggering();
    void stopTriggering();

    bool fillBuffer(QtArvBuffer* buffer);

signals:
    void frameReady(QtArvBuffer* buffer);

private slots:
    void onTrigger();

private:
    int m_width = 640;
    int m_height = 480;
    QString m_pixelFormat = "Mono8";
    int m_payloadSize = 640 * 480;
    double m_fps = 10.0;

    QTimer* m_triggerTimer = nullptr;
    QElapsedTimer m_time;
};
