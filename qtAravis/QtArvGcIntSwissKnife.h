#pragma once

#include "QtArvGcSwissKnife.h"

class QtArvGcIntSwissKnife : public QtArvGcSwissKnife {
public:
    QtArvGcIntSwissKnife();
    ~QtArvGcIntSwissKnife();

    QString nodeName() const override;

    qint64 intValue() const;
    void setIntValue(qint64 value); // 읽기 전용, 무시 처리

    QString representation() const;
    QString unit() const;
};
