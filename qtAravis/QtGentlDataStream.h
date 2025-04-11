// QtGentlDataStream.h - Interface for GenTL DataStream abstraction
#pragma once

#include <QObject>

class QtGentlDataStream : public QObject {
    Q_OBJECT

public:
    explicit QtGentlDataStream(QObject* parent = nullptr);
    ~QtGentlDataStream();

    // Placeholder functions
    bool startAcquisition();
    void stopAcquisition();
    bool queueBuffer(int index);
    bool flushQueue();

signals:
    void bufferReady(int index);
};
