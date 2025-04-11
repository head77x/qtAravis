// QtGentlEvent.h - GenTL Event abstraction (placeholder)
#pragma once

#include <QObject>

class QtGentlEvent : public QObject {
    Q_OBJECT

public:
    explicit QtGentlEvent(QObject* parent = nullptr);
    ~QtGentlEvent();

    QByteArray getData(int timeoutMs = 100);
    QVariant getDataInfo(int infoType);
    QVariant getInfo(int infoCmd);
    bool flush();
    bool kill();

signals:
    void eventReceived();
};
