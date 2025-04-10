#include "QtArvGcInvalidatorNode.h"
#include "QtArvGcFeatureNode.h"

QtArvGcInvalidatorNode::QtArvGcInvalidatorNode() {}
QtArvGcInvalidatorNode::~QtArvGcInvalidatorNode() {}

QString QtArvGcInvalidatorNode::nodeName() const {
    return "pInvalidator";
}

bool QtArvGcInvalidatorNode::hasChanged() {
    QtArvGcNode* linked = linkedNode();
    auto* feature = dynamic_cast<QtArvGcFeatureNode*>(linked);
    if (!feature) return false;

    quint64 currentCount = feature->changeCount();
    if (currentCount != m_cachedChangeCount) {
        m_cachedChangeCount = currentCount;
        return true;
    }

    return false;
}
