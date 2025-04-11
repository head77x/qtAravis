// QtArvV4L2Stream.cpp - V4L2 streaming abstraction for Qt
#include "QtArvV4L2Stream.h"
#include <QDebug>
#include <QThread>

QtArvV4L2Stream::QtArvV4L2Stream(QObject* parent)
    : QObject(parent), m_running(false) {
}

QtArvV4L2Stream::~QtArvV4L2Stream() {
    stop();
}

void QtArvV4L2Stream::start() {
    if (m_running) return;
    m_running = true;
    qDebug() << "[QtArvV4L2Stream] Acquisition started";

    m_thread = QtConcurrent::run([this]() {
        while (m_running) {
            QThread::sleep(1); // Simulate wait for buffer

            emit newBufferReady();
        }
        emit streamStopped();
        qDebug() << "[QtArvV4L2Stream] Acquisition stopped";
    });
}

void QtArvV4L2Stream::stop() {
    if (!m_running) return;
    m_running = false;
    m_thread.waitForFinished();
}

bool QtArvV4L2Stream::isRunning() const {
    return m_running;
}
