// QtArvGcIntReg.cpp - GenICam IntReg node implementation
#include "QtArvGcIntReg.h"
#include "QtArvGcPropertyNode.h"
#include <QtEndian>
#include <QDebug>
#include <climits>
#include <cstring>

QtArvGcIntReg::QtArvGcIntReg() {}
QtArvGcIntReg::~QtArvGcIntReg() {}

QString QtArvGcIntReg::nodeName() const {
    return "IntReg";
}

bool QtArvGcIntReg::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::Sign:
        const_cast<QtArvGcIntReg*>(this)->m_sign = prop;
        return false;
    case QtArvGcPropertyNodeType::Endianness:
        const_cast<QtArvGcIntReg*>(this)->m_endianness = prop;
        return false;
    case QtArvGcPropertyNodeType::Unit:
        const_cast<QtArvGcIntReg*>(this)->m_unit = prop;
        return false;
    case QtArvGcPropertyNodeType::Representation:
        const_cast<QtArvGcIntReg*>(this)->m_representation = prop;
        return false;
    case QtArvGcPropertyNodeType::PSelected:
        const_cast<QtArvGcIntReg*>(this)->m_selecteds.append(prop);
        return false;
    default:
        return QtArvGcRegister::canAppendChild(child);
    }
}

qint64 QtArvGcIntReg::intValue() const {
    QByteArray data = read();
    if (data.isEmpty() || data.size() > 8)
        return 0;

    quint64 raw = 0;
    memcpy(&raw, data.constData(), data.size());

    if (!m_endianness || m_endianness->toString() == "BigEndian")
        raw = qFromBigEndian(raw);
    else
        raw = qFromLittleEndian(raw);

    if (m_sign && m_sign->toString() == "Signed") {
        qint64 signedVal = 0;
        memcpy(&signedVal, &raw, data.size());
        return signedVal;
    }

    return static_cast<qint64>(raw);
}

void QtArvGcIntReg::setIntValue(qint64 value) {
    QByteArray buffer(length(), 0);
    quint64 raw = static_cast<quint64>(value);
    if (!m_endianness || m_endianness->toString() == "BigEndian")
        raw = qToBigEndian(raw);
    else
        raw = qToLittleEndian(raw);
    memcpy(buffer.data(), &raw, buffer.size());
    write(buffer);
}

qint64 QtArvGcIntReg::intMin() const {
    int bits = length() * 8;
    if (m_sign && m_sign->toString() == "Signed") {
        return -(1LL << (bits - 1));
    }
    return 0;
}

qint64 QtArvGcIntReg::intMax() const {
    int bits = length() * 8;
    if (m_sign && m_sign->toString() == "Signed") {
        return (1LL << (bits - 1)) - 1;
    }
    return (1ULL << bits) - 1;
}

qint64 QtArvGcIntReg::intInc() const {
    return 1;
}

QString QtArvGcIntReg::unit() const {
    return m_unit ? m_unit->toString() : QString();
}

QString QtArvGcIntReg::representation() const {
    return m_representation ? m_representation->toString() : QString();
}
