#pragma once

#include "QtArvGcPropertyNode.h"

class QtArvGcValueIndexedNode : public QtArvGcPropertyNode {
public:
    QtArvGcValueIndexedNode(QtArvGcPropertyNodeType type);
    ~QtArvGcValueIndexedNode();

    QString nodeName() const override;
    void setAttribute(const QString& name, const QString& value) override;
    QString getAttribute(const QString& name) const override;

    qint64 index() const;

private:
    QString m_indexString;
};
