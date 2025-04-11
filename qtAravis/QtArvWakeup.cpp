// QtArvWakeup.cpp - Implementation of Qt-compatible wakeup mechanism
#include "QtArvWakeup.h"
#include <QDebug>
#include <fcntl.h>
#include <errno.h>

QtArvWakeup::QtArvWakeup(QObject* parent)
    : QObject(parent), m_readFd(-1), m_writeFd(-1), m_notifier(nullptr) {
    int fds[2];
    if (pipe(fds) != 0) {
        qFatal("[QtArvWakeup] Failed to create pipe");
        return;
    }

    m_readFd = fds[0];
    m_writeFd = fds[1];

    fcntl(m_readFd, F_SETFL, O_NONBLOCK);
    fcntl(m_writeFd, F_SETFL, O_NONBLOCK);

    m_notifier = new QSocketNotifier(m_readFd, QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &QtArvWakeup::onActivated);
}

QtArvWakeup::~QtArvWakeup() {
    if (m_notifier) delete m_notifier;
    if (m_readFd >= 0) close(m_readFd);
    if (m_writeFd >= 0) close(m_writeFd);
}

int QtArvWakeup::pollFd() const {
    return m_readFd;
}

void QtArvWakeup::signal() {
    char one = 1;
    if (write(m_writeFd, &one, sizeof(one)) == -1 && errno != EAGAIN) {
        qWarning("[QtArvWakeup] Failed to signal: %s", strerror(errno));
    }
}

void QtArvWakeup::acknowledge() {
    char buffer[16];
    while (read(m_readFd, buffer, sizeof(buffer)) > 0) {}
}

void QtArvWakeup::onActivated() {
    acknowledge();
    emit triggered();
}
