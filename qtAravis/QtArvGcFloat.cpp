#include "QtArvGcFloat.h"
#include "QtArvGcPropertyNode.h"

QtArvGcFloat::QtArvGcFloat() {}
QtArvGcFloat::~QtArvGcFloat() {}

QString QtArvGcFloat::nodeName() const {
    return "Float";
}

bool QtArvGcFloat::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::Value:
    case QtArvGcPropertyNodeType::PValue:
        const_cast<QtArvGcFloat*>(this)->m_value = prop;
        return false;
    case QtArvGcPropertyNodeType::Min:
        const_cast<QtArvGcFloat*>(this)->m_min = prop;
        return false;
    case QtArvGcPropertyNodeType::Max:
        const_cast<QtArvGcFloat*>(this)->m_max = prop;
        return false;
    case QtArvGcPropertyNodeType::Inc:
        const_cast<QtArvGcFloat*>(this)->m_inc = prop;
        return false;
    case QtArvGcPropertyNodeType::Unit:
        const_cast<QtArvGcFloat*>(this)->m_unit = prop;
        return false;
    case QtArvGcPropertyNodeType::Representation:
        const_cast<QtArvGcFloat*>(this)->m_representation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayNotation:
        const_cast<QtArvGcFloat*>(this)->m_displayNotation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayPrecision:
        const_cast<QtArvGcFloat*>(this)->m_displayPrecision = prop;
        return false;
    default:
        return true;
    }
}

double QtArvGcFloat::floatValue() const {
    return m_value ? m_value->toDouble() : 0.0;
}

void QtArvGcFloat::setFloatValue(double value) {
    if (m_value) m_value->setDouble(value);
}

double QtArvGcFloat::floatMin() const {
    return m_min ? m_min->toDouble() : 0.0;
}

double QtArvGcFloat::floatMax() const {
    return m_max ? m_max->toDouble() : 0.0;
}

double QtArvGcFloat::floatIncrement() const {
    return m_inc ? m_inc->toDouble() : 0.0;
}

QString QtArvGcFloat::unit() const {
    return m_unit ? m_unit->toString() : QString();
}

QString QtArvGcFloat::representation() const {
    return m_representation ? m_representation->toString() : QString();
}

QString QtArvGcFloat::displayNotation() const {
    return m_displayNotation ? m_displayNotation->toString() : QString();
}

int QtArvGcFloat::displayPrecision() const {
    return m_displayPrecision ? m_displayPrecision->toInt() : -1;
}
