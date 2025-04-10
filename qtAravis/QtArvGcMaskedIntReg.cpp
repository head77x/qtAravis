// QtArvGcMaskedIntReg.cpp - GenICam MaskedIntReg node
#include "QtArvGcMaskedIntReg.h"
#include "QtArvGcPropertyNode.h"
#include <QtEndian>
#include <QDebug>
#include <climits>

QtArvGcMaskedIntReg::QtArvGcMaskedIntReg() {}
QtArvGcMaskedIntReg::~QtArvGcMaskedIntReg() {}

QString QtArvGcMaskedIntReg::nodeName() const {
    return "MaskedIntReg";
}

bool QtArvGcMaskedIntReg::canAppendChild(QtArvDomNode* child) const {
    auto* prop = dynamic_cast<QtArvGcPropertyNode*>(child);
    if (!prop) return true;

    switch (prop->propertyType()) {
    case QtArvGcPropertyNodeType::LSB:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_lsb = prop;
        return false;
    case QtArvGcPropertyNodeType::MSB:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_msb = prop;
        return false;
    case QtArvGcPropertyNodeType::Bit:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_lsb = prop;
        const_cast<QtArvGcMaskedIntReg*>(this)->m_msb = prop;
        return false;
    case QtArvGcPropertyNodeType::Sign:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_sign = prop;
        return false;
    case QtArvGcPropertyNodeType::Endianness:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_endianness = prop;
        return false;
    case QtArvGcPropertyNodeType::Representation:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_representation = prop;
        return false;
    case QtArvGcPropertyNodeType::Unit:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_unit = prop;
        return false;
    case QtArvGcPropertyNodeType::PSelected:
        const_cast<QtArvGcMaskedIntReg*>(this)->m_selecteds.append(prop);
        return false;
    default:
        return QtArvGcRegister::canAppendChild(child);
    }
}

qint64 QtArvGcMaskedIntReg::intValue() const {
    int lsb = m_lsb ? m_lsb->toInt() : 0;
    int msb = m_msb ? m_msb->toInt() : 31;
    bool signedness = m_sign && m_sign->toString() == "Signed";
    bool bigEndian = !m_endianness || m_endianness->toString() == "BigEndian";

    QByteArray buffer = read();
    if (buffer.isEmpty()) return 0;

    quint64 raw = 0;
    memcpy(&raw, buffer.constData(), qMin(sizeof(raw), size_t(buffer.size())));
    if (bigEndian) raw = qFromBigEndian(raw);
    else raw = qFromLittleEndian(raw);

    int bitStart = qMin(lsb, msb);
    int bitEnd = qMax(lsb, msb);
    int width = bitEnd - bitStart + 1;
    quint64 mask = ((1ULL << width) - 1) << bitStart;
    quint64 value = (raw & mask) >> bitStart;

    if (signedness) {
        qint64 signedVal = value;
        qint64 signBit = 1ULL << (width - 1);
        if (value & signBit) signedVal -= (1LL << width);
        return signedVal;
    }
    return static_cast<qint64>(value);
}

void QtArvGcMaskedIntReg::setIntValue(qint64 value) {
    int lsb = m_lsb ? m_lsb->toInt() : 0;
    int msb = m_msb ? m_msb->toInt() : 31;
    bool signedness = m_sign && m_sign->toString() == "Signed";
    bool bigEndian = !m_endianness || m_endianness->toString() == "BigEndian";

    int bitStart = qMin(lsb, msb);
    int bitEnd = qMax(lsb, msb);
    int width = bitEnd - bitStart + 1;
    quint64 raw = 0;

    if (signedness && value < 0)
        raw = (1ULL << width) + value;
    else
        raw = static_cast<quint64>(value);

    raw <<= bitStart;
    QByteArray buffer = read();
    if (buffer.size() < 8) buffer.resize(8);

    quint64 existing = 0;
    memcpy(&existing, buffer.constData(), 8);
    if (bigEndian) existing = qFromBigEndian(existing);
    else existing = qFromLittleEndian(existing);

    quint64 mask = ((1ULL << width) - 1) << bitStart;
    existing = (existing & ~mask) | raw;

    quint64 result = bigEndian ? qToBigEndian(existing) : qToLittleEndian(existing);
    memcpy(buffer.data(), &result, 8);
    write(buffer);
}

qint64 QtArvGcMaskedIntReg::intMin() const {
    int lsb = m_lsb ? m_lsb->toInt() : 0;
    int msb = m_msb ? m_msb->toInt() : 31;
    int width = qAbs(msb - lsb) + 1;
    if (m_sign && m_sign->toString() == "Signed") {
        return -(1LL << (width - 1));
    }
    return 0;
}

qint64 QtArvGcMaskedIntReg::intMax() const {
    int lsb = m_lsb ? m_lsb->toInt() : 0;
    int msb = m_msb ? m_msb->toInt() : 31;
    int width = qAbs(msb - lsb) + 1;
    if (m_sign && m_sign->toString() == "Signed") {
        return (1LL << (width - 1)) - 1;
    }
    return (1ULL << width) - 1;
}

qint64 QtArvGcMaskedIntReg::intInc() const {
    return 1;
}

QString QtArvGcMaskedIntReg::representation() const {
    return m_representation ? m_representation->toString() : QString();
}

QString QtArvGcMaskedIntReg::unit() const {
    return m_unit ? m_unit->toString() : QString();
}
