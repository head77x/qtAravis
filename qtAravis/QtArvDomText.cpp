// QtArvDomText.cpp - Implementation of DOM text node
#include "QtArvDomText.h"

QtArvDomText::QtArvDomText(const QString& data, QObject* parent)
    : QtArvDomCharacterData(parent) {
    setData(data);
}

QtArvDomText::~QtArvDomText() {}

QString QtArvDomText::nodeName() const {
    return "#text";
}

QString QtArvDomText::nodeValue() const {
    return data();
}

void QtArvDomText::setNodeValue(const QString& value) {
    setData(value);
}
