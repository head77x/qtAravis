#pragma once

#include "QtArvGcRegister.h"
#include <QString>

class QtArvGcStringReg : public QtArvGcRegister {
public:
    QtArvGcStringReg();
    ~QtArvGcStringReg();

    QString nodeName() const override;

    QString stringValue() const;
    void setStringValue(const QString& value);

    int maxLength() const;
};
