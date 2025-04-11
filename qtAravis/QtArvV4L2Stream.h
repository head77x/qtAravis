// QtArvV4L2Stream.h - Header for V4L2 streaming class
#pragma once

#include <QObject>
#include <QFuture>
#include <QtConcurrent>

class QtArvV4L2Stream : public QObject {
    Q_OBJECT

public:
    explicit QtArvV4L2Stream(QObject* parent = nullptr);
    ~QtArvV4L2Stream();

    void start();
    void stop();
    bool isRunning() const;

signals:
    void newBufferReady();
    void streamStopped();

private:
    bool m_running;
    QFuture<void> m_thread;
};
