// QtArvGentlSystem.h - Wrapper for GenTL System module
#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QMutex>

class QtArvGentlInterface;

class QtArvGentlSystem : public QObject {
    Q_OBJECT
public:
    explicit QtArvGentlSystem(const QString& ctiPath, QObject* parent = nullptr);
    ~QtArvGentlSystem();

    bool open();
    void close();

    bool isValid() const;
    QString fileName() const;

    QStringList interfaceIds();
    QtArvGentlInterface* openInterface(const QString& id);

    static QList<QtArvGentlSystem*> availableSystems();

private:
    QString m_ctiPath;
    void* m_module = nullptr;
    void* m_systemHandle = nullptr;
    QMap<QString, QtArvGentlInterface*> m_interfaces;
    bool m_opened = false;
};
