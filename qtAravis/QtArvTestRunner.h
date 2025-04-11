// QtArvTestRunner.h - Header for QtArvTestRunner
#pragma once

#include <QObject>

class QtArvTestRunner : public QObject {
    Q_OBJECT

public:
    explicit QtArvTestRunner(QObject* parent = nullptr);
    void run();
};
