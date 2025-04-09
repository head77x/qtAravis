// QtArvGenicam.cpp - Implementation for QtArvGenicam
#include "QtArvGenicam.h"
#include "QtArvDevice.h"
#include "QtArvNode.h"
#include <QDebug>

QtArvGenicam::QtArvGenicam(QtArvDevice* device, const QByteArray& xmlData, QObject* parent)
    : QObject(parent), device(device), xml(xmlData) {
    if (!parseXml(xmlData)) {
        qWarning() << "[QtArvGenicam] Failed to parse GenICam XML.";
    }
    else {
        qDebug() << "[QtArvGenicam] XML parsed successfully.";
    }
}

QtArvGenicam::~QtArvGenicam() {
    nodeMap.clear();
}

QtArvGenicam::CachePolicy QtArvGenicam::getCachePolicy() const {
    return cachePolicy;
}

void QtArvGenicam::setCachePolicy(CachePolicy policy) {
    cachePolicy = policy;
}

QtArvNode* QtArvGenicam::getNode(const QString& name) const {
    if (nodeMap.contains(name)) {
        return nodeMap.value(name).data();
    }
    return nullptr;
}

void QtArvGenicam::registerFeatureNode(const QString& name, QtArvNode* node) {
    if (!name.isEmpty() && node) {
        nodeMap.insert(name, QSharedPointer<QtArvNode>(node));
        qDebug() << "[QtArvGenicam] Registered node:" << name;
    }
}

QStringList QtArvGenicam::getAllFeatureNames() const {
    return nodeMap.keys();
}

bool QtArvGenicam::parseXml(const QByteArray& xml) {
    QString errorStr;
    int errorLine, errorColumn;
    if (!dom.setContent(xml, false, &errorStr, &errorLine, &errorColumn)) {
        qWarning() << "[QtArvGenicam] XML parse error at line" << errorLine << "column" << errorColumn << ":" << errorStr;
        return false;
    }
    QDomElement root = dom.documentElement();
    if (root.tagName() != "RegisterDescription") {
        qWarning() << "[QtArvGenicam] Unexpected root tag:" << root.tagName();
        return false;
    }
    // TODO: 角力 FeatureNode 颇教 棺 积己 肺流
    return true;
}
