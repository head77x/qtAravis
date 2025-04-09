#pragma once
// QtArvStream.h - C++ wrapper for Aravis stream
#pragma once

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QSharedPointer>
#include <QVector>
#include <QByteArray>
#include <functional>

class QtArvBuffer;
class QtArvDevice;

class QtArvStream : public QObject {
    Q_OBJECT

public:
    explicit QtArvStream(QtArvDevice* device, std::function<void()> callback = nullptr, QObject* parent = nullptr);
    ~QtArvStream();

    void pushBuffer(QSharedPointer<QtArvBuffer> buffer);
    QSharedPointer<QtArvBuffer> popBuffer();
    QSharedPointer<QtArvBuffer> tryPopBuffer();
    QSharedPointer<QtArvBuffer> timeoutPopBuffer(qint64 timeoutMs);

    void pushOutputBuffer(QSharedPointer<QtArvBuffer> buffer);
    QSharedPointer<QtArvBuffer> popInputBuffer();
    QSharedPointer<QtArvBuffer> timeoutPopInputBuffer(qint64 timeoutMs);

    void getBufferStatistics(int* input, int* output, int* filling);

    bool startAcquisition();
    bool stopAcquisition();

    void setEmitSignals(bool enabled);
    bool getEmitSignals() const;

    void declareInfo(const QString& name, QVariant value);
    int getInfoCount() const;
    QString getInfoName(int index) const;
    QVariant getInfoValue(int index) const;
    QVariant getInfoValueByName(const QString& name) const;

signals:
    void newBufferAvailable();

private:
    QQueue<QSharedPointer<QtArvBuffer>> inputQueue;
    QQueue<QSharedPointer<QtArvBuffer>> outputQueue;

    mutable QMutex mutex;
    QWaitCondition bufferAvailable;

    QtArvDevice* device;
    std::function<void()> callback;

    int fillingCount = 0;
    bool emitSignal = false;

    struct StreamInfo {
        QString name;
        QVariant value;
    };
    QVector<StreamInfo> streamInfo;
};