// QtGentlDataStream.cpp - Stub implementation of GenTL DataStream abstraction
#include "QtGentlDataStream.h"
#include <QDebug>

QtGentlDataStream::QtGentlDataStream(QObject* parent)
    : QObject(parent) {
    qDebug() << "[QtGentlDataStream] Initialized";
}

QtGentlDataStream::~QtGentlDataStream() {
    qDebug() << "[QtGentlDataStream] Destroyed";
}

bool QtGentlDataStream::startAcquisition() {
    qWarning() << "[DS] startAcquisition not implemented";
    return false;
}

void QtGentlDataStream::stopAcquisition() {
    qWarning() << "[DS] stopAcquisition not implemented";
}

bool QtGentlDataStream::queueBuffer(int index) {
    qWarning() << "[DS] queueBuffer not implemented";
    return false;
}

bool QtGentlDataStream::flushQueue() {
    qWarning() << "[DS] flushQueue not implemented";
    return false;
}
