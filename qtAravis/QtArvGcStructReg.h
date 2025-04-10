#pragma once

#include "QtArvGcRegister.h"

class QtArvGcStructReg : public QtArvGcRegister {
public:
    QtArvGcStructReg();
    ~QtArvGcStructReg();

    QString nodeName() const override;
};
