// QtArvEnumerationNode.cpp - Implementation of Enumeration node
#include "QtArvEnumerationNode.h"
#include "QtArvGenicam.h"
#include "QtArvEnumEntryNode.h"
#include <QDomNodeList>
#include <QDebug>

QtArvEnumerationNode::QtArvEnumerationNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvEnumerationNode] Constructed:" << name();
}

QtArvEnumerationNode::~QtArvEnumerationNode() {
    qDebug() << "[QtArvEnumerationNode] Destroyed:" << name();
}

QVariant QtArvEnumerationNode::read() const {
    QDomElement valueElem = element.firstChildElement("Value");
    if (valueElem.isNull()) return QVariant();

    QString entryName = valueElem.text().trimmed();
    QtArvNode* entryNode = genicam->getNode(entryName);
    if (entryNode) {
        return entryNode->read();
    }
    return QVariant();
}

bool QtArvEnumerationNode::write(const QVariant& value) {
    if (!value.canConvert<QString>()) {
        qWarning() << "[QtArvEnumerationNode] Invalid write type for node:" << name();
        return false;
    }
    QString target = value.toString();
    QtArvNode* entryNode = genicam->getNode(target);
    if (!entryNode) {
        qWarning() << "[QtArvEnumerationNode] Enum entry not found:" << target;
        return false;
    }
    qDebug() << "[QtArvEnumerationNode] Set enumeration to" << target;
    // 실제 레지스터 연동 필요 (TODO)
    return true;
}

QStringList QtArvEnumerationNode::availableEntryNames() const {
    QStringList entries;
    QDomNodeList list = element.elementsByTagName("pEnumerationEntry");
    for (int i = 0; i < list.count(); ++i) {
        QDomElement el = list.at(i).toElement();
        if (!el.isNull()) {
            entries << el.text().trimmed();
        }
    }
    return entries;
}

int QtArvEnumerationNode::maxEntryNameLength() const {
    int maxLen = 0;
    for (const QString& name : availableEntryNames()) {
        maxLen = qMax(maxLen, name.length());
    }
    return maxLen;
}
