// QtArvBooleanNode.cpp - Implementation for QtArvBooleanNode
#include "QtArvBooleanNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvBooleanNode::QtArvBooleanNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvBooleanNode] Constructed:" << name();
}

QtArvBooleanNode::~QtArvBooleanNode() {
    qDebug() << "[QtArvBooleanNode] Destroyed:" << name();
}

QVariant QtArvBooleanNode::read() const {
    QDomElement valueElem = element.firstChildElement("Value");
    if (valueElem.isNull()) return QVariant(false);

    qint64 value = valueElem.text().toLongLong();
    return QVariant(value == onValue());
}

bool QtArvBooleanNode::write(const QVariant& value) {
    if (!value.canConvert<bool>()) {
        qWarning() << "[QtArvBooleanNode] Invalid write type for node:" << name();
        return false;
    }
    bool v = value.toBool();
    qint64 toWrite = v ? onValue() : offValue();

    // TODO: 실제 레지스터 쓰기 구현
    qDebug() << "[QtArvBooleanNode] Write to" << name() << ":" << toWrite;
    return true;
}

qint64 QtArvBooleanNode::onValue() const {
    QDomElement onElem = element.firstChildElement("OnValue");
    if (!onElem.isNull()) {
        return onElem.text().toLongLong();
    }
    return 1; // default fallback
}

qint64 QtArvBooleanNode::offValue() const {
    QDomElement offElem = element.firstChildElement("OffValue");
    if (!offElem.isNull()) {
        return offElem.text().toLongLong();
    }
    return 0; // default fallback
}
