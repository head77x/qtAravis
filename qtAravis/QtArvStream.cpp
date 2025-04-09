// QtArvStream.cpp - Implementation for QtArvStream
#include "QtArvStream.h"
#include "QtArvBuffer.h"
#include "QtArvDevice.h"
#include <QDebug>

QtArvStream::QtArvStream(QtArvDevice* device, std::function<void()> callback, QObject* parent)
    : QObject(parent), device(device), callback(callback), emitSignal(true)
{
    qDebug() << "[QtArvStream] Stream created.";
}

QtArvStream::~QtArvStream() {
    qDebug() << "[QtArvStream] Stream destroyed.";
}

void QtArvStream::pushBuffer(QSharedPointer<QtArvBuffer> buffer) {
    QMutexLocker locker(&mutex);
    inputQueue.enqueue(buffer);
    bufferAvailable.wakeOne();
    if (emitSignal)
        emit newBufferAvailable();
    if (callback)
        callback();
}

QSharedPointer<QtArvBuffer> QtArvStream::popBuffer() {
    QMutexLocker locker(&mutex);
    while (inputQueue.isEmpty()) {
        bufferAvailable.wait(&mutex);
    }
    return inputQueue.dequeue();
}

QSharedPointer<QtArvBuffer> QtArvStream::tryPopBuffer() {
    QMutexLocker locker(&mutex);
    if (inputQueue.isEmpty()) return nullptr;
    return inputQueue.dequeue();
}

QSharedPointer<QtArvBuffer> QtArvStream::timeoutPopBuffer(qint64 timeoutMs) {
    QMutexLocker locker(&mutex);
    if (!bufferAvailable.wait(&mutex, timeoutMs)) return nullptr;
    if (inputQueue.isEmpty()) return nullptr;
    return inputQueue.dequeue();
}

void QtArvStream::pushOutputBuffer(QSharedPointer<QtArvBuffer> buffer) {
    QMutexLocker locker(&mutex);
    outputQueue.enqueue(buffer);
    fillingCount++;
}

QSharedPointer<QtArvBuffer> QtArvStream::popInputBuffer() {
    QMutexLocker locker(&mutex);
    if (outputQueue.isEmpty()) return nullptr;
    fillingCount--;
    return outputQueue.dequeue();
}

QSharedPointer<QtArvBuffer> QtArvStream::timeoutPopInputBuffer(qint64 timeoutMs) {
    QMutexLocker locker(&mutex);
    if (!bufferAvailable.wait(&mutex, timeoutMs)) return nullptr;
    if (outputQueue.isEmpty()) return nullptr;
    fillingCount--;
    return outputQueue.dequeue();
}

void QtArvStream::getBufferStatistics(int* input, int* output, int* filling) {
    QMutexLocker locker(&mutex);
    if (input) *input = inputQueue.size();
    if (output) *output = outputQueue.size();
    if (filling) *filling = fillingCount;
}

bool QtArvStream::startAcquisition() {
    qDebug() << "[QtArvStream] startAcquisition called (not yet implemented)";
    return false;
}

bool QtArvStream::stopAcquisition() {
    qDebug() << "[QtArvStream] stopAcquisition called (not yet implemented)";
    return false;
}

void QtArvStream::setEmitSignals(bool enabled) {
    emitSignal = enabled;
}

bool QtArvStream::getEmitSignals() const {
    return emitSignal;
}

void QtArvStream::declareInfo(const QString& name, QVariant value) {
    QMutexLocker locker(&mutex);
    streamInfo.append({ name, value });
}

int QtArvStream::getInfoCount() const {
    return streamInfo.size();
}

QString QtArvStream::getInfoName(int index) const {
    if (index >= 0 && index < streamInfo.size())
        return streamInfo[index].name;
    return QString();
}

QVariant QtArvStream::getInfoValue(int index) const {
    if (index >= 0 && index < streamInfo.size())
        return streamInfo[index].value;
    return QVariant();
}

QVariant QtArvStream::getInfoValueByName(const QString& name) const {
    for (const auto& info : streamInfo) {
        if (info.name == name)
            return info.value;
    }
    return QVariant();
}