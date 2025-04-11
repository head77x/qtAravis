// QtArvGcFeatureNode.h (»Æ¿Âµ )
#pragma once

#include "QtArvGcNode.h"
#include <QList>

class QtArvGcFeatureNode : public QtArvGcNode {
public:
    QtArvGcFeatureNode();
    virtual ~QtArvGcFeatureNode();

    virtual bool isSelector() const;
    virtual QList<QtArvGcFeatureNode*> selectedFeatures() const;
};

// QtArvGcFeatureNode.cpp (»Æ¿Âµ )
#include "QtArvGcFeatureNode.h"

QtArvGcFeatureNode::QtArvGcFeatureNode() {}
QtArvGcFeatureNode::~QtArvGcFeatureNode() {}

bool QtArvGcFeatureNode::isSelector() const {
    return !selectedFeatures().isEmpty();
}

QList<QtArvGcFeatureNode*> QtArvGcFeatureNode::selectedFeatures() const {
    return {};
}


