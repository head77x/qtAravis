#include "QtArvGcNode.h"
#include "QtArvGenicam.h"

QtArvGcNode::QtArvGcNode() {}
QtArvGcNode::~QtArvGcNode() {}

QtArvGenicam* QtArvGcNode::genicamContext() const {
    return dynamic_cast<QtArvGenicam*>(ownerDocument());
}
