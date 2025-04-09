// QtArvGcCommand.h - GenICam Command node
#pragma once

#include "QtArvGcFeatureNode.h"
class QtArvGcPropertyNode;

class QtArvGcCommand : public QtArvGcFeatureNode {
public:
    QtArvGcCommand();
    ~QtArvGcCommand();

    QString nodeName() const override;
    bool canAppendChild(QtArvDomNode* child) const override;

    void execute();
    QtArvGcFeatureNode* getLinkedFeature() const override;

private:
    QtArvGcPropertyNode* m_commandValue = nullptr;
    QtArvGcPropertyNode* m_value = nullptr;
};
