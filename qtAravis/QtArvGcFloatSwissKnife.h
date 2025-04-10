#pragma once

#include "QtArvGcSwissKnife.h"

class QtArvGcFloatSwissKnife : public QtArvGcSwissKnife {
public:
    QtArvGcFloatSwissKnife();
    ~QtArvGcFloatSwissKnife();

    QString nodeName() const override;

    double floatValue() const;
    void setFloatValue(double value);  // ����

    QString displayNotation() const;
    int displayPrecision() const;
};
