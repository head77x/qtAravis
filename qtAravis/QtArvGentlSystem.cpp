// QtArvGentlSystem.cpp - Implementation of GenTL System wrapper
#include "QtArvGentlSystem.h"
#include "QtArvGentlInterface.h"
#include <QDebug>
#include <QDirIterator>

// Hypothetical C API from GenTL Loader
extern "C" {
    void* gentl_load_module(const char* ctiPath);
    void gentl_unload_module(void* module);
    void* gentl_open_system(void* module);
    void gentl_close_system(void* system);
    int gentl_get_interface_count(void* system);
    const char* gentl_get_interface_id(void* system, int index);
    void* gentl_open_interface(void* system, const char* id);
    void gentl_close_interface(void* iface);
}

QtArvGentlSystem::QtArvGentlSystem(const QString& ctiPath, QObject* parent)
    : QObject(parent), m_ctiPath(ctiPath) {
}

QtArvGentlSystem::~QtArvGentlSystem() {
    close();
}

bool QtArvGentlSystem::open() {
    if (m_opened) return true;

    m_module = gentl_load_module(m_ctiPath.toUtf8().constData());
    if (!m_module) {
        qWarning() << "[QtArvGentlSystem] Failed to load module from" << m_ctiPath;
        return false;
    }

    m_systemHandle = gentl_open_system(m_module);
    if (!m_systemHandle) {
        qWarning() << "[QtArvGentlSystem] Failed to open system.";
        gentl_unload_module(m_module);
        m_module = nullptr;
        return false;
    }

    m_opened = true;
    return true;
}

void QtArvGentlSystem::close() {
    if (!m_opened) return;

    for (auto* iface : m_interfaces) {
        iface->deleteLater();
    }
    m_interfaces.clear();

    if (m_systemHandle) {
        gentl_close_system(m_systemHandle);
        m_systemHandle = nullptr;
    }

    if (m_module) {
        gentl_unload_module(m_module);
        m_module = nullptr;
    }

    m_opened = false;
}

bool QtArvGentlSystem::isValid() const {
    return m_opened && m_systemHandle;
}

QString QtArvGentlSystem::fileName() const {
    return m_ctiPath;
}

QStringList QtArvGentlSystem::interfaceIds() {
    QStringList result;
    if (!isValid()) return result;

    int count = gentl_get_interface_count(m_systemHandle);
    for (int i = 0; i < count; ++i) {
        result << gentl_get_interface_id(m_systemHandle, i);
    }
    return result;
}

QtArvGentlInterface* QtArvGentlSystem::openInterface(const QString& id) {
    if (!isValid()) return nullptr;
    if (m_interfaces.contains(id)) return m_interfaces[id];

    void* rawIface = gentl_open_interface(m_systemHandle, id.toUtf8().constData());
    if (!rawIface) {
        qWarning() << "[QtArvGentlSystem] Failed to open interface" << id;
        return nullptr;
    }

    QtArvGentlInterface* iface = new QtArvGentlInterface();
    m_interfaces[id] = iface;
    return iface;
}

QList<QtArvGentlSystem*> QtArvGentlSystem::availableSystems() {
    QList<QtArvGentlSystem*> systems;
    const QString env = qEnvironmentVariable("GENICAM_GENTL64_PATH");
    if (env.isEmpty()) return systems;

    QDirIterator it(env, QStringList() << "*.cti", QDir::Files);
    while (it.hasNext()) {
        QString path = it.next();
        auto* sys = new QtArvGentlSystem(path);
        if (sys->open()) systems << sys;
        else delete sys;
    }
    return systems;
}
