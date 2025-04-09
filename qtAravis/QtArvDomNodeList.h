// QtArvDomNodeList.h - Abstract interface for node lists
#pragma once

class QtArvDomNode;

class QtArvDomNodeList {
public:
    virtual ~QtArvDomNodeList() = default;

    virtual QtArvDomNode* item(int index) const = 0;
    virtual int length() const = 0;

    static QtArvDomNode* get(QtArvDomNodeList* list, int index);
    static int count(QtArvDomNodeList* list);
};
