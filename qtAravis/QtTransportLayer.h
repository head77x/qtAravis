#pragma once

#include <QObject>

class QtTransportLayer : public QObject {
    Q_OBJECT
public:
    explicit QtTransportLayer(QObject* parent = nullptr);
};
