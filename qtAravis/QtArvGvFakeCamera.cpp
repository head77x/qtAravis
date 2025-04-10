// QtArvGvFakeCamera.cpp - Simulated GigE Vision camera logic
#include "QtArvGvFakeCamera.h"
#include <QDebug>
#include "QtArvFakeCamera.h" // assumed implementation

QtArvGvFakeCamera::QtArvGvFakeCamera(const QString& interfaceName,
    const QString& serialNumber,
    const QString& genicamFile,
    QObject* parent)
    : QObject(parent),
    m_interfaceName(interfaceName),
    m_serialNumber(serialNumber),
    m_genicamFile(genicamFile)
{
    m_camera = new QtArvFakeCamera(serialNumber, genicamFile);
    start();
}

QtArvGvFakeCamera::~QtArvGvFakeCamera() {
    stop();
    delete m_camera;
    m_camera = nullptr;
}

void QtArvGvFakeCamera::start() {
    if (m_running) return;
    qDebug() << "[QtArvGvFakeCamera] Starting camera on interface" << m_interfaceName;
    m_running = true;
    // TODO: Start UDP listening sockets and GVSP stream in separate thread
}

void QtArvGvFakeCamera::stop() {
    if (!m_running) return;
    m_running = false;
    qDebug() << "[QtArvGvFakeCamera] Stopping camera";
    // TODO: Gracefully stop GVSP stream and control server
}

bool QtArvGvFakeCamera::isRunning() const {
    return m_running;
}

QtArvFakeCamera* QtArvGvFakeCamera::fakeCamera() const {
    return m_camera;
}
