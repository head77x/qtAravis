// QtArvGcCategory.h - GenICam Category node
#pragma once

#include "QtArvGcFeatureNode.h"
#include <QStringList>

class QtArvGcCategory : public QtArvGcFeatureNode {
public:
    QtArvGcCategory();
    ~QtArvGcCategory();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    QStringList features() const;

private:
    QStringList m_features;
};
