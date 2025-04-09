// QtArvDomDocument.cpp - DOM document root implementation
#include "QtArvDomDocument.h"
#include "QtArvDomElement.h"
#include "QtArvDomText.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

QtArvDomDocument::QtArvDomDocument(QObject* parent)
    : QtArvDomNode(parent) {
}

QtArvDomDocument::~QtArvDomDocument() {}

QString QtArvDomDocument::nodeName() const {
    return "#document";
}

QString QtArvDomDocument::nodeValue() const {
    return QString();
}

void QtArvDomDocument::setNodeValue(const QString& value) {
    Q_UNUSED(value);
}

QtArvDomElement* QtArvDomDocument::getDocumentElement() const {
    for (QtArvDomNode* child : childNodes()) {
        auto* elem = qobject_cast<QtArvDomElement*>(child);
        if (elem) return elem;
    }
    return nullptr;
}

QtArvDomElement* QtArvDomDocument::createElement(const QString& tagName) {
    return new QtArvDomElement(tagName, const_cast<QtArvDomDocument*>(this));
}

QtArvDomText* QtArvDomDocument::createTextNode(const QString& data) {
    return new QtArvDomText(data, const_cast<QtArvDomDocument*>(this));
}

void QtArvDomDocument::setUrl(const QUrl& url) {
    m_url = url;
}

QUrl QtArvDomDocument::url() const {
    return m_url;
}

QByteArray QtArvDomDocument::getHrefData(const QString& href, qint64* size) const {
    QUrl resolved = m_url.resolved(QUrl(href));
    QFile file(resolved.toLocalFile());
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[QtArvDomDocument] Failed to open href file:" << resolved.toString();
        if (size) *size = 0;
        return QByteArray();
    }
    QByteArray data = file.readAll();
    if (size) *size = data.size();
    return data;
}
