// QtArvIntegerNode.cpp - Implementation for QtArvIntegerNode
#include "QtArvIntegerNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvIntegerNode::QtArvIntegerNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvIntegerNode] Constructed:" << name();
}

QtArvIntegerNode::~QtArvIntegerNode() {
    qDebug() << "[QtArvIntegerNode] Destroyed:" << name();
}

QVariant QtArvIntegerNode::read() const {
    // TODO: 실제 디바이스 레지스터에서 읽기 구현
    qint64 dummyValue = 42;
    return QVariant(dummyValue);
}

bool QtArvIntegerNode::write(const QVariant& value) {
    if (!value.canConvert<qint64>()) {
        qWarning() << "[QtArvIntegerNode] Invalid write type for node:" << name();
        return false;
    }
    qint64 val = value.toLongLong();
    qDebug() << "[QtArvIntegerNode] Write to" << name() << ":" << val;
    // TODO: 실제 디바이스에 레지스터 쓰기 구현
    return true;
}

qint64 QtArvIntegerNode::minimum(bool* ok) const {
    return readIntegerElement("Min", ok);
}

qint64 QtArvIntegerNode::maximum(bool* ok) const {
    return readIntegerElement("Max", ok);
}

qint64 QtArvIntegerNode::increment(bool* ok) const {
    return readIntegerElement("Inc", ok);
}

QString QtArvIntegerNode::unit() const {
    return element.attribute("Unit");
}

qint64 QtArvIntegerNode::readIntegerElement(const QString& tagName, bool* ok) const {
    QDomElement child = element.firstChildElement(tagName);
    if (!child.isNull()) {
        bool valid = false;
        qint64 val = child.text().toLongLong(&valid);
        if (ok) *ok = valid;
        return val;
    }
    if (ok) *ok = false;
    return 0;
}
