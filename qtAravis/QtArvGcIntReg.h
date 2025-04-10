// QtArvGcIntReg.h - GenICam IntReg node (Register with integer interpretation)
#pragma once

#include "QtArvGcRegister.h"

class QtArvGcPropertyNode;

class QtArvGcIntReg : public QtArvGcRegister {
public:
    QtArvGcIntReg();
    ~QtArvGcIntReg();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    qint64 intValue() const;
    void setIntValue(qint64 value);

    qint64 intMin() const;
    qint64 intMax() const;
    qint64 intInc() const;

    QString unit() const;
    QString representation() const;

private:
    QtArvGcPropertyNode* m_sign = nullptr;
    QtArvGcPropertyNode* m_endianness = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;

    QList<QtArvGcPropertyNode*> m_selecteds;
};
