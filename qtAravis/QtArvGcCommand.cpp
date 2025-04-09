// QtArvGcCommand.cpp - GenICam Command node implementation
#include "QtArvGcCommand.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGenicam.h"
#include <QDebug>

QtArvGcCommand::QtArvGcCommand() {}

QtArvGcCommand::~QtArvGcCommand() {}

QString QtArvGcCommand::nodeName() const {
    return "Command";
}

bool QtArvGcCommand::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::Value:
    case QtArvGcPropertyNodeType::PValue:
        const_cast<QtArvGcCommand*>(this)->m_value = prop;
        return false;
    case QtArvGcPropertyNodeType::CommandValue:
    case QtArvGcPropertyNodeType::PCommandValue:
        const_cast<QtArvGcCommand*>(this)->m_commandValue = prop;
        return false;
    default:
        return true;
    }
}

void QtArvGcCommand::execute() {
    if (!m_value || !m_commandValue) return;

    if (!checkWriteAccess()) return;

    bool ok = false;
    qint64 commandVal = m_commandValue->toInt64(&ok);
    if (!ok) {
        qWarning() << "[QtArvGcCommand] Invalid command value.";
        return;
    }

    incrementChangeCount();
    m_value->setInt64(commandVal);

    qDebug() << "[QtArvGcCommand::execute] Executed command with value:" << commandVal;
}

QtArvGcFeatureNode* QtArvGcCommand::getLinkedFeature() const {
    if (!m_value) return nullptr;
    QtArvGcNode* linked = m_value->linkedNode();
    return dynamic_cast<QtArvGcFeatureNode*>(linked);
}
