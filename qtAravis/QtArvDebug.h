// QtArvDebug.h - Logging and debug utility
#pragma once

#include <QString>
#include <QMap>
#include <QMutex>

enum class QtArvDebugLevel {
    Warning = 1,
    Info = 2,
    Debug = 3,
    Trace = 4
};

class QtArvDebug {
public:
    static void setLevel(const QString& category, QtArvDebugLevel level);
    static QtArvDebugLevel level(const QString& category);

    static void log(const QString& category, QtArvDebugLevel level, const QString& message);

    static void warning(const QString& category, const QString& message);
    static void info(const QString& category, const QString& message);
    static void debug(const QString& category, const QString& message);
    static void trace(const QString& category, const QString& message);

    static void printAvailableCategories();

private:
    static QMap<QString, QtArvDebugLevel> categoryLevels;
    static QMutex mutex;
};
