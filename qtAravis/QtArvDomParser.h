// QtArvDomParser.h
#pragma once

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QUrl>

class QtArvDomParser : public QObject {
    Q_OBJECT

public:
    explicit QtArvDomParser(QObject* parent = nullptr);
    ~QtArvDomParser();

    bool parseFromMemory(const QByteArray& xmlData, QDomDocument& outDoc, QString* errorMsg = nullptr);
    bool parseFromFile(const QString& path, QDomDocument& outDoc, QString* errorMsg = nullptr);
    bool parseFromUrl(const QUrl& url, QDomDocument& outDoc, QString* errorMsg = nullptr);
};
