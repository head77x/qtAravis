// QtArvDomNode.cpp - Base class implementation for DOM nodes
#include "QtArvDomNode.h"

QtArvDomNode::QtArvDomNode(QObject* parent)
    : QObject(parent) {
}

QtArvDomNode::~QtArvDomNode() {}

QtArvDomNode* QtArvDomNode::parentNode() const {
    return m_parent;
}

QtArvDomNode* QtArvDomNode::firstChild() const {
    return m_firstChild;
}

QtArvDomNode* QtArvDomNode::lastChild() const {
    return m_lastChild;
}

QtArvDomNode* QtArvDomNode::previousSibling() const {
    return m_prevSibling;
}

QtArvDomNode* QtArvDomNode::nextSibling() const {
    return m_nextSibling;
}

QVector<QtArvDomNode*> QtArvDomNode::childNodes() const {
    return m_children;
}

QtArvDomDocument* QtArvDomNode::ownerDocument() const {
    // Placeholder: override in derived if needed
    return nullptr;
}

void QtArvDomNode::appendChild(QtArvDomNode* child) {
    if (!child) return;
    if (!m_children.isEmpty()) {
        QtArvDomNode* last = m_children.last();
        last->m_nextSibling = child;
        child->m_prevSibling = last;
    }
    else {
        m_firstChild = child;
    }
    m_lastChild = child;
    child->m_parent = this;
    m_children.append(child);
    notifyDomChanged();
}

void QtArvDomNode::insertBefore(QtArvDomNode* newChild, QtArvDomNode* refChild) {
    if (!newChild || !refChild) return;
    int index = m_children.indexOf(refChild);
    if (index >= 0) {
        m_children.insert(index, newChild);
        newChild->m_parent = this;
        notifyDomChanged();
    }
}

QtArvDomNode* QtArvDomNode::removeChild(QtArvDomNode* child) {
    if (!child) return nullptr;
    int index = m_children.indexOf(child);
    if (index >= 0) {
        m_children.removeAt(index);
        child->m_parent = nullptr;
        child->m_prevSibling = nullptr;
        child->m_nextSibling = nullptr;
        notifyDomChanged();
        return child;
    }
    return nullptr;
}

QtArvDomNode* QtArvDomNode::replaceChild(QtArvDomNode* newChild, QtArvDomNode* oldChild) {
    if (!newChild || !oldChild) return nullptr;
    int index = m_children.indexOf(oldChild);
    if (index >= 0) {
        m_children[index] = newChild;
        newChild->m_parent = this;
        oldChild->m_parent = nullptr;
        notifyDomChanged();
        return oldChild;
    }
    return nullptr;
}

bool QtArvDomNode::hasChildNodes() const {
    return !m_children.isEmpty();
}

void QtArvDomNode::notifyDomChanged() {
    emit domChanged();
}
