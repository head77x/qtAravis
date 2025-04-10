#pragma once

#include "QtArvGcSwissKnife.h"

class QtArvGcIntSwissKnife : public QtArvGcSwissKnife {
public:
    QtArvGcIntSwissKnife();
    ~QtArvGcIntSwissKnife();

    QString nodeName() const override;

    qint64 intValue() const;
    void setIntValue(qint64 value); // �б� ����, ���� ó��

    QString representation() const;
    QString unit() const;
};
