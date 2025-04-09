// QtArvDomElement.h - Element node for DOM
#pragma once

#include "QtArvDomNode.h"
#include <QMap>

class QtArvDomElement : public QtArvDomNode {
    Q_OBJECT

public:
    explicit QtArvDomElement(const QString& tagName, QObject* parent = nullptr);
    ~QtArvDomElement();

    QString nodeName() const override;
    QString nodeValue() const override;
    void setNodeValue(const QString& value) override;

    QString getAttribute(const QString& name) const;
    void setAttribute(const QString& name, const QString& value);

private:
    QString m_tagName;
    QMap<QString, QString> m_attributes;
};
