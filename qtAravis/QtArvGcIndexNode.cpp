#include "QtArvGcIndexNode.h"
#include "QtArvGenicam.h"
#include "QtArvGcInteger.h"
#include <QDebug>

QtArvGcIndexNode::QtArvGcIndexNode() {}
QtArvGcIndexNode::~QtArvGcIndexNode() {}

QString QtArvGcIndexNode::nodeName() const {
    return "pIndex";
}

bool QtArvGcIndexNode::canAppendChild(QtArvDomNode* child) const {
    return child && child->isText();
}

void QtArvGcIndexNode::setAttribute(const QString& name, const QString& value) {
    if (name == "Offset") {
        m_offset = value;
        m_isPOffset = false;
    }
    else if (name == "pOffset") {
        m_offset = value;
        m_isPOffset = true;
    }
    else {
        QtArvGcPropertyNode::setAttribute(name, value);
    }
}

qint64 QtArvGcIndexNode::getIndex(qint64 defaultOffset) const {
    qint64 offset = defaultOffset;

    if (!m_offset.isEmpty()) {
        if (m_isPOffset) {
            auto* genicam = genicamContext();
            auto* node = genicam ? genicam->getNode(m_offset) : nullptr;
            auto* integer = dynamic_cast<QtArvGcInteger*>(node);
            if (integer)
                offset = integer->intValue();
        }
        else {
            bool ok = false;
            offset = m_offset.toLongLong(&ok, 0);
            if (!ok) offset = defaultOffset;
        }
    }

    return offset * intValue();  // intValue() inherited from QtArvGcPropertyNode
}
