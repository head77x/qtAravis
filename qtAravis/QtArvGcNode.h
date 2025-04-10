// QtArvGcNode.h - Abstract base class for all GenICam XML nodes
#pragma once

#include "QtArvDomElement.h"
#include <QString>

class QtArvGenicam;

class QtArvGcNode : public QtArvDomElement {
public:
    QtArvGcNode();
    virtual ~QtArvGcNode();

    QtArvGenicam* genicamContext() const;

    virtual QString nodeName() const = 0;
};
