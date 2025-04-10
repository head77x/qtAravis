#pragma once

#include "QtArvGcRegister.h"

class QtArvGcPropertyNode;

class QtArvGcMaskedIntReg : public QtArvGcRegister {
public:
    QtArvGcMaskedIntReg();
    ~QtArvGcMaskedIntReg();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    qint64 intValue() const;
    void setIntValue(qint64 value);

    qint64 intMin() const;
    qint64 intMax() const;
    qint64 intInc() const;

    QString representation() const;
    QString unit() const;

private:
    QtArvGcPropertyNode* m_lsb = nullptr;
    QtArvGcPropertyNode* m_msb = nullptr;
    QtArvGcPropertyNode* m_sign = nullptr;
    QtArvGcPropertyNode* m_endianness = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;

    QList<QtArvGcPropertyNode*> m_selecteds;
};
