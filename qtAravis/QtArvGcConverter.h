// QtArvGcConverter.h - GenICam abstract converter node
#pragma once

#include "QtArvGcFeatureNode.h"
#include <QList>
#include <QString>
#include <QScopedPointer>
#include "QtArvEvaluator.h"

class QtArvGcPropertyNode;

class QtArvGcConverter : public QtArvGcFeatureNode {
public:
    QtArvGcConverter();
    ~QtArvGcConverter();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;
    QtArvGcFeatureNode* getLinkedFeature() const override;

    double convertToDouble() const;
    qint64 convertToInt64() const;
    void convertFromDouble(double value);
    void convertFromInt64(qint64 value);

    QString unit() const;
    QString representation() const;
    QString displayNotation() const;
    int displayPrecision() const;

protected:
    QList<QtArvGcPropertyNode*> m_variables;
    QList<QtArvGcPropertyNode*> m_constants;
    QList<QtArvGcPropertyNode*> m_expressions;

    QtArvGcPropertyNode* m_value = nullptr;
    QtArvGcPropertyNode* m_formulaTo = nullptr;
    QtArvGcPropertyNode* m_formulaFrom = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_displayNotation = nullptr;
    QtArvGcPropertyNode* m_displayPrecision = nullptr;
    QtArvGcPropertyNode* m_isLinear = nullptr;
    QtArvGcPropertyNode* m_slope = nullptr;

    QScopedPointer<QtArvEvaluator> m_evalTo;
    QScopedPointer<QtArvEvaluator> m_evalFrom;

    bool updateFromVariables() const;
    void updateToVariables(double fromValue) const;
};
