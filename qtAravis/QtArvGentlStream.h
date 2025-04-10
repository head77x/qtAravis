// QtArvGentlStream.h - Qt wrapper for GenTL streaming
#pragma once

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QVector>
#include <QMutex>
#include <QWaitCondition>

class QtArvGentlDevice;
class QtArvBuffer;

class QtArvGentlStream : public QObject {
    Q_OBJECT
public:
    explicit QtArvGentlStream(QtArvGentlDevice* device, QObject* parent = nullptr);
    ~QtArvGentlStream();

    bool start();
    void stop();

    bool createBuffers(int count, size_t size);

signals:
    void frameReady(QtArvBuffer* buffer);

private:
    void streamLoop();

    QtArvGentlDevice* m_device;
    QThread* m_thread;
    QVector<QtArvBuffer*> m_buffers;

    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_running = false;
};
