#include "QtArvGcFloatSwissKnife.h"
#include <QDebug>

QtArvGcFloatSwissKnife::QtArvGcFloatSwissKnife() {}
QtArvGcFloatSwissKnife::~QtArvGcFloatSwissKnife() {}

QString QtArvGcFloatSwissKnife::nodeName() const {
    return "FloatSwissKnife";
}

double QtArvGcFloatSwissKnife::floatValue() const {
    return evaluate();
}

void QtArvGcFloatSwissKnife::setFloatValue(double) {
    qWarning() << "[QtArvGcFloatSwissKnife] Attempt to set read-only SwissKnife value.";
}

QString QtArvGcFloatSwissKnife::displayNotation() const {
    for (auto* node : m_variables + m_constants + m_expressions) {
        if (node->propertyType() == QtArvGcPropertyNodeType::DisplayNotation)
            return node->toString();
    }
    return "Default";
}

int QtArvGcFloatSwissKnife::displayPrecision() const {
    for (auto* node : m_variables + m_constants + m_expressions) {
        if (node->propertyType() == QtArvGcPropertyNodeType::DisplayPrecision)
            return node->toInt();
    }
    return 2;
}
