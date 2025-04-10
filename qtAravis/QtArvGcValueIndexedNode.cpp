#include "QtArvGcValueIndexedNode.h"
#include <QDebug>

QtArvGcValueIndexedNode::QtArvGcValueIndexedNode(QtArvGcPropertyNodeType type)
    : QtArvGcPropertyNode(type) {
}

QtArvGcValueIndexedNode::~QtArvGcValueIndexedNode() {}

QString QtArvGcValueIndexedNode::nodeName() const {
    switch (propertyType()) {
    case QtArvGcPropertyNodeType::ValueIndexed: return "ValueIndexed";
    case QtArvGcPropertyNodeType::pValueIndexed: return "pValueIndexed";
    default:
        qWarning() << "[QtArvGcValueIndexedNode] Unknown node type!";
        return "Unknown";
    }
}

void QtArvGcValueIndexedNode::setAttribute(const QString& name, const QString& value) {
    if (name == "Index") {
        m_indexString = value;
    }
    else {
        QtArvGcPropertyNode::setAttribute(name, value);
    }
}

QString QtArvGcValueIndexedNode::getAttribute(const QString& name) const {
    if (name == "Index") {
        return m_indexString;
    }
    return QtArvGcPropertyNode::getAttribute(name);
}

qint64 QtArvGcValueIndexedNode::index() const {
    bool ok = false;
    qint64 val = m_indexString.toLongLong(&ok, 0);
    return ok ? val : 0;
}
