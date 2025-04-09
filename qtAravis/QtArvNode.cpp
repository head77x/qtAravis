// QtArvNode.cpp - Base implementation for QtArvNode
#include "QtArvNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvNode::QtArvNode(QtArvGenicam* genicam, const QDomElement& domElement, QObject* parent)
    : QObject(parent), genicam(genicam), element(domElement) {
    nodeName = element.attribute("Name");
    qDebug() << "[QtArvNode] Initialized node:" << nodeName;
}

QtArvNode::~QtArvNode() {
    qDebug() << "[QtArvNode] Destroyed node:" << nodeName;
}

QString QtArvNode::name() const {
    return nodeName;
}

bool QtArvNode::write(const QVariant& value) {
    Q_UNUSED(value);
    qWarning() << "[QtArvNode] Write not supported on node:" << nodeName;
    return false;
}