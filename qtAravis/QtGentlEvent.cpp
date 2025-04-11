// QtGentlEvent.cpp - Stub for GenTL Event object
#include "QtGentlEvent.h"
#include <QDebug>

QtGentlEvent::QtGentlEvent(QObject* parent)
    : QObject(parent) {
    qDebug() << "[QtGentlEvent] Initialized";
}

QtGentlEvent::~QtGentlEvent() {
    qDebug() << "[QtGentlEvent] Destroyed";
}

QByteArray QtGentlEvent::getData(int timeoutMs) {
    qWarning() << "[Event] getData not implemented";
    Q_UNUSED(timeoutMs);
    return QByteArray();
}

QVariant QtGentlEvent::getDataInfo(int infoType) {
    qWarning() << "[Event] getDataInfo not implemented";
    Q_UNUSED(infoType);
    return QVariant();
}

QVariant QtGentlEvent::getInfo(int infoCmd) {
    qWarning() << "[Event] getInfo not implemented";
    Q_UNUSED(infoCmd);
    return QVariant();
}

bool QtGentlEvent::flush() {
    qWarning() << "[Event] flush not implemented";
    return false;
}

bool QtGentlEvent::kill() {
    qWarning() << "[Event] kill not implemented";
    return false;
}
