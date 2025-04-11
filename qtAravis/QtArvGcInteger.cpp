// QtArvGcInteger.cpp
#include "QtArvGcInteger.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGenicam.h"

QtArvGcInteger::QtArvGcInteger() {}
QtArvGcInteger::~QtArvGcInteger() {}

QString QtArvGcInteger::nodeName() const {
    return "Integer";
}

qint64 QtArvGcInteger::intValue() const {
    return m_value ? m_value->toInt() : 0;
}

void QtArvGcInteger::setIntValue(qint64 value) {
    if (m_value) m_value->setInt(value);
}

QList<QtArvGcFeatureNode*> QtArvGcInteger::selectedFeatures() const {
    QList<QtArvGcFeatureNode*> selected;
    for (auto* prop : m_selecteds) {
        auto* linked = dynamic_cast<QtArvGcFeatureNode*>(prop->linkedNode());
        if (linked) selected.append(linked);
    }
    return selected;
}
