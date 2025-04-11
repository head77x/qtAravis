#pragma once

#include <QObject>
#include <QString>
#include <QVector>

class QtGentlInterface;

class QtGentlTransportLayer : public QObject {
    Q_OBJECT

public:
    explicit QtGentlTransportLayer(QObject* parent = nullptr);
    ~QtGentlTransportLayer();

    bool open();
    void close();

    int getNumInterfaces() const;
    QString getInterfaceId(int index) const;
    QString getInterfaceInfo(const QString& ifaceId, int infoCmd) const;

    QtGentlInterface* openInterface(const QString& ifaceId);
    bool updateInterfaceList(bool* changed = nullptr, quint64 timeout = 0);

private:
    bool m_isOpen;
};
