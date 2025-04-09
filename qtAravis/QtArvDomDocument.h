// QtArvDomDocument.h
#pragma once

#include "QtArvDomNode.h"
#include "QtArvDomElement.h"
#include "QtArvDomText.h"
#include <QUrl>
#include <QByteArray>

class QtArvDomDocument : public QtArvDomNode {
    Q_OBJECT

public:
    explicit QtArvDomDocument(QObject* parent = nullptr);
    ~QtArvDomDocument();

    QString nodeName() const override;
    QString nodeValue() const override;
    void setNodeValue(const QString& value) override;

    QtArvDomElement* getDocumentElement() const;
    QtArvDomElement* createElement(const QString& tagName);
    QtArvDomText* createTextNode(const QString& data);

    void setUrl(const QUrl& url);
    QUrl url() const;

    QByteArray getHrefData(const QString& href, qint64* size = nullptr) const;

private:
    QUrl m_url;
};
