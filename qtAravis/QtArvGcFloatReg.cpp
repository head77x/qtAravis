// QtArvGcFloatReg.cpp - Implementation of GenICam FloatReg node
#include "QtArvGcFloatReg.h"
#include "QtArvGcPropertyNode.h"
#include <QtEndian>
#include <QtGlobal>
#include <QDebug>
#include <cfloat>
#include <cstring>

QtArvGcFloatReg::QtArvGcFloatReg() {}
QtArvGcFloatReg::~QtArvGcFloatReg() {}

QString QtArvGcFloatReg::nodeName() const {
    return "FloatReg";
}

bool QtArvGcFloatReg::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::Endianness:
        const_cast<QtArvGcFloatReg*>(this)->m_endianness = prop;
        return false;
    case QtArvGcPropertyNodeType::Unit:
        const_cast<QtArvGcFloatReg*>(this)->m_unit = prop;
        return false;
    case QtArvGcPropertyNodeType::Representation:
        const_cast<QtArvGcFloatReg*>(this)->m_representation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayNotation:
        const_cast<QtArvGcFloatReg*>(this)->m_displayNotation = prop;
        return false;
    case QtArvGcPropertyNodeType::DisplayPrecision:
        const_cast<QtArvGcFloatReg*>(this)->m_displayPrecision = prop;
        return false;
    case QtArvGcPropertyNodeType::PSelected:
        const_cast<QtArvGcFloatReg*>(this)->m_selecteds.append(prop);
        return false;
    default:
        return QtArvGcRegister::canAppendChild(child);
    }
}

double QtArvGcFloatReg::floatValue() const {
    QByteArray raw = read();
    if (raw.size() == 4) {
        quint32 val;
        memcpy(&val, raw.constData(), 4);
        if (!m_endianness || m_endianness->toString() == "BigEndian")
            val = qFromBigEndian(val);
        else
            val = qFromLittleEndian(val);
        float f;
        memcpy(&f, &val, 4);
        return static_cast<double>(f);
    }
    else if (raw.size() == 8) {
        quint64 val;
        memcpy(&val, raw.constData(), 8);
        if (!m_endianness || m_endianness->toString() == "BigEndian")
            val = qFromBigEndian(val);
        else
            val = qFromLittleEndian(val);
        double d;
        memcpy(&d, &val, 8);
        return d;
    }
    return 0.0;
}

void QtArvGcFloatReg::setFloatValue(double value) {
    QByteArray raw;
    if (length() == 4) {
        float f = static_cast<float>(value);
        quint32 val;
        memcpy(&val, &f, 4);
        if (!m_endianness || m_endianness->toString() == "BigEndian")
            val = qToBigEndian(val);
        else
            val = qToLittleEndian(val);
        raw = QByteArray(reinterpret_cast<const char*>(&val), 4);
    }
    else if (length() == 8) {
        quint64 val;
        memcpy(&val, &value, 8);
        if (!m_endianness || m_endianness->toString() == "BigEndian")
            val = qToBigEndian(val);
        else
            val = qToLittleEndian(val);
        raw = QByteArray(reinterpret_cast<const char*>(&val), 8);
    }
    write(raw);
}

double QtArvGcFloatReg::floatMin() const {
    return (length() == 4) ? -FLT_MAX : -DBL_MAX;
}

double QtArvGcFloatReg::floatMax() const {
    return (length() == 4) ? FLT_MAX : DBL_MAX;
}

QString QtArvGcFloatReg::unit() const {
    return m_unit ? m_unit->toString() : QString();
}

QString QtArvGcFloatReg::representation() const {
    return m_representation ? m_representation->toString() : QString();
}

QString QtArvGcFloatReg::displayNotation() const {
    return m_displayNotation ? m_displayNotation->toString() : QString();
}

int QtArvGcFloatReg::displayPrecision() const {
    return m_displayPrecision ? m_displayPrecision->toInt() : -1;
}
