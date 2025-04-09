// QtArvFakeStream.h
#pragma once

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QAtomicInt>
#include <QElapsedTimer>
#include "QtArvBuffer.h"

class QtArvFakeCamera;
class QtArvFakeDevice;

class QtArvFakeStream : public QObject {
    Q_OBJECT

public:
    explicit QtArvFakeStream(QtArvFakeDevice* device, QObject* parent = nullptr);
    ~QtArvFakeStream();

    void start();
    void stop();
    void pushBuffer(QtArvBuffer* buffer);
    QtArvBuffer* popBuffer();

    quint64 transferredBytes() const;
    quint64 completedBuffers() const;
    quint64 failedBuffers() const;
    quint64 underruns() const;

signals:
    void frameReady(QtArvBuffer* buffer);

private:
    void run();
    QtArvFakeCamera* m_camera;
    QThread* m_thread;
    QAtomicInt m_cancel;

    mutable QMutex m_mutex;
    QList<QtArvBuffer*> m_bufferPool;

    // Statistics
    quint64 m_transferredBytes = 0;
    quint64 m_completed = 0;
    quint64 m_failed = 0;
    quint64 m_underrun = 0;
};
