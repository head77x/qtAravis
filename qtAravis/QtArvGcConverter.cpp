// QtArvGcConverter.cpp - GenICam abstract converter implementation
#include "QtArvGcConverter.h"
#include "QtArvGcPropertyNode.h"
#include <QDebug>

QtArvGcConverter::QtArvGcConverter() {
    m_evalTo.reset(new QtArvEvaluator());
    m_evalFrom.reset(new QtArvEvaluator());
}

QtArvGcConverter::~QtArvGcConverter() {}

QString QtArvGcConverter::nodeName() const {
    return "Converter";
}

bool QtArvGcConverter::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::Value:
    case QtArvGcPropertyNodeType::PValue:
        const_cast<QtArvGcConverter*>(this)->m_value = prop;
        return false;
    case QtArvGcPropertyNodeType::FormulaTo:
        const_cast<QtArvGcConverter*>(this)->m_formulaTo = prop;
        return false;
    case QtArvGcPropertyNodeType::FormulaFrom:
        const_cast<QtArvGcConverter*>(this)->m_formulaFrom = prop;
        return false;
    case QtArvGcPropertyNodeType::Variable:
        const_cast<QtArvGcConverter*>(this)->m_variables.append(prop);
        return false;
    case QtArvGcPropertyNodeType::Constant:
        const_cast<QtArvGcConverter*>(this)->m_constants.append(prop);
        return false;
    case QtArvGcPropertyNodeType::Expression:
        const_cast<QtArvGcConverter*>(this)->m_expressions.append(prop);
        return false;
    case QtArvGcPropertyNodeType::Unit:
        const_cast<QtArvGcConverter*>(this)->m_unit = prop;
        return false;
    case QtArvGcPropertyNodeType::Representation:
        const_cast<QtArvGcConverter*>(this)->m_representation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayNotation:
        const_cast<QtArvGcConverter*>(this)->m_displayNotation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayPrecision:
        const_cast<QtArvGcConverter*>(this)->m_displayPrecision = prop;
        return false;
    case QtArvGcPropertyNodeType::IsLinear:
        const_cast<QtArvGcConverter*>(this)->m_isLinear = prop;
        return false;
    case QtArvGcPropertyNodeType::Slope:
        const_cast<QtArvGcConverter*>(this)->m_slope = prop;
        return false;
    default:
        return true;
    }
}

QtArvGcFeatureNode* QtArvGcConverter::getLinkedFeature() const {
    return dynamic_cast<QtArvGcFeatureNode*>(m_value ? m_value->linkedNode() : nullptr);
}

bool QtArvGcConverter::updateFromVariables() const {
    if (!m_evalTo || !m_formulaTo) return false;

    m_evalTo->setExpression(m_formulaTo->toString());
    for (auto* var : m_variables)
        m_evalTo->setVariable(var->name(), var->toDouble());
    for (auto* c : m_constants)
        m_evalTo->setConstant(c->name(), c->toString());

    return true;
}

void QtArvGcConverter::updateToVariables(double fromValue) const {
    for (auto* var : m_variables) {
        if (var->name() == "Value") {
            var->setDouble(fromValue);
            break;
        }
    }
}

double QtArvGcConverter::convertToDouble() const {
    if (!m_value || !m_formulaTo) return m_value ? m_value->toDouble() : 0.0;

    if (!updateFromVariables()) return 0.0;

    double val = m_value->toDouble();
    updateToVariables(val);

    bool ok = false;
    double result = m_evalTo->evaluateAsDouble(&ok);
    return ok ? result : val;
}

qint64 QtArvGcConverter::convertToInt64() const {
    return static_cast<qint64>(convertToDouble());
}

void QtArvGcConverter::convertFromDouble(double value) {
    if (!m_value || !m_formulaFrom || !m_evalFrom) return;

    m_evalFrom->setExpression(m_formulaFrom->toString());
    updateToVariables(value);

    for (auto* var : m_variables)
        m_evalFrom->setVariable(var->name(), var->toDouble());
    for (auto* c : m_constants)
        m_evalFrom->setConstant(c->name(), c->toString());

    bool ok = false;
    double result = m_evalFrom->evaluateAsDouble(&ok);
    if (ok)
        m_value->setDouble(result);
}

void QtArvGcConverter::convertFromInt64(qint64 value) {
    convertFromDouble(static_cast<double>(value));
}

QString QtArvGcConverter::unit() const {
    return m_unit ? m_unit->toString() : QString();
}

QString QtArvGcConverter::representation() const {
    return m_representation ? m_representation->toString() : QString();
}

QString QtArvGcConverter::displayNotation() const {
    return m_displayNotation ? m_displayNotation->toString() : QString();
}

int QtArvGcConverter::displayPrecision() const {
    return m_displayPrecision ? m_displayPrecision->toInt() : -1;
}
