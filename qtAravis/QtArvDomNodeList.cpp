// QtArvDomNodeList.cpp - Static dispatch interface for node list
#include "QtArvDomNodeList.h"
#include "QtArvDomNode.h"

QtArvDomNode* QtArvDomNodeList::get(QtArvDomNodeList* list, int index) {
    if (!list || index < 0) return nullptr;
    return list->item(index);
}

int QtArvDomNodeList::count(QtArvDomNodeList* list) {
    return list ? list->length() : 0;
}
