#pragma once

#include "QtArvGcPropertyNode.h"

class QtArvGcIndexNode : public QtArvGcPropertyNode {
public:
    QtArvGcIndexNode();
    ~QtArvGcIndexNode();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;
    void setAttribute(const QString& name, const QString& value) override;

    qint64 getIndex(qint64 defaultOffset = 0) const;

private:
    QString m_offset;
    bool m_isPOffset = false;
};
