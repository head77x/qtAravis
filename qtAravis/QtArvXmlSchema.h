// QtArvXmlSchema.h - Qt C++ class for XML Schema validation
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QScopedPointer>
#include <QMutex>

class QtArvXmlSchema : public QObject {
    Q_OBJECT

public:
    explicit QtArvXmlSchema(QObject* parent = nullptr);
    ~QtArvXmlSchema();

    static QtArvXmlSchema* fromFile(const QString& path);
    static QtArvXmlSchema* fromMemory(const QByteArray& xsdData);

    bool validate(const QByteArray& xml, int* line = nullptr, int* column = nullptr, QString* errorMessage = nullptr);

private:
    QByteArray m_xsd;
    void* m_parserContext = nullptr;
    void* m_schema = nullptr;
    void* m_validationContext = nullptr;

    static QMutex s_mutex;
};
