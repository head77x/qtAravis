// QtArvDomParser.cpp - DOM parser for XML sources
#include "QtArvDomParser.h"
#include <QFile>
#include <QDebug>

QtArvDomParser::QtArvDomParser(QObject* parent)
    : QObject(parent) {
}

QtArvDomParser::~QtArvDomParser() {}

bool QtArvDomParser::parseFromMemory(const QByteArray& xmlData, QDomDocument& outDoc, QString* errorMsg) {
    QString errorStr;
    int errorLine = 0, errorColumn = 0;
    if (!outDoc.setContent(xmlData, false, &errorStr, &errorLine, &errorColumn)) {
        if (errorMsg) {
            *errorMsg = QString("Line %1, Column %2: %3").arg(errorLine).arg(errorColumn).arg(errorStr);
        }
        return false;
    }
    return true;
}

bool QtArvDomParser::parseFromFile(const QString& path, QDomDocument& outDoc, QString* errorMsg) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        if (errorMsg) *errorMsg = "Cannot open file: " + path;
        return false;
    }
    QByteArray xmlData = file.readAll();
    return parseFromMemory(xmlData, outDoc, errorMsg);
}

bool QtArvDomParser::parseFromUrl(const QUrl& url, QDomDocument& outDoc, QString* errorMsg) {
    if (!url.isLocalFile()) {
        if (errorMsg) *errorMsg = "Only local file URLs are supported.";
        return false;
    }
    return parseFromFile(url.toLocalFile(), outDoc, errorMsg);
}
