#pragma once

#include "QtArvGcRegister.h"
#include <QStringList>

class QtArvGcPropertyNode;

class QtArvGcFloatReg : public QtArvGcRegister {
public:
    QtArvGcFloatReg();
    ~QtArvGcFloatReg();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    double floatValue() const;
    void setFloatValue(double value);

    double floatMin() const;
    double floatMax() const;

    QString unit() const;
    QString representation() const;
    QString displayNotation() const;
    int displayPrecision() const;

private:
    QtArvGcPropertyNode* m_endianness = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_displayNotation = nullptr;
    QtArvGcPropertyNode* m_displayPrecision = nullptr;

    QList<QtArvGcPropertyNode*> m_selecteds;
};
