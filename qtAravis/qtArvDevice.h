// QtArvDevice.h - C++ 리팩토링 헤더
#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QByteArray>
#include <functional>
#include <memory>

class QtArvStream;
class QtArvGenicam;
class QtArvNode;

class QtArvDevice : public QObject {
    Q_OBJECT

public:
    explicit QtArvDevice(QObject* parent = nullptr);
    virtual ~QtArvDevice();

    std::shared_ptr<QtArvStream> createStream(std::function<void()> callback = nullptr);

    bool readMemory(quint64 address, quint32 size, void* buffer);
    bool writeMemory(quint64 address, quint32 size, const void* buffer);

    bool readRegister(quint64 address, quint32& value);
    bool writeRegister(quint64 address, quint32 value);

    QByteArray getGenicamXml() const;
    QtArvGenicam* getGenicam();

    bool executeCommand(const QString& feature);

    bool getBoolean(const QString& feature);
    void setBoolean(const QString& feature, bool value);

    qint64 getInteger(const QString& feature);
    void setInteger(const QString& feature, qint64 value);

    double getFloat(const QString& feature);
    void setFloat(const QString& feature, double value);

    QString getString(const QString& feature);
    void setString(const QString& feature, const QString& value);

    bool isFeatureAvailable(const QString& feature);
    bool isFeatureImplemented(const QString& feature);

    bool startAcquisition();
    bool stopAcquisition();

signals:
    void controlLost();
    void deviceEvent(int eventId);

private:
    void* internal = nullptr; // 원래 C 구조체를 래핑하거나 대체할 내부 포인터
    QVector<std::shared_ptr<QtArvStream>> streams;

    QtArvGenicam* genicam = nullptr;
    void* getFeatureNode(const QString& name);
};
