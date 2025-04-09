// QtArvFakeCamera.cpp - Simulated fake camera implementation
#include "QtArvFakeCamera.h"
#include "QtArvBuffer.h"
#include <QDebug>
#include <QImage>
#include <QPainter>

QtArvFakeCamera::QtArvFakeCamera(QObject* parent)
    : QObject(parent), m_triggerTimer(new QTimer(this)) {
    connect(m_triggerTimer, &QTimer::timeout, this, &QtArvFakeCamera::onTrigger);
}

QtArvFakeCamera::~QtArvFakeCamera() {
    stopTriggering();
}

void QtArvFakeCamera::setPixelFormat(const QString& format) {
    m_pixelFormat = format;
}

void QtArvFakeCamera::setFrameSize(int width, int height) {
    m_width = width;
    m_height = height;
    m_payloadSize = width * height; // Mono8 assumption
}

void QtArvFakeCamera::setPayloadSize(int size) {
    m_payloadSize = size;
}

void QtArvFakeCamera::setFrameRate(double fps) {
    m_fps = fps;
    if (m_triggerTimer->isActive()) {
        startTriggering();
    }
}

int QtArvFakeCamera::getPayloadSize() const {
    return m_payloadSize;
}

QByteArray QtArvFakeCamera::readMemory(quint32 address, int size) const {
    Q_UNUSED(address);
    return QByteArray(size, 0xFF); // Dummy memory filled with 0xFF
}

void QtArvFakeCamera::startTriggering() {
    int intervalMs = static_cast<int>(1000.0 / m_fps);
    m_triggerTimer->start(intervalMs);
    m_time.start();
    qDebug() << "[QtArvFakeCamera] Triggering started at" << m_fps << "FPS";
}

void QtArvFakeCamera::stopTriggering() {
    m_triggerTimer->stop();
    qDebug() << "[QtArvFakeCamera] Triggering stopped.";
}

void QtArvFakeCamera::onTrigger() {
    auto* buffer = new QtArvBuffer(m_payloadSize);
    if (fillBuffer(buffer)) {
        emit frameReady(buffer);
    }
    else {
        delete buffer;
    }
}

bool QtArvFakeCamera::fillBuffer(QtArvBuffer* buffer) {
    if (!buffer) return false;

    QImage img(m_width, m_height, QImage::Format_Grayscale8);
    img.fill(Qt::black);

    QPainter p(&img);
    p.setPen(Qt::white);
    p.drawText(img.rect(), Qt::AlignCenter, "FAKE");
    p.end();

    QByteArray data(reinterpret_cast<const char*>(img.bits()), img.sizeInBytes());
    buffer->setData(data);
    buffer->setTimestamp(m_time.elapsed());
    return true;
}
