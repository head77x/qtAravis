#pragma once

#include "QtArvGcNode.h"

enum class QtArvGcPropertyNodeType {
    Unknown,
    Value, Address, Unit, Representation,
    Min, Max, Inc,
    pValue, pMin, pMax, pInc,
    Endianness, Sign, Bit, LSB, MSB,
    ChunkID, EventID,
    Constant, Formula, Expression,
    AccessMode, Visibility,
    DisplayName, ToolTip,
    pSelected, pPort, pVariable,
    Streamable
};

class QtArvGcFeatureNode;

class QtArvGcPropertyNode : public QtArvGcNode {
public:
    QtArvGcPropertyNode(QtArvGcPropertyNodeType type);
    ~QtArvGcPropertyNode();

    QString nodeName() const override;
    void setAttribute(const QString& name, const QString& value) override;
    QString getAttribute(const QString& name) const override;

    QtArvGcPropertyNodeType propertyType() const;

    QString toString() const;
    void setString(const QString& value);

    qint64 toInt() const;
    void setInt(qint64 value);

    double toDouble() const;
    void setDouble(double value);

    QtArvGcNode* linkedNode() const;

private:
    QString m_name;
    QtArvGcPropertyNodeType m_type;
    mutable QString m_cachedValue;
    mutable bool m_valueCached = false;

    QString getRawValue() const;
    void setRawValue(const QString& val);
};
