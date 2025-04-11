// QtArvGcStructEntryNode.h
#pragma once

#include "QtArvGcFeatureNode.h"
#include "QtArvTypes.h"

class QtArvGcPropertyNode;

class QtArvGcStructEntryNode : public QtArvGcFeatureNode {
    Q_OBJECT

public:
    explicit QtArvGcStructEntryNode(QObject* parent = nullptr);

    QString nodeName() const override;

    QtArvGcAccessMode getAccessMode() const override;
    qint64 getIntegerValue() const override;
    void setIntegerValue(qint64 value) override;

    qint64 minValue() const override;
    qint64 maxValue() const override;
    QtArvGcRepresentation representationType() const override;

protected:
    void postNewChild(QtArvDomNode* child) override;

private:
    QtArvGcPropertyNode* sign;
    QtArvGcPropertyNode* representation;
    QtArvGcPropertyNode* lsb;
    QtArvGcPropertyNode* msb;
    QtArvGcPropertyNode* accessMode;
    QtArvGcPropertyNode* cachable;
};
