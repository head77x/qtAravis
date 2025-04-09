// QtArvDomElement.cpp - Element node implementation
#include "QtArvDomElement.h"
#include <QDebug>

QtArvDomElement::QtArvDomElement(const QString& tagName, QObject* parent)
    : QtArvDomNode(parent), m_tagName(tagName) {
}

QtArvDomElement::~QtArvDomElement() {}

QString QtArvDomElement::nodeName() const {
    return m_tagName;
}

QString QtArvDomElement::nodeValue() const {
    return QString(); // Element nodes typically don't have a value
}

void QtArvDomElement::setNodeValue(const QString& value) {
    Q_UNUSED(value);
    // No-op for element node
}

QString QtArvDomElement::getAttribute(const QString& name) const {
    return m_attributes.value(name, QString());
}

void QtArvDomElement::setAttribute(const QString& name, const QString& value) {
    m_attributes[name] = value;
    notifyDomChanged();
}
