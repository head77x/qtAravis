#pragma once

#include "QtArvGcPropertyNode.h"

class QtArvGcInvalidatorNode : public QtArvGcPropertyNode {
public:
    QtArvGcInvalidatorNode();
    ~QtArvGcInvalidatorNode();

    QString nodeName() const override;
    bool hasChanged();

private:
    quint64 m_cachedChangeCount = 0;
};
