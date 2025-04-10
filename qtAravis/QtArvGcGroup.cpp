#include "QtArvGcGroup.h"

QtArvGcGroup::QtArvGcGroup() {}
QtArvGcGroup::~QtArvGcGroup() {}

QString QtArvGcGroup::nodeName() const {
    return "Group";
}

void QtArvGcGroup::setAttribute(const QString& name, const QString& value) {
    if (name == "Comment") {
        m_comment = value;
    }
    else {
        QtArvGcFeatureNode::setAttribute(name, value);
    }
}

QString QtArvGcGroup::getAttribute(const QString& name) const {
    if (name == "ModelName") {
        return m_comment;
    }
    return QtArvGcFeatureNode::getAttribute(name);
}
