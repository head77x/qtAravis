// QtArvDomNodeChildList.h
#pragma once

#include "QtArvDomNodeList.h"

class QtArvDomNode;

class QtArvDomNodeChildList : public QtArvDomNodeList {
public:
    explicit QtArvDomNodeChildList(QtArvDomNode* parent);
    ~QtArvDomNodeChildList();

    QtArvDomNode* item(int index) const override;
    int length() const override;

private:
    QtArvDomNode* m_parent;
};
