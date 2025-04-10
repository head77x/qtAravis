// QtArvGcFeatureNode.h (확장됨)
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

// QtArvGcFeatureNode.cpp (확장됨)
#include "QtArvGcFeatureNode.h"

QtArvGcFeatureNode::QtArvGcFeatureNode() {}
QtArvGcFeatureNode::~QtArvGcFeatureNode() {}

bool QtArvGcFeatureNode::isSelector() const {
    return !selectedFeatures().isEmpty();
}

QList<QtArvGcFeatureNode*> QtArvGcFeatureNode::selectedFeatures() const {
    return {};
}

// QtArvGcInteger.h (선택자 기능 포함)
#pragma once

#include "QtArvGcFeatureNode.h"
#include <QList>

class QtArvGcPropertyNode;

class QtArvGcInteger : public QtArvGcFeatureNode {
public:
    QtArvGcInteger();
    ~QtArvGcInteger();

    QString nodeName() const override;
    qint64 intValue() const;
    void setIntValue(qint64 value);

    QList<QtArvGcFeatureNode*> selectedFeatures() const override;

private:
    QtArvGcPropertyNode* m_value = nullptr;
    QtArvGcPropertyNode* m_min = nullptr;
    QtArvGcPropertyNode* m_max = nullptr;
    QtArvGcPropertyNode* m_inc = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_unit = nullptr;
    QList<QtArvGcPropertyNode*> m_selecteds;
};

// QtArvGcInteger.cpp
#include "QtArvGcInteger.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGenicam.h"

QtArvGcInteger::QtArvGcInteger() {}
QtArvGcInteger::~QtArvGcInteger() {}

QString QtArvGcInteger::nodeName() const {
    return "Integer";
}

qint64 QtArvGcInteger::intValue() const {
    return m_value ? m_value->toInt() : 0;
}

void QtArvGcInteger::setIntValue(qint64 value) {
    if (m_value) m_value->setInt(value);
}

QList<QtArvGcFeatureNode*> QtArvGcInteger::selectedFeatures() const {
    QList<QtArvGcFeatureNode*> selected;
    for (auto* prop : m_selecteds) {
        auto* linked = dynamic_cast<QtArvGcFeatureNode*>(prop->linkedNode());
        if (linked) selected.append(linked);
    }
    return selected;
}
