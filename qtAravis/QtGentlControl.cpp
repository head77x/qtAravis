// QtGentlControl.cpp - Implementation of GenTL Control API wrapper
#include "QtGentlControl.h"
#include <QDebug>

QtGentlControl::QtGentlControl(QObject* parent)
    : QObject(parent) {
    qDebug() << "[QtGentlControl] Initialized";
}

QtGentlControl::~QtGentlControl() {
    qDebug() << "[QtGentlControl] Destroyed";
}

QString QtGentlControl::getInfo(const QString& key) {
    qWarning() << "[GC] getInfo not implemented for key:" << key;
    return "AravisStubInfo";
}

QString QtGentlControl::getLastError() {
    qWarning() << "[GC] getLastError not implemented";
    return "No error";
}

QByteArray QtGentlControl::readPort(quint64 address, int length) {
    qWarning() << "[GC] readPort not implemented: addr=" << address << ", len=" << length;
    return QByteArray(length, '\0');
}

bool QtGentlControl::writePort(quint64 address, const QByteArray& data) {
    qWarning() << "[GC] writePort not implemented: addr=" << address << ", dataLen=" << data.size();
    return false;
}

QString QtGentlControl::getPortURL() {
    qWarning() << "[GC] getPortURL not implemented";
    return "Local:aravis.xml";
}

QVariant QtGentlControl::getPortInfo(int infoType) {
    qWarning() << "[GC] getPortInfo not implemented. InfoType=" << infoType;
    return QVariant();
}

int QtGentlControl::getNumPortURLs() {
    qWarning() << "[GC] getNumPortURLs not implemented";
    return 1;
}

QVariant QtGentlControl::getPortURLInfo(int index, int infoType) {
    Q_UNUSED(index);
    Q_UNUSED(infoType);
    qWarning() << "[GC] getPortURLInfo not implemented";
    return QVariant();
}

bool QtGentlControl::registerEvent(int eventType) {
    Q_UNUSED(eventType);
    qWarning() << "[GC] registerEvent not implemented";
    return false;
}

bool QtGentlControl::unregisterEvent(int eventType) {
    Q_UNUSED(eventType);
    qWarning() << "[GC] unregisterEvent not implemented";
    return false;
}

QByteArray QtGentlControl::readPortStacked() {
    qWarning() << "[GC] readPortStacked not implemented";
    return QByteArray();
}

bool QtGentlControl::writePortStacked() {
    qWarning() << "[GC] writePortStacked not implemented";
    return false;
}
