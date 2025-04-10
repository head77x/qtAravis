#pragma once

#include "QtArvGcConverter.h"

class QtArvGcIntConverter : public QtArvGcConverter {
public:
    QtArvGcIntConverter();
    ~QtArvGcIntConverter();

    QString nodeName() const override;

    qint64 intValue() const;
    void setIntValue(qint64 value);

    qint64 intMin() const;
    qint64 intMax() const;
    qint64 intInc() const;

    QString unit() const;
    QString representation() const;
};
