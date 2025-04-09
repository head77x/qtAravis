// QtArvEnumEntryNode.cpp - Implementation of EnumEntry node
#include "QtArvEnumEntryNode.h"
#include <QDebug>

QtArvEnumEntryNode::QtArvEnumEntryNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvEnumEntryNode] Constructed:" << name();
}

QtArvEnumEntryNode::~QtArvEnumEntryNode() {
    qDebug() << "[QtArvEnumEntryNode] Destroyed:" << name();
}

qint64 QtArvEnumEntryNode::getValue(bool* ok) const {
    QDomElement valueElem = element.firstChildElement("Value");
    if (!valueElem.isNull()) {
        bool valid = false;
        qint64 v = valueElem.text().toLongLong(&valid);
        if (ok) *ok = valid;
        return v;
    }
    if (ok) *ok = false;
    return 0;
}

QVariant QtArvEnumEntryNode::read() const {
    bool ok;
    qint64 val = getValue(&ok);
    return ok ? QVariant(val) : QVariant();
}

bool QtArvEnumEntryNode::write(const QVariant& value) {
    Q_UNUSED(value);
    // EnumEntry는 일반적으로 쓰기 불가
    qWarning() << "[QtArvEnumEntryNode] Write not supported for EnumEntry node:" << name();
    return false;
}
