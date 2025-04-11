// QtArvUvStream.h - Header for USB3Vision streaming handler
#pragma once

#include <QObject>
#include <QByteArray>
#include <QFuture>
#include <QtConcurrent>

class QtArvUvStream : public QObject {
    Q_OBJECT
public:
    explicit QtArvUvStream(QObject* parent = nullptr);
    ~QtArvUvStream();

    void start();
    void stop();

signals:
    void packetReceived(const QByteArray& packet);

private:
    bool m_streaming;
    QFuture<void> m_thread;

    QByteArray createDummyPacket() const;
};
