// QtArvBuffer.cpp - Implementation of QtArvBuffer
#include "QtArvBuffer.h"
#include <QDebug>
#include <cstring>

QtArvBuffer::QtArvBuffer(size_t size, void* preallocated) {
    if (preallocated) {
        byteBuffer = QByteArray::fromRawData(static_cast<const char*>(preallocated), static_cast<int>(size));
    }
    else {
        byteBuffer.resize(static_cast<int>(size));
    }
    userPtr = nullptr;
    qDebug() << "[QtArvBuffer] Allocated buffer of size" << size;
}

QtArvBuffer::~QtArvBuffer() {
    // nothing specific for now
    qDebug() << "[QtArvBuffer] Destroyed.";
}

const void* QtArvBuffer::data(size_t* sizeOut) const {
    if (sizeOut) *sizeOut = static_cast<size_t>(byteBuffer.size());
    return byteBuffer.constData();
}

void* QtArvBuffer::data() {
    return byteBuffer.data();
}

bool QtArvBuffer::hasChunks() const {
    return chunkEnabled;
}

const void* QtArvBuffer::getChunkData(quint64 chunkId, size_t* sizeOut) const {
    Q_UNUSED(chunkId)
        if (sizeOut) *sizeOut = 0;
    return nullptr; // not implemented
}

bool QtArvBuffer::hasGenDC() const {
    return gendcEnabled;
}

const void* QtArvBuffer::getGenDCData(size_t* sizeOut) const {
    if (sizeOut) *sizeOut = gendcSize;
    return gendcSize > 0 ? byteBuffer.constData() + gendcOffset : nullptr;
}

const void* QtArvBuffer::getGenDCDescriptor(size_t* sizeOut) const {
    if (sizeOut) *sizeOut = gendcDescSize;
    return gendcDescSize > 0 ? byteBuffer.constData() + gendcOffset + gendcSize : nullptr;
}

const void* QtArvBuffer::userData() const {
    return userPtr;
}

QtArvBufferStatus QtArvBuffer::status() const {
    return bufferStatus;
}

QtArvPayloadType QtArvBuffer::payloadType() const {
    return payload;
}

quint64 QtArvBuffer::timestamp() const {
    return timeStamp;
}

void QtArvBuffer::setTimestamp(quint64 ts) {
    timeStamp = ts;
}

quint64 QtArvBuffer::systemTimestamp() const {
    return sysTimeStamp;
}

void QtArvBuffer::setSystemTimestamp(quint64 ts) {
    sysTimeStamp = ts;
}

quint64 QtArvBuffer::frameId() const {
    return frameNumber;
}

void QtArvBuffer::setFrameId(quint64 id) {
    frameNumber = id;
}

int QtArvBuffer::partCount() const {
    return parts.size();
}

int QtArvBuffer::findComponent(int componentId) const {
    for (int i = 0; i < parts.size(); ++i) {
        if (parts[i].componentId == componentId) return i;
    }
    return -1;
}

const void* QtArvBuffer::partData(int partId, size_t* sizeOut) const {
    if (partId < 0 || partId >= parts.size()) return nullptr;
    const auto& p = parts[partId];
    if (sizeOut) *sizeOut = p.size;
    return byteBuffer.constData() + p.dataOffset;
}

quint64 QtArvBuffer::partPixelFormat(int partId) const {
    if (partId < 0 || partId >= parts.size()) return 0;
    return parts[partId].pixelFormat;
}

QRect QtArvBuffer::partRegion(int partId) const {
    if (partId < 0 || partId >= parts.size()) return QRect();
    const auto& p = parts[partId];
    return QRect(p.xOffset, p.yOffset, p.width, p.height);
}

QSize QtArvBuffer::partSize(int partId) const {
    if (partId < 0 || partId >= parts.size()) return QSize();
    return QSize(parts[partId].width, parts[partId].height);
}

QPoint QtArvBuffer::partOffset(int partId) const {
    if (partId < 0 || partId >= parts.size()) return QPoint();
    return QPoint(parts[partId].xOffset, parts[partId].yOffset);
}

QPoint QtArvBuffer::partPadding(int partId) const {
    if (partId < 0 || partId >= parts.size()) return QPoint();
    return QPoint(parts[partId].xPadding, parts[partId].yPadding);
}

const void* QtArvBuffer::imageData(size_t* sizeOut) const {
    return partData(0, sizeOut);
}

quint64 QtArvBuffer::imagePixelFormat() const {
    return partPixelFormat(0);
}

QRect QtArvBuffer::imageRegion() const {
    return partRegion(0);
}

QSize QtArvBuffer::imageSize() const {
    return partSize(0);
}

QPoint QtArvBuffer::imageOffset() const {
    return partOffset(0);
}

QPoint QtArvBuffer::imagePadding() const {
    return partPadding(0);
}

QImage QtArvBuffer::toQImage() const {
    QSize sz = imageSize();
    const uchar* ptr = static_cast<const uchar*>(imageData());
    if (!ptr || sz.isEmpty()) return QImage();
    return QImage(ptr, sz.width(), sz.height(), QImage::Format_Grayscale8).copy();
}