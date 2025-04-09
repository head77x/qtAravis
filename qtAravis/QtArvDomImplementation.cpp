// QtArvDomImplementation.cpp - DOM document factory implementation
#include "QtArvDomImplementation.h"
#include "QtArvDomDocument.h"
#include <QDebug>

QMap<QString, std::function<QtArvDomDocument* ()>> QtArvDomImplementation::s_factories;

void QtArvDomImplementation::registerDocumentType(const QString& qualifiedName, std::function<QtArvDomDocument* ()> factory) {
    s_factories[qualifiedName.toLower()] = factory;
    qDebug() << "[QtArvDomImplementation] Registered document type for:" << qualifiedName;
}

QtArvDomDocument* QtArvDomImplementation::createDocument(const QString& qualifiedName) {
    QString key = qualifiedName.toLower();
    if (s_factories.contains(key)) {
        return s_factories[key]();
    }
    else {
        qWarning() << "[QtArvDomImplementation] Unknown document type:" << qualifiedName;
        return nullptr;
    }
}

void QtArvDomImplementation::cleanup() {
    s_factories.clear();
    qDebug() << "[QtArvDomImplementation] Factory map cleared.";
}