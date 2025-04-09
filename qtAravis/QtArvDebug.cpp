// QtArvDebug.cpp - Logging and debug utility implementation
#include "QtArvDebug.h"
#include <QTextStream>
#include <QDebug>

QMap<QString, QtArvDebugLevel> QtArvDebug::categoryLevels;
QMutex QtArvDebug::mutex;

void QtArvDebug::setLevel(const QString& category, QtArvDebugLevel level) {
    QMutexLocker locker(&mutex);
    categoryLevels[category.toLower()] = level;
}

QtArvDebugLevel QtArvDebug::level(const QString& category) {
    QMutexLocker locker(&mutex);
    return categoryLevels.value(category.toLower(), QtArvDebugLevel::Warning);
}

void QtArvDebug::log(const QString& category, QtArvDebugLevel level, const QString& message) {
    if (level <= QtArvDebug::level(category)) {
        QString tag;
        switch (level) {
        case QtArvDebugLevel::Warning: tag = "[WARN]"; break;
        case QtArvDebugLevel::Info: tag = "[INFO]"; break;
        case QtArvDebugLevel::Debug: tag = "[DEBUG]"; break;
        case QtArvDebugLevel::Trace: tag = "[TRACE]"; break;
        }
        qInfo().noquote() << QString("%1 [%2] %3").arg(tag, category.toUpper(), message);
    }
}

void QtArvDebug::warning(const QString& category, const QString& message) {
    log(category, QtArvDebugLevel::Warning, message);
}

void QtArvDebug::info(const QString& category, const QString& message) {
    log(category, QtArvDebugLevel::Info, message);
}

void QtArvDebug::debug(const QString& category, const QString& message) {
    log(category, QtArvDebugLevel::Debug, message);
}

void QtArvDebug::trace(const QString& category, const QString& message) {
    log(category, QtArvDebugLevel::Trace, message);
}

void QtArvDebug::printAvailableCategories() {
    QMutexLocker locker(&mutex);
    qInfo() << "Available QtArvDebug categories:";
    for (const QString& key : categoryLevels.keys()) {
        qInfo() << " -" << key << ": level" << static_cast<int>(categoryLevels.value(key));
    }
}