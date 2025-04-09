// QtArvDomText.h - DOM text node
#pragma once

#include "QtArvDomCharacterData.h"

class QtArvDomText : public QtArvDomCharacterData {
    Q_OBJECT

public:
    explicit QtArvDomText(const QString& data = QString(), QObject* parent = nullptr);
    ~QtArvDomText();

    QString nodeName() const override;
    QString nodeValue() const override;
    void setNodeValue(const QString& value) override;
};
