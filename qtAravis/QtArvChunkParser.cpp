// QtArvChunkParser.cpp - Implementation of QtArvChunkParser
#include "QtArvChunkParser.h"
#include "QtArvGenicam.h"
#include "QtArvBuffer.h"
#include "QtArvNode.h"
#include <QDebug>

QtArvChunkParser::QtArvChunkParser(QSharedPointer<QtArvGenicam> genicam, QObject* parent)
    : QObject(parent), genicam(genicam) {
    qDebug() << "[QtArvChunkParser] Initialized.";
}

QtArvChunkParser::~QtArvChunkParser() {
    qDebug() << "[QtArvChunkParser] Destroyed.";
}

bool QtArvChunkParser::getBooleanValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok) const {
    Q_UNUSED(buffer)
        if (!genicam) return false;
    QtArvNode* node = genicam->getNode(chunkName);
    if (node) {
        QVariant value = node->read();
        if (ok) *ok = value.isValid();
        return value.toBool();
    }
    if (ok) *ok = false;
    return false;
}

qint64 QtArvChunkParser::getIntegerValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok) const {
    Q_UNUSED(buffer)
        if (!genicam) return 0;
    QtArvNode* node = genicam->getNode(chunkName);
    if (node) {
        QVariant value = node->read();
        if (ok) *ok = value.isValid();
        return value.toLongLong();
    }
    if (ok) *ok = false;
    return 0;
}

double QtArvChunkParser::getFloatValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok) const {
    Q_UNUSED(buffer)
        if (!genicam) return 0.0;
    QtArvNode* node = genicam->getNode(chunkName);
    if (node) {
        QVariant value = node->read();
        if (ok) *ok = value.isValid();
        return value.toDouble();
    }
    if (ok) *ok = false;
    return 0.0;
}

QString QtArvChunkParser::getStringValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok) const {
    Q_UNUSED(buffer)
        if (!genicam) return QString();
    QtArvNode* node = genicam->getNode(chunkName);
    if (node) {
        QVariant value = node->read();
        if (ok) *ok = value.isValid();
        return value.toString();
    }
    if (ok) *ok = false;
    return QString();
}