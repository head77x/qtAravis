// QtArvV4L2Device.cpp - Qt C++ implementation of V4L2 device logic or Windows camera

#include "QtArvV4L2Device.h"
#include <QDebug>

#ifdef Q_OS_LINUX
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#endif

#ifdef Q_OS_WIN
#include <QMediaDevices>
#include <QCamera>
#include <QCameraDevice>
#endif

QtArvV4L2Device::QtArvV4L2Device(const QString& deviceFile, QObject* parent)
    : QObject(parent), m_deviceFile(deviceFile)
{
#ifdef Q_OS_LINUX
    m_fd = -1;
#endif

#ifdef Q_OS_WIN
    m_camera = nullptr;
#endif
}

QtArvV4L2Device::~QtArvV4L2Device() {
    close();
}

bool QtArvV4L2Device::open() {
#ifdef Q_OS_LINUX
    if (m_fd >= 0) return true;
    m_fd = ::open(m_deviceFile.toStdString().c_str(), O_RDWR);
    if (m_fd < 0) {
        qWarning() << "Failed to open V4L2 device" << m_deviceFile;
        return false;
    }

    struct v4l2_capability cap;
    if (ioctl(m_fd, VIDIOC_QUERYCAP, &cap) == 0) {
        m_driver = QString(reinterpret_cast<const char*>(cap.driver));
        m_card = QString(reinterpret_cast<const char*>(cap.card));
        m_version = QString::number(VERSION_MAJOR(cap.version)) + "." +
            QString::number(VERSION_MINOR(cap.version)) + "." +
            QString::number(VERSION_PATCH(cap.version));
    }

    return loadGenicamXml();
#endif

#ifdef Q_OS_WIN
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    for (const QCameraDevice& dev : cameras) {
        if (dev.id() == m_deviceFile) {
            m_camera = new QCamera(dev, this);
            m_driver = dev.description();
            m_card = dev.id();
            m_version = "1.0";
            m_camera->start();
            return loadGenicamXml();
        }
    }
    qWarning() << "No matching camera found for device:" << m_deviceFile;
    return false;
#endif
}

void QtArvV4L2Device::close() {
#ifdef Q_OS_LINUX
    if (m_fd >= 0) {
        ::close(m_fd);
        m_fd = -1;
    }
#endif

#ifdef Q_OS_WIN
    if (m_camera) {
        m_camera->stop();
        delete m_camera;
        m_camera = nullptr;
    }
#endif
}

QString QtArvV4L2Device::deviceName() const {
    return m_card;
}

QString QtArvV4L2Device::driverVersion() const {
    return m_version;
}

QString QtArvV4L2Device::driverName() const {
    return m_driver;
}

QString QtArvV4L2Device::manufacturerInfo() const {
    return QString("%1 v%2").arg(m_driver, m_version);
}

QByteArray QtArvV4L2Device::readMemory(quint64 address, int size) {
    Q_UNUSED(address)
        Q_UNUSED(size)
        return QByteArray();
}

bool QtArvV4L2Device::writeMemory(quint64 address, const QByteArray& data) {
    Q_UNUSED(address)
        Q_UNUSED(data)
        return false;
}

QByteArray QtArvV4L2Device::getGenicamXml() const {
    return m_genicamXml;
}

bool QtArvV4L2Device::loadGenicamXml() {
    m_genicamXml = QByteArray("<genicam>stub</genicam>");
    return true;
}
