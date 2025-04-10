#pragma once

#include "QtArvGcSwissKnife.h"

class QtArvGcFloatSwissKnife : public QtArvGcSwissKnife {
public:
    QtArvGcFloatSwissKnife();
    ~QtArvGcFloatSwissKnife();

    QString nodeName() const override;

    double floatValue() const;
    void setFloatValue(double value);  // ¹«½Ã

    QString displayNotation() const;
    int displayPrecision() const;
};
