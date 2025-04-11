// QtArvGcInteger.h - GenICam Integer Feature Node
#pragma once

#include "QtArvGcFeatureNode.h"
#include <QList>
#include <QString>
#include <QtGlobal>

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
