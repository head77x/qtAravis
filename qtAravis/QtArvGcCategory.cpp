// QtArvGcCategory.cpp - GenICam Category node implementation
#include "QtArvGcCategory.h"
#include "QtArvDomNode.h"
#include "QtArvDomElement.h"

QtArvGcCategory::QtArvGcCategory() {}

QtArvGcCategory::~QtArvGcCategory() {}

QString QtArvGcCategory::nodeName() const {
    return "Category";
}

bool QtArvGcCategory::canAppendChild(QtArvDomNode* child) const {
    // Only allow Feature nodes (name-only text elements)
    if (!child) return false;
    return true;
}

QStringList QtArvGcCategory::features() const {
    QStringList list;
    for (QtArvDomNode* node : childNodes()) {
        if (auto* elem = qobject_cast<QtArvDomElement*>(node)) {
            if (elem->nodeName() == "pFeature") {
                list << elem->nodeValue();
            }
        }
    }
    return list;
}