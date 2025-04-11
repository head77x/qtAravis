// QtArvSystem.h - Device and interface management system
#pragma once

#include <QString>
#include "QtArvInterface.h"
#include "QtArvDevice.h"

namespace QtArvSystem {

	int getInterfaceCount();
	QtArvInterface* getInterface(int index);
	QtArvInterface* getInterfaceById(const QString& id);
	QString getInterfaceId(int index);
	QString getInterfaceProtocol(int index);
	void enableInterface(const QString& id);
	void disableInterface(const QString& id);

	void updateDeviceList();
	int getDeviceCount();
	QString getDeviceId(int index);
	QString getDevicePhysicalId(int index);
	QString getDeviceVendor(int index);
	QString getDeviceModel(int index);
	QString getDeviceSerialNumber(int index);
	QString getDeviceAddress(int index);
	QString getDeviceProtocol(int index);
	QString getDeviceManufacturerInfo(int index);

	QtArvDevice* openDevice(const QString& deviceId, QString* error = nullptr);
	void shutdown();

} // namespace QtArvSystem
