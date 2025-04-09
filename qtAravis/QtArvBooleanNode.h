// QtArvBooleanNode.h - Boolean node feature implementation
#pragma once

#include "QtArvNode.h"

class QtArvBooleanNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvBooleanNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvBooleanNode();

    QVariant read() const override;
    bool write(const QVariant& value) override;

private:
    qint64 onValue() const;
    qint64 offValue() const;
};