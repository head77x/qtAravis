#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class QtArvGvStream : public QObject {
    Q_OBJECT

public:
    QtArvGvStream();
    ~QtArvGvStream();

    bool open(const QString& ip, quint16 port);
    void close();
    bool sendCommand(const QByteArray& packet);

signals:
    void packetReceived(const QByteArray& packet);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket* _socket;
    QHostAddress _address;
    quint16 _port;
};
