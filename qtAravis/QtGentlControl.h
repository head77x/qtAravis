// QtGentlControl.h - Abstract interface for GenTL control-like API
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QVariant>

class QtGentlControl : public QObject {
    Q_OBJECT

public:
    explicit QtGentlControl(QObject* parent = nullptr);
    ~QtGentlControl();

    QString getInfo(const QString& key);
    QString getLastError();

    QByteArray readPort(quint64 address, int length);
    bool writePort(quint64 address, const QByteArray& data);

    QString getPortURL();
    QVariant getPortInfo(int infoType);

    int getNumPortURLs();
    QVariant getPortURLInfo(int index, int infoType);

    bool registerEvent(int eventType);
    bool unregisterEvent(int eventType);

    QByteArray readPortStacked(); // Placeholder
    bool writePortStacked();      // Placeholder
};
