// QtArvDomImplementation.h
#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class QtArvDomDocument;

class QtArvDomImplementation {
public:
    static void registerDocumentType(const QString& qualifiedName, std::function<QtArvDomDocument* ()> factory);
    static QtArvDomDocument* createDocument(const QString& qualifiedName);
    static void cleanup();

private:
    static QMap<QString, std::function<QtArvDomDocument* ()>> s_factories;
};
