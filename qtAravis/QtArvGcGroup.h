#pragma once

#include "QtArvGcFeatureNode.h"

class QtArvGcGroup : public QtArvGcFeatureNode {
public:
    QtArvGcGroup();
    ~QtArvGcGroup();

    QString nodeName() const override;
    void setAttribute(const QString& name, const QString& value) override;
    QString getAttribute(const QString& name) const override;

private:
    QString m_comment;
};
