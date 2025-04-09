// QtArvEvaluator.cpp - GenICam math expression evaluator (ported from Aravis)
#include "QtArvEvaluator.h"
#include <QtMath>
#include <QStack>
#include <QDebug>

QtArvEvaluator::QtArvEvaluator(QObject* parent)
    : QObject(parent) {
    m_variables["PI"] = M_PI;
    m_variables["E"] = M_E;
}

QtArvEvaluator::~QtArvEvaluator() {}

void QtArvEvaluator::setExpression(const QString& expression) {
    if (m_expression != expression) {
        m_expression = expression;
        m_parsed = false;
    }
}

QString QtArvEvaluator::getExpression() const {
    return m_expression;
}

void QtArvEvaluator::setConstant(const QString& name, const QString& expression) {
    m_constants.insert(name, expression);
    m_parsed = false;
}

QString QtArvEvaluator::getConstant(const QString& name) const {
    return m_constants.value(name);
}

void QtArvEvaluator::setSubExpression(const QString& name, const QString& expression) {
    m_subExpressions.insert(name, expression);
    m_parsed = false;
}

QString QtArvEvaluator::getSubExpression(const QString& name) const {
    return m_subExpressions.value(name);
}

void QtArvEvaluator::setVariable(const QString& name, double value) {
    m_variables.insert(name, value);
    m_parsed = false;
}

void QtArvEvaluator::setVariable(const QString& name, qint64 value) {
    m_variables.insert(name, static_cast<qint64>(value));
    m_parsed = false;
}

double QtArvEvaluator::evaluateAsDouble(bool* ok) const {
    QVariant result;
    if (evaluate(&result, true)) {
        if (ok) *ok = true;
        return result.toDouble();
    }
    if (ok) *ok = false;
    return 0.0;
}

qint64 QtArvEvaluator::evaluateAsInt64(bool* ok) const {
    QVariant result;
    if (evaluate(&result, false)) {
        if (ok) *ok = true;
        return result.toLongLong();
    }
    if (ok) *ok = false;
    return 0;
}

bool QtArvEvaluator::parse() const {
    // TODO: Parse m_expression to RPN and fill m_rpnStack
    m_rpnStack.clear();
    // For demonstration, assume the expression is just a numeric literal:
    bool ok = false;
    double val = m_expression.toDouble(&ok);
    if (ok) {
        m_rpnStack.append(val);
        return true;
    }
    return false;
}

bool QtArvEvaluator::evaluate(QVariant* result, bool asDouble) const {
    if (!m_parsed) {
        if (!parse()) return false;
        m_parsed = true;
    }
    if (m_rpnStack.isEmpty()) return false;

    QVariant top = m_rpnStack.last();
    if (asDouble) {
        *result = top.toDouble();
    }
    else {
        *result = top.toLongLong();
    }
    return true;
}
