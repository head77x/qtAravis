#pragma once

#include "QtArvGcFeatureNode.h"
class QtArvGcPropertyNode;

class QtArvGcString : public QtArvGcFeatureNode {
public:
    QtArvGcString();
    ~QtArvGcString();

    QString nodeName() const override;

    QString stringValue() const;
    void setStringValue(const QString& value);

    int maxLength() const;

protected:
    QtArvGcPropertyNode* m_value = nullptr;
    QtArvGcPropertyNode* m_maxLength = nullptr;
};
