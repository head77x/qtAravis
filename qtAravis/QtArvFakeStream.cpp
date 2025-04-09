// QtArvFakeStream.cpp - Simulated streaming pipeline implementation
#include "QtArvFakeStream.h"
#include "QtArvFakeDevice.h"
#include "QtArvFakeCamera.h"
#include <QDebug>

QtArvFakeStream::QtArvFakeStream(QtArvFakeDevice* device, QObject* parent)
    : QObject(parent), m_camera(device->camera()), m_thread(new QThread(this)), m_cancel(0) {
    moveToThread(m_thread);
}

QtArvFakeStream::~QtArvFakeStream() {
    stop();
    delete m_thread;
}

void QtArvFakeStream::start() {
    if (m_thread->isRunning()) return;
    m_cancel = 0;
    connect(m_thread, &QThread::started, this, &QtArvFakeStream::run);
    m_thread->start();
    qDebug() << "[QtArvFakeStream] Stream started.";
}

void QtArvFakeStream::stop() {
    m_cancel = 1;
    if (m_thread->isRunning()) {
        m_thread->quit();
        m_thread->wait();
    }
    qDebug() << "[QtArvFakeStream] Stream stopped.";
}

void QtArvFakeStream::pushBuffer(QtArvBuffer* buffer) {
    QMutexLocker locker(&m_mutex);
    m_bufferPool.append(buffer);
}

QtArvBuffer* QtArvFakeStream::popBuffer() {
    QMutexLocker locker(&m_mutex);
    if (m_bufferPool.isEmpty()) {
        m_underrun++;
        return nullptr;
    }
    return m_bufferPool.takeFirst();
}

quint64 QtArvFakeStream::transferredBytes() const {
    return m_transferredBytes;
}

quint64 QtArvFakeStream::completedBuffers() const {
    return m_completed;
}

quint64 QtArvFakeStream::failedBuffers() const {
    return m_failed;
}

quint64 QtArvFakeStream::underruns() const {
    return m_underrun;
}

void QtArvFakeStream::run() {
    while (!m_cancel) {
        QtArvBuffer* buffer = popBuffer();
        if (!buffer) {
            QThread::msleep(1);
            continue;
        }

        if (m_camera && m_camera->fillBuffer(buffer)) {
            m_completed++;
            m_transferredBytes += buffer->data().size();
            emit frameReady(buffer);
        }
        else {
            m_failed++;
        }
        QThread::msleep(1);
    }
}
