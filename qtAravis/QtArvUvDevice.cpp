// QtArvUvDevice.cpp - Qt C++ port of arvuvdevice.c
#include "QtArvUvDevice.h"
#include "QtArvUvcp.h"
#include <QDebug>

QtArvUvDevice::QtArvUvDevice(QObject* parent)
    : QObject(parent) {
}

QtArvUvDevice::~QtArvUvDevice() {
    close();
}

bool QtArvUvDevice::open(const QString& devicePath) {
    this->devicePath = devicePath;
    isOpen = true;  // 실제 USB 열기 구현 필요
    qDebug() << "[QtArvUvDevice] Opened:" << devicePath;
    return isOpen;
}

void QtArvUvDevice::close() {
    if (isOpen) {
        isOpen = false;
        qDebug() << "[QtArvUvDevice] Closed:" << devicePath;
    }
}

bool QtArvUvDevice::readMemory(quint64 address, QByteArray& outData, QString& error) {
    if (!isOpen) {
        error = "Device not open";
        return false;
    }

    QByteArray cmd = QtArvUvcp::newReadMemoryCmd(address, 1024, 1); // packetId = 1
    QByteArray response;
    if (!sendControlTransfer(cmd, response, error)) {
        return false;
    }

    outData = response;
    return true;
}

bool QtArvUvDevice::writeMemory(quint64 address, const QByteArray& data, QString& error) {
    if (!isOpen) {
        error = "Device not open";
        return false;
    }

    QByteArray cmd = QtArvUvcp::newWriteMemoryCmd(address, data, 2); // packetId = 2
    QByteArray response;
    if (!sendControlTransfer(cmd, response, error)) {
        return false;
    }

    return true;
}

bool QtArvUvDevice::sendControlTransfer(const QByteArray& request, QByteArray& response, QString& error) {
    // FIXME: 실제 USB 전송 로직 구현 필요 (libusb 또는 Windows API)
    qDebug() << "[QtArvUvDevice] SendControlTransfer (stub)";
    response = QByteArray("DUMMY_RESPONSE");
    return true;
}

QString QtArvUvDevice::getDevicePath() const {
    return devicePath;
}
