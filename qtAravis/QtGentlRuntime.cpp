#include "QtGentlRuntime.h"
#include "QtGentlEvent.h"
#include <QDebug>

QtGentlRuntime::QtGentlRuntime(QObject* parent)
    : QObject(parent), m_initialized(false) {
}

QtGentlRuntime::~QtGentlRuntime() {
    finalize();
}

QtGentlRuntime& QtGentlRuntime::instance() {
    static QtGentlRuntime runtime;
    return runtime;
}

void QtGentlRuntime::initialize() {
    if (m_initialized) return;
    m_initialized = true;
    m_events.clear();
    qDebug() << "[Gentl] Initialized";
}

void QtGentlRuntime::finalize() {
    if (!m_initialized) return;
    m_events.clear();
    m_initialized = false;
    qDebug() << "[Gentl] Finalized";
}

bool QtGentlRuntime::isInitialized() const {
    return m_initialized;
}

QHash<void*, QHash<int, QtGentlEvent*>>& QtGentlRuntime::eventMap() {
    return m_events;
}
