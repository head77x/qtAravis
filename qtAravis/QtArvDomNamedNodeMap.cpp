// QtArvDomNamedNodeMap.cpp - Abstract base with default dispatch support
#include "QtArvDomNamedNodeMap.h"
#include "QtArvDomNode.h"

QtArvDomNode* QtArvDomNamedNodeMap::get(QtArvDomNamedNodeMap* map, const QString& name) {
    if (!map) return nullptr;
    return map->getNamedItem(name);
}

QtArvDomNode* QtArvDomNamedNodeMap::set(QtArvDomNamedNodeMap* map, QtArvDomNode* item) {
    if (!map) return nullptr;
    return map->setNamedItem(item);
}

QtArvDomNode* QtArvDomNamedNodeMap::remove(QtArvDomNamedNodeMap* map, const QString& name) {
    if (!map) return nullptr;
    return map->removeNamedItem(name);
}

QtArvDomNode* QtArvDomNamedNodeMap::at(QtArvDomNamedNodeMap* map, int index) {
    if (!map) return nullptr;
    return map->item(index);
}

int QtArvDomNamedNodeMap::count(QtArvDomNamedNodeMap* map) {
    return map ? map->length() : 0;
}
