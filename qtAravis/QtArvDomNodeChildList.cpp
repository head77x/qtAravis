// QtArvDomNodeChildList.cpp - Implementation of child node list
#include "QtArvDomNodeChildList.h"
#include "QtArvDomNode.h"

QtArvDomNodeChildList::QtArvDomNodeChildList(QtArvDomNode* parent)
    : m_parent(parent) {
}

QtArvDomNodeChildList::~QtArvDomNodeChildList() {}

QtArvDomNode* QtArvDomNodeChildList::item(int index) const {
    if (!m_parent || index < 0) return nullptr;
    const auto children = m_parent->childNodes();
    if (index >= children.size()) return nullptr;
    return children.at(index);
}

int QtArvDomNodeChildList::length() const {
    return m_parent ? m_parent->childNodes().size() : 0;
}
