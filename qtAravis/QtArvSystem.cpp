// QtArvSystem.cpp - Ported from arvsystem.c
#include "QtArvSystem.h"
#include "QtArvInterface.h"
#include "QtArvDevice.h"
#include "QtArvDomImplementation.h"
#include <QMutex>
#include <QMap>
#include <QString>
#include <QVector>
#include <QDebug>

static QMutex systemMutex;

namespace QtArvSystem {

    struct InterfaceInfo {
        QString interfaceId;
        QString protocol;
        bool available;
        QtArvInterface* (*getInstance)();
        void (*destroyInstance)();
    };

    static QVector<InterfaceInfo> interfaces = {
        {"Fake", "Fake", false, getFakeInterfaceInstance, destroyFakeInterfaceInstance},
        {"GigEVision", "GigEVision", true, getGvInterfaceInstance, destroyGvInterfaceInstance},
        {"GenTL", "Mixed", true, getGentlInterfaceInstance, destroyGentlInterfaceInstance}
    };

    int getInterfaceCount() {
        return interfaces.size();
    }

    QtArvInterface* getInterface(int index) {
        if (index < 0 || index >= interfaces.size()) return nullptr;
        return interfaces[index].getInstance();
    }

    QtArvInterface* getInterfaceById(const QString& id) {
        for (const auto& iface : interfaces) {
            if (iface.interfaceId == id)
                return iface.getInstance();
        }
        return nullptr;
    }

    QString getInterfaceId(int index) {
        if (index < 0 || index >= interfaces.size()) return QString();
        return interfaces[index].interfaceId;
    }

    QString getInterfaceProtocol(int index) {
        if (index < 0 || index >= interfaces.size()) return QString();
        return interfaces[index].protocol;
    }

    void enableInterface(const QString& id) {
        for (auto& iface : interfaces)
            if (iface.interfaceId == id)
                iface.available = true;
    }

    void disableInterface(const QString& id) {
        for (auto& iface : interfaces)
            if (iface.interfaceId == id)
                iface.available = false;
    }

    void updateDeviceList() {
        QMutexLocker locker(&systemMutex);
        for (const auto& iface : interfaces) {
            if (iface.available) {
                QtArvInterface* intf = iface.getInstance();
                intf->updateDeviceList();
            }
        }
    }

    int getDeviceCount() {
        QMutexLocker locker(&systemMutex);
        int count = 0;
        for (const auto& iface : interfaces) {
            if (iface.available) {
                QtArvInterface* intf = iface.getInstance();
                count += intf->getDeviceCount();
            }
        }
        return count;
    }

    QString getDeviceInfo(int index, QString(QtArvInterface::* infoFunc)(int) const) {
        QMutexLocker locker(&systemMutex);
        int offset = 0;
        for (const auto& iface : interfaces) {
            if (iface.available) {
                QtArvInterface* intf = iface.getInstance();
                int n = intf->getDeviceCount();
                if (index - offset < n)
                    return (intf->*infoFunc)(index - offset);
                offset += n;
            }
        }
        return QString();
    }

    QString getDeviceId(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceId); }
    QString getDevicePhysicalId(int index) { return getDeviceInfo(index, &QtArvInterface::getDevicePhysicalId); }
    QString getDeviceVendor(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceVendor); }
    QString getDeviceModel(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceModel); }
    QString getDeviceSerialNumber(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceSerialNumber); }
    QString getDeviceAddress(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceAddress); }
    QString getDeviceProtocol(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceProtocol); }
    QString getDeviceManufacturerInfo(int index) { return getDeviceInfo(index, &QtArvInterface::getDeviceManufacturerInfo); }

    QtArvDevice* openDevice(const QString& deviceId, QString* error) {
        QMutexLocker locker(&systemMutex);
        for (const auto& iface : interfaces) {
            if (iface.available) {
                QtArvInterface* intf = iface.getInstance();
                QString err;
                QtArvDevice* dev = intf->openDevice(deviceId, &err);
                if (dev || !err.isEmpty()) {
                    if (error) *error = err;
                    return dev;
                }
            }
        }
        if (error) *error = deviceId.isEmpty() ? "No supported device found" : QString("Device '%1' not found").arg(deviceId);
        return nullptr;
    }

    void shutdown() {
        QMutexLocker locker(&systemMutex);
        for (const auto& iface : interfaces)
            iface.destroyInstance();

        QtArvDomImplementation::cleanup();
    }

} // namespace QtArvSystem
