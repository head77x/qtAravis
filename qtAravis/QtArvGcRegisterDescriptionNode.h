#pragma once

#include "QtArvGcFeatureNode.h"

class QtArvGcRegisterDescriptionNode : public QtArvGcFeatureNode {
public:
    QtArvGcRegisterDescriptionNode();
    ~QtArvGcRegisterDescriptionNode();

    QString nodeName() const override;
    void setAttribute(const QString& name, const QString& value) override;
    QString getAttribute(const QString& name) const override;

    int compareSchemaVersion(int major, int minor, int subminor) const;
    bool checkSchemaVersion(int major, int minor, int subminor) const;

    QString modelName() const;
    QString vendorName() const;

    int majorVersion() const;
    int minorVersion() const;
    int subminorVersion() const;

    int schemaMajorVersion() const;
    int schemaMinorVersion() const;
    int schemaSubminorVersion() const;

private:
    QString m_modelName;
    QString m_vendorName;
    QString m_productGuid;
    QString m_versionGuid;
    QString m_standardNamespace;
    QString m_tooltip;

    int m_majorVersion = 0;
    int m_minorVersion = 0;
    int m_subminorVersion = 0;

    int m_schemaMajor = 0;
    int m_schemaMinor = 0;
    int m_schemaSubminor = 0;
};
