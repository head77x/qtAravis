// QtArvWakeup.h - Portable wakeup signaling mechanism
#pragma once

#include <QObject>
#include <QSocketNotifier>
#include <QMutex>
#include <QByteArray>
#include <unistd.h>

class QtArvWakeup : public QObject {
    Q_OBJECT

public:
    QtArvWakeup(QObject* parent = nullptr);
    ~QtArvWakeup();

    int pollFd() const;
    void signal();
    void acknowledge();

signals:
    void triggered();

private slots:
    void onActivated();

private:
    int m_readFd;
    int m_writeFd;
    QSocketNotifier* m_notifier;
};
