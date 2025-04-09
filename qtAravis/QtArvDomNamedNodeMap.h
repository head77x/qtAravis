// QtArvDomNamedNodeMap.h - Interface for named node access
#pragma once

#include <QString>

class QtArvDomNode;

class QtArvDomNamedNodeMap {
public:
    virtual ~QtArvDomNamedNodeMap() = default;

    virtual QtArvDomNode* getNamedItem(const QString& name) const = 0;
    virtual QtArvDomNode* setNamedItem(QtArvDomNode* item) = 0;
    virtual QtArvDomNode* removeNamedItem(const QString& name) = 0;

    virtual QtArvDomNode* item(int index) const = 0;
    virtual int length() const = 0;

    // Static wrapper for compatibility
    static QtArvDomNode* get(QtArvDomNamedNodeMap* map, const QString& name);
    static QtArvDomNode* set(QtArvDomNamedNodeMap* map, QtArvDomNode* item);
    static QtArvDomNode* remove(QtArvDomNamedNodeMap* map, const QString& name);
    static QtArvDomNode* at(QtArvDomNamedNodeMap* map, int index);
    static int count(QtArvDomNamedNodeMap* map);
};
