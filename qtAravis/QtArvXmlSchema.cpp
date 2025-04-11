// QtArvXmlSchema.cpp - Qt C++ implementation for XML Schema validation
#include "QtArvXmlSchema.h"
#include <QFile>
#include <QDebug>
#include <libxml/parser.h>
#include <libxml/valid.h>
#include <libxml/xmlschemas.h>

QMutex QtArvXmlSchema::s_mutex;

QtArvXmlSchema::QtArvXmlSchema(QObject* parent)
    : QObject(parent) {
}

QtArvXmlSchema::~QtArvXmlSchema() {
    QMutexLocker locker(&s_mutex);
    if (m_validationContext)
        xmlSchemaFreeValidCtxt((xmlSchemaValidCtxtPtr)m_validationContext);
    if (m_schema)
        xmlSchemaFree((xmlSchemaPtr)m_schema);
    if (m_parserContext)
        xmlSchemaFreeParserCtxt((xmlSchemaParserCtxtPtr)m_parserContext);
}

QtArvXmlSchema* QtArvXmlSchema::fromFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[QtArvXmlSchema] Failed to open file:" << path;
        return nullptr;
    }
    QByteArray content = file.readAll();
    return fromMemory(content);
}

QtArvXmlSchema* QtArvXmlSchema::fromMemory(const QByteArray& xsdData) {
    if (xsdData.isEmpty()) return nullptr;
    QtArvXmlSchema* schema = new QtArvXmlSchema();

    QMutexLocker locker(&s_mutex);
    schema->m_xsd = xsdData;
    schema->m_parserContext = xmlSchemaNewMemParserCtxt(schema->m_xsd.constData(), schema->m_xsd.size());
    if (!schema->m_parserContext) return schema;

    schema->m_schema = xmlSchemaParse((xmlSchemaParserCtxtPtr)schema->m_parserContext);
    if (!schema->m_schema) return schema;

    schema->m_validationContext = xmlSchemaNewValidCtxt((xmlSchemaPtr)schema->m_schema);
    return schema;
}

bool QtArvXmlSchema::validate(const QByteArray& xml, int* line, int* column, QString* errorMessage) {
    if (!m_validationContext) return false;
    QMutexLocker locker(&s_mutex);

    xmlSetStructuredErrorFunc(nullptr, nullptr);
    xmlDocPtr doc = xmlParseMemory(xml.constData(), xml.size());
    if (!doc) return false;

    bool result = (xmlSchemaValidateDoc((xmlSchemaValidCtxtPtr)m_validationContext, doc) == 0);
    if (!result && errorMessage) *errorMessage = QString("Validation failed");
    if (line) *line = 0;  // Line info requires custom error handler
    if (column) *column = 0;

    xmlFreeDoc(doc);
    return result;
}
