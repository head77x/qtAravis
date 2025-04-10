#pragma once

#include "QtArvGcFeatureNode.h"
#include "QtArvGcRegisterInterface.h"

class QtArvGcPropertyNode;

class QtArvGcStructEntry : public QtArvGcFeatureNode, public QtArvGcRegisterInterface {
public:
    QtArvGcStructEntry();
    ~QtArvGcStructEntry();

    QString nodeName() const override;

    // Register interface
    QByteArray read() const override;
    void write(const QByteArray& buffer) override;
    quint64 address() const override;
    quint64 length() const override;

    // Integer logic
    qint64 intValue() const;
    void setIntValue(qint64 value);
    qint64 intMin() const;
    qint64 intMax() const;
    QString representation() const;

protected:
    QtArvGcPropertyNode* m_sign = nullptr;
    QtArvGcPropertyNode* m_representation = nullptr;
    QtArvGcPropertyNode* m_lsb = nullptr;
    QtArvGcPropertyNode* m_msb = nullptr;
    QtArvGcPropertyNode* m_accessMode = nullptr;
    QtArvGcPropertyNode* m_cachable = nullptr;
};
