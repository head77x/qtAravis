#pragma once
// QtArvBuffer.h - C++ 리팩토링 헤더
#pragma once

#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QSharedPointer>
#include <QImage>
#include <QVector>

enum class QtArvBufferStatus {
    Unknown,
    Success,
    Cleared,
    Incomplete,
    Corrupted
};

enum class QtArvPayloadType {
    Unknown,
    Image,
    ExtendedChunk,
    Multipart,
    GenDC
};

struct QtArvBufferPartInfo {
    int componentId = 0;
    int dataOffset = 0;
    int size = 0;
    int width = 0;
    int height = 0;
    int xOffset = 0;
    int yOffset = 0;
    int xPadding = 0;
    int yPadding = 0;
    quint64 pixelFormat = 0;
    int dataType = 0;
};

class QtArvBuffer {
public:
    QtArvBuffer(size_t size, void* preallocated = nullptr);
    ~QtArvBuffer();

    const void* data(size_t* sizeOut = nullptr) const;
    void* data();

    bool hasChunks() const;
    const void* getChunkData(quint64 chunkId, size_t* sizeOut = nullptr) const;

    bool hasGenDC() const;
    const void* getGenDCData(size_t* sizeOut = nullptr) const;
    const void* getGenDCDescriptor(size_t* sizeOut = nullptr) const;

    const void* userData() const;

    QtArvBufferStatus status() const;
    QtArvPayloadType payloadType() const;

    quint64 timestamp() const;
    void setTimestamp(quint64 ts);

    quint64 systemTimestamp() const;
    void setSystemTimestamp(quint64 ts);

    quint64 frameId() const;
    void setFrameId(quint64 id);

    int partCount() const;
    int findComponent(int componentId) const;
    const void* partData(int partId, size_t* sizeOut = nullptr) const;
    quint64 partPixelFormat(int partId) const;
    QRect partRegion(int partId) const;
    QSize partSize(int partId) const;
    QPoint partOffset(int partId) const;
    QPoint partPadding(int partId) const;

    // Convenience for single image part (0)
    const void* imageData(size_t* sizeOut = nullptr) const;
    quint64 imagePixelFormat() const;
    QRect imageRegion() const;
    QSize imageSize() const;
    QPoint imageOffset() const;
    QPoint imagePadding() const;

    QImage toQImage() const;

private:
    QByteArray byteBuffer;
    QVector<QtArvBufferPartInfo> parts;

    QtArvBufferStatus bufferStatus = QtArvBufferStatus::Cleared;
    QtArvPayloadType payload = QtArvPayloadType::Unknown;

    quint64 timeStamp = 0;
    quint64 sysTimeStamp = 0;
    quint64 frameNumber = 0;

    bool chunkEnabled = false;
    bool gendcEnabled = false;

    int gendcOffset = 0;
    int gendcSize = 0;
    int gendcDescSize = 0;

    void* userPtr = nullptr;
};