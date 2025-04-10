// QtArvGcString.cpp - GenICam String node implementation
#include "QtArvGcString.h"
#include "QtArvGcPropertyNode.h"

QtArvGcString::QtArvGcString() {}
QtArvGcString::~QtArvGcString() {}

QString QtArvGcString::nodeName() const {
    return "String";
}

QString QtArvGcString::stringValue() const {
    return m_value ? m_value->toString() : QString();
}

void QtArvGcString::setStringValue(const QString& value) {
    if (m_value)
        m_value->setString(value);
}

int QtArvGcString::maxLength() const {
    if (!m_maxLength)
        return 0;
    return m_maxLength->toInt();
}
