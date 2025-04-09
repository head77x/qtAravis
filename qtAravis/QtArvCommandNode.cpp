// QtArvCommandNode.cpp - Implementation for QtArvCommandNode
#include "QtArvCommandNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvCommandNode::QtArvCommandNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent)
    : QtArvNode(genicam, element, parent) {
    qDebug() << "[QtArvCommandNode] Constructed:" << name();
}

QtArvCommandNode::~QtArvCommandNode() {
    qDebug() << "[QtArvCommandNode] Destroyed:" << name();
}

QVariant QtArvCommandNode::read() const {
    // Commands have no readable value in general
    return QVariant();
}

bool QtArvCommandNode::write(const QVariant& value) {
    Q_UNUSED(value);
    // Optional: allow calling execute() via write(true)
    return execute();
}

bool QtArvCommandNode::execute() {
    qDebug() << "[QtArvCommandNode] Execute command on" << name();
    // TODO: 실제 장치 명령 전송 구현 필요
    return true;
}
