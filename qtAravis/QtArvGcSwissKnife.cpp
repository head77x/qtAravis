// QtArvGcSwissKnife.cpp - Shared base logic for SwissKnife-type nodes
#include "QtArvGcSwissKnife.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGenicam.h"

QtArvGcSwissKnife::QtArvGcSwissKnife() {}
QtArvGcSwissKnife::~QtArvGcSwissKnife() {}

QString QtArvGcSwissKnife::unit() const {
    return m_unit ? m_unit->toString() : QString();
}

QString QtArvGcSwissKnife::representation() const {
    return m_representation ? m_representation->toString() : QString();
}

double QtArvGcSwissKnife::evaluate() const {
    updateEvaluator();
    return m_evaluator.evaluate();
}

void QtArvGcSwissKnife::updateEvaluator() const {
    if (m_evalReady) return;

    m_evaluator.clear();

    for (auto* constant : m_constants) {
        m_evaluator.addConstant(constant->getAttribute("Name"), constant->toDouble());
    }

    for (auto* variable : m_variables) {
        auto* node = variable->linkedNode();
        if (node) {
            auto* prop = dynamic_cast<QtArvGcPropertyNode*>(node);
            if (prop) {
                m_evaluator.addVariable(variable->getAttribute("Name"), prop->toDouble());
            }
        }
    }

    if (m_formulaNode) {
        m_evaluator.setExpression(m_formulaNode->toString());
    }
    else if (!m_expressions.isEmpty()) {
        m_evaluator.setExpression(m_expressions.first()->toString());
    }

    m_evalReady = true;
}
