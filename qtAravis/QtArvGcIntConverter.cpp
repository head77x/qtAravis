#include "QtArvGcIntConverter.h"
#include <QtGlobal>
#include <limits>

QtArvGcIntConverter::QtArvGcIntConverter() {}
QtArvGcIntConverter::~QtArvGcIntConverter() {}

QString QtArvGcIntConverter::nodeName() const {
    return "IntConverter";
}

qint64 QtArvGcIntConverter::intValue() const {
    return convertToInt64();
}

void QtArvGcIntConverter::setIntValue(qint64 value) {
    convertFromInt64(value);
}

qint64 QtArvGcIntConverter::intMin() const {
    qint64 a = convertToInt64();  // ideally MinNode
    qint64 b = convertToInt64();  // ideally MaxNode
    return qMin(a, b);
}

qint64 QtArvGcIntConverter::intMax() const {
    qint64 a = convertToInt64();  // ideally MinNode
    qint64 b = convertToInt64();  // ideally MaxNode
    return qMax(a, b);
}

qint64 QtArvGcIntConverter::intInc() const {
    return 1; // GenICam 2.1.1 spec: increment is always 1
}

QString QtArvGcIntConverter::unit() const {
    return QtArvGcConverter::unit();
}

QString QtArvGcIntConverter::representation() const {
    return QtArvGcConverter::representation();
}
