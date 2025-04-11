#include "QtTransportLayer.h"
#include <QDebug>

QtTransportLayer::QtTransportLayer(QObject* parent)
    : QObject(parent) {
    qDebug() << "[QtTransportLayer] Initialized";
}
