// QtArvGcStructEntryNode.cpp - Qt C++ port of ArvGcStructEntryNode
#include "QtArvGcStructEntryNode.h"
#include "QtArvGcRegisterNode.h"
#include "QtArvGcRegister.h"
#include "QtArvGcIntegerInterface.h"
#include "QtArvGcPropertyNode.h"
#include "QtArvGcPort.h"
#include "QtArvGcFeatureNodePrivate.h"
#include <QDebug>
#include <cmath>

QtArvGcStructEntryNode::QtArvGcStructEntryNode(QObject* parent)
    : QtArvGcFeatureNode(parent), sign(nullptr), representation(nullptr), lsb(nullptr), msb(nullptr), accessMode(nullptr), cachable(nullptr) {
}

QString QtArvGcStructEntryNode::nodeName() const {
    return "StructEntry";
}

void QtArvGcStructEntryNode::postNewChild(QtArvDomNode* child) {
    if (auto* property = qobject_cast<QtArvGcPropertyNode*>(child)) {
        switch (property->nodeType()) {
        case QtArvGcPropertyNodeType::Sign: sign = property; break;
        case QtArvGcPropertyNodeType::Representation: representation = property; break;
        case QtArvGcPropertyNodeType::LSB: lsb = property; break;
        case QtArvGcPropertyNodeType::MSB: msb = property; break;
        case QtArvGcPropertyNodeType::Bit: lsb = msb = property; break;
        case QtArvGcPropertyNodeType::AccessMode: accessMode = property; break;
        case QtArvGcPropertyNodeType::Cachable: cachable = property; break;
        default: QtArvGcFeatureNode::postNewChild(child); break;
        }
    }
}

QtArvGcAccessMode QtArvGcStructEntryNode::getAccessMode() const {
    if (accessMode)
        return accessMode->accessMode(QtArvGcAccessMode::ReadOnly);
    auto* parentRegister = qobject_cast<QtArvGcRegisterNode*>(parent());
    return parentRegister ? parentRegister->actualAccessMode() : QtArvGcAccessMode::ReadOnly;
}

qint64 QtArvGcStructEntryNode::getIntegerValue() const {
    auto* parentRegister = qobject_cast<QtArvGcRegisterNode*>(parent());
    if (!parentRegister) return 0;
    return parentRegister->getMaskedIntegerValue(
        lsb ? lsb->value(0) : 0,
        msb ? msb->value(31) : 31,
        sign ? sign->signedness() : QtArvGcSignedness::Unsigned,
        0,
        cachable ? cachable->cachableMode() : QtArvGcCachable::WriteAround
    );
}

void QtArvGcStructEntryNode::setIntegerValue(qint64 value) {
    auto* parentRegister = qobject_cast<QtArvGcRegisterNode*>(parent());
    if (!parentRegister) return;
    incrementChangeCount();
    parentRegister->setMaskedIntegerValue(
        lsb ? lsb->value(0) : 0,
        msb ? msb->value(31) : 31,
        sign ? sign->signedness() : QtArvGcSignedness::Unsigned,
        0,
        cachable ? cachable->cachableMode() : QtArvGcCachable::WriteAround,
        value
    );
}

qint64 QtArvGcStructEntryNode::minValue() const {
    auto* parentRegister = qobject_cast<QtArvGcRegisterNode*>(parent());
    if (!parentRegister) return 0;

    auto s = sign ? sign->signedness() : QtArvGcSignedness::Unsigned;
    auto e = parentRegister->endianness();
    int l = lsb ? lsb->value(e == QtArvEndianness::BigEndian ? 31 : 0) : 0;
    int m = msb ? msb->value(e == QtArvEndianness::BigEndian ? 0 : 31) : 31;

    if ((e == QtArvEndianness::BigEndian && m > l) || (e != QtArvEndianness::BigEndian && l > m)) {
        qWarning() << "Invalid bit range for node";
        return std::numeric_limits<qint64>::max();
    }

    if (s == QtArvGcSignedness::Signed)
        return -(1LL << std::abs(l - m));
    else
        return 0;
}

qint64 QtArvGcStructEntryNode::maxValue() const {
    auto* parentRegister = qobject_cast<QtArvGcRegisterNode*>(parent());
    if (!parentRegister) return 0;

    auto s = sign ? sign->signedness() : QtArvGcSignedness::Unsigned;
    auto e = parentRegister->endianness();
    int l = lsb ? lsb->value(e == QtArvEndianness::BigEndian ? 31 : 0) : 0;
    int m = msb ? msb->value(e == QtArvEndianness::BigEndian ? 0 : 31) : 31;

    if ((e == QtArvEndianness::BigEndian && m > l) || (e != QtArvEndianness::BigEndian && l > m)) {
        qWarning() << "Invalid bit range for node";
        return std::numeric_limits<qint64>::max();
    }

    int width = std::abs(l - m) + 1;
    return s == QtArvGcSignedness::Signed ? (1LL << (width - 1)) - 1 : (1LL << width) - 1;
}

QtArvGcRepresentation QtArvGcStructEntryNode::representationType() const {
    return representation ? representation->representation(QtArvGcRepresentation::Undefined)
        : QtArvGcRepresentation::Undefined;
}
