#include "QtArvGcIntSwissKnife.h"
#include <QDebug>

QtArvGcIntSwissKnife::QtArvGcIntSwissKnife() {}
QtArvGcIntSwissKnife::~QtArvGcIntSwissKnife() {}

QString QtArvGcIntSwissKnife::nodeName() const {
    return "IntSwissKnife";
}

qint64 QtArvGcIntSwissKnife::intValue() const {
    return static_cast<qint64>(evaluate()); // QtArvGcSwissKnife::evaluate()
}

void QtArvGcIntSwissKnife::setIntValue(qint64) {
    qWarning() << "[QtArvGcIntSwissKnife] Read-only node. setIntValue() ignored.";
}

QString QtArvGcIntSwissKnife::representation() const {
    return QtArvGcSwissKnife::representation();
}

QString QtArvGcIntSwissKnife::unit() const {
    return QtArvGcSwissKnife::unit();
}
