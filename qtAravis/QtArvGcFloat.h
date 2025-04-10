#pragma once

#include "QtArvGcFeatureNode.h"

class QtArvGcPropertyNode;

class QtArvGcFloat : public QtArvGcFeatureNode {
public:
    QtArvGcFloat();
    ~QtArvGcFloat();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    double floatValue() const;
    void setFloatValue(double value);

    double floatMin() const;
    double floatMax() const;
    double floatIncrement() const;

    QString unit() const;
    QString representation() const;
    QString displayNotation() const;
    int displayPrecision() const;

private:
    QtArvGcPropertyNode* m_value = nullptr;
    QtArvGcPropertyNode* m_min = nullptr;
    QtArvGcPropertyNode* m_max = nullptr;
    QtArvGcPropertyNode* m_inc = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_displayNotation = nullptr;
    QtArvGcPropertyNode* m_displayPrecision = nullptr;
};
