// QtArvGcFeatureNode.cpp - Abstract base class for GenICam feature nodes

#include "QtArvGcFeatureNode.h"
#include "QtArvGcPropertyNode.h"

QtArvGcFeatureNode::QtArvGcFeatureNode()
    : m_nameSpace(QtArvGcNameSpace::Custom),
    m_changeCount(0),
    m_displayName(nullptr),
    m_description(nullptr),
    m_tooltip(nullptr),
    m_visibility(nullptr),
    m_isAvailable(nullptr),
    m_isImplemented(nullptr),
    m_isLocked(nullptr)
{
}

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

void QtArvGcFeatureNode::setNameSpace(QtArvGcNameSpace ns) {
    m_nameSpace = ns;
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
    return m_isAvailable ? (m_isAvailable->toInt() != 0) : true;
}

bool QtArvGcFeatureNode::isImplemented() const {
    return m_isImplemented ? (m_isImplemented->toInt() != 0) : true;
}

bool QtArvGcFeatureNode::isLocked() const {
    return m_isLocked ? (m_isLocked->toInt() != 0) : false;
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

void QtArvGcFeatureNode::setIsAvailable(QtArvGcPropertyNode* node) {
    m_isAvailable = node;
}

void QtArvGcFeatureNode::setIsImplemented(QtArvGcPropertyNode* node) {
    m_isImplemented = node;
}

void QtArvGcFeatureNode::setIsLocked(QtArvGcPropertyNode* node) {
    m_isLocked = node;
}
