// QtArvGcRegisterDescriptionNode.cpp - Implementation of <RegisterDescription> node
#include "QtArvGcRegisterDescriptionNode.h"
#include <QString>

QtArvGcRegisterDescriptionNode::QtArvGcRegisterDescriptionNode() {}
QtArvGcRegisterDescriptionNode::~QtArvGcRegisterDescriptionNode() {}

QString QtArvGcRegisterDescriptionNode::nodeName() const {
    return "RegisterDescription";
}

void QtArvGcRegisterDescriptionNode::setAttribute(const QString& name, const QString& value) {
    if (name == "ModelName") m_modelName = value;
    else if (name == "VendorName") m_vendorName = value;
    else if (name == "ProductGuid") m_productGuid = value;
    else if (name == "VersionGuid") m_versionGuid = value;
    else if (name == "ToolTip") m_tooltip = value;
    else if (name == "StandardNameSpace") m_standardNamespace = value;
    else if (name == "MajorVersion") m_majorVersion = value.toInt();
    else if (name == "MinorVersion") m_minorVersion = value.toInt();
    else if (name == "SubMinorVersion") m_subminorVersion = value.toInt();
    else if (name == "SchemaMajorVersion") m_schemaMajor = value.toInt();
    else if (name == "SchemaMinorVersion") m_schemaMinor = value.toInt();
    else if (name == "SchemaSubMinorVersion") m_schemaSubminor = value.toInt();
    else QtArvGcFeatureNode::setAttribute(name, value);
}

QString QtArvGcRegisterDescriptionNode::getAttribute(const QString& name) const {
    if (name == "ModelName") return m_modelName;
    if (name == "VendorName") return m_vendorName;
    if (name == "ProductGuid") return m_productGuid;
    if (name == "VersionGuid") return m_versionGuid;
    if (name == "ToolTip") return m_tooltip;
    if (name == "StandardNameSpace") return m_standardNamespace;
    if (name == "MajorVersion") return QString::number(m_majorVersion);
    if (name == "MinorVersion") return QString::number(m_minorVersion);
    if (name == "SubMinorVersion") return QString::number(m_subminorVersion);
    if (name == "SchemaMajorVersion") return QString::number(m_schemaMajor);
    if (name == "SchemaMinorVersion") return QString::number(m_schemaMinor);
    if (name == "SchemaSubMinorVersion") return QString::number(m_schemaSubminor);
    return QtArvGcFeatureNode::getAttribute(name);
}

QString QtArvGcRegisterDescriptionNode::modelName() const { return m_modelName; }
QString QtArvGcRegisterDescriptionNode::vendorName() const { return m_vendorName; }
int QtArvGcRegisterDescriptionNode::majorVersion() const { return m_majorVersion; }
int QtArvGcRegisterDescriptionNode::minorVersion() const { return m_minorVersion; }
int QtArvGcRegisterDescriptionNode::subminorVersion() const { return m_subminorVersion; }
int QtArvGcRegisterDescriptionNode::schemaMajorVersion() const { return m_schemaMajor; }
int QtArvGcRegisterDescriptionNode::schemaMinorVersion() const { return m_schemaMinor; }
int QtArvGcRegisterDescriptionNode::schemaSubminorVersion() const { return m_schemaSubminor; }

int QtArvGcRegisterDescriptionNode::compareSchemaVersion(int major, int minor, int subminor) const {
    if (m_schemaMajor != major)
        return m_schemaMajor < major ? -1 : 1;
    if (m_schemaMinor != minor)
        return m_schemaMinor < minor ? -1 : 1;
    if (m_schemaSubminor != subminor)
        return m_schemaSubminor < subminor ? -1 : 1;
    return 0;
}

bool QtArvGcRegisterDescriptionNode::checkSchemaVersion(int major, int minor, int subminor) const {
    return compareSchemaVersion(major, minor, subminor) >= 0;
}
