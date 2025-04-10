// QtArvGcFeatureNode.cpp - Abstract base class for GenICam feature nodes
#include "QtArvGcFeatureNode.h"
#include "QtArvGcPropertyNode.h"

QtArvGcFeatureNode::QtArvGcFeatureNode() {}
QtArvGcFeatureNode::~QtArvGcFeatureNode() {}

QString QtArvGcFeatureNode::name() const {
    return m_name;
}

void QtArvGcFeatureNode::setName(const QString& name) {
    m_name = name;
}

QtArvGcNameSpace QtArvGcFeatureNode::nameSpace() const {
    return m_nameSpace;
}

QString QtArvGcFeatureNode::displayName() const {
    return m_displayName ? m_displayName->toString() : QString();
}

QString QtArvGcFeatureNode::description() const {
    return m_description ? m_description->toString() : QString();
}

QString QtArvGcFeatureNode::tooltip() const {
    return m_tooltip ? m_tooltip->toString() : QString();
}

QtArvGcVisibility QtArvGcFeatureNode::visibility() const {
    return m_visibility ? QtArvGcVisibilityFromString(m_visibility->toString()) : QtArvGcVisibility::Beginner;
}

bool QtArvGcFeatureNode::isAvailable() const {
    return true;
}

bool QtArvGcFeatureNode::isImplemented() const {
    return true;
}

bool QtArvGcFeatureNode::isLocked() const {
    return false;
}

quint64 QtArvGcFeatureNode::changeCount() const {
    return m_changeCount;
}

void QtArvGcFeatureNode::incrementChangeCount() {
    ++m_changeCount;
}

void QtArvGcFeatureNode::setVisibility(QtArvGcPropertyNode* node) {
    m_visibility = node;
}

void QtArvGcFeatureNode::setDisplayName(QtArvGcPropertyNode* node) {
    m_displayName = node;
}

void QtArvGcFeatureNode::setDescription(QtArvGcPropertyNode* node) {
    m_description = node;
}

void QtArvGcFeatureNode::setTooltip(QtArvGcPropertyNode* node) {
    m_tooltip = node;
}
