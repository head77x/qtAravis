#pragma once

#include <QObject>
#include <QHash>
#include <QMutex>

class QtGentlEvent;

class QtGentlRuntime : public QObject {
    Q_OBJECT

public:
    static QtGentlRuntime& instance();

    bool isInitialized() const;
    void initialize();
    void finalize();

    QHash<void*, QHash<int, QtGentlEvent*>>& eventMap();

private:
    explicit QtGentlRuntime(QObject* parent = nullptr);
    ~QtGentlRuntime();

    bool m_initialized;
    QHash<void*, QHash<int, QtGentlEvent*>> m_events;

    Q_DISABLE_COPY(QtGentlRuntime)
};
