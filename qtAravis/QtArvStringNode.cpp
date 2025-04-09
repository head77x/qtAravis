// QtArvStringNode.cpp - Implementation for QtArvStringNode
#include "QtArvStringNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvStringNode::QtArvStringNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvStringNode] Constructed:" << name();
}

QtArvStringNode::~QtArvStringNode() {
    qDebug() << "[QtArvStringNode] Destroyed:" << name();
}

QVariant QtArvStringNode::read() const {
    QDomElement valueElem = element.firstChildElement("Value");
    if (valueElem.isNull()) return QVariant();

    QString value = valueElem.text().trimmed();
    return QVariant(value);
}

bool QtArvStringNode::write(const QVariant& value) {
    if (!value.canConvert<QString>()) {
        qWarning() << "[QtArvStringNode] Invalid write type for node:" << name();
        return false;
    }
    QString str = value.toString();
    qDebug() << "[QtArvStringNode] Write to" << name() << ":" << str;
    // TODO: 실제 디바이스에 문자열 쓰기 구현 필요
    return true;
}

int QtArvStringNode::maxLength(bool* ok) const {
    QDomElement maxLenElem = element.firstChildElement("MaxLength");
    if (!maxLenElem.isNull()) {
        bool valid = false;
        int len = maxLenElem.text().toInt(&valid);
        if (ok) *ok = valid;
        return len;
    }
    if (ok) *ok = false;
    return 0;
}
