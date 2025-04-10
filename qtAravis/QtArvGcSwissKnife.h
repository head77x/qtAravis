#pragma once

#include "QtArvGcFeatureNode.h"
#include "QtArvEvaluator.h"
#include <QList>

class QtArvGcPropertyNode;

class QtArvGcSwissKnife : public QtArvGcFeatureNode {
public:
    QtArvGcSwissKnife();
    ~QtArvGcSwissKnife();

    QString nodeName() const override = 0;

    double evaluate() const;
    QString unit() const;
    QString representation() const;

protected:
    void updateEvaluator() const;

    QList<QtArvGcPropertyNode*> m_variables;
    QList<QtArvGcPropertyNode*> m_constants;
    QList<QtArvGcPropertyNode*> m_expressions;

    QtArvGcPropertyNode* m_formulaNode = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;

    mutable QtArvEvaluator m_evaluator;
};
