#pragma once
// QtArvIntegerNode.h - Integer node feature implementation
#pragma once

#include "QtArvNode.h"

class QtArvIntegerNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvIntegerNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvIntegerNode();

    QVariant read() const override;
    bool write(const QVariant& value) override;

    qint64 minimum(bool* ok = nullptr) const;
    qint64 maximum(bool* ok = nullptr) const;
    qint64 increment(bool* ok = nullptr) const;

    QString unit() const;

private:
    qint64 readIntegerElement(const QString& tagName, bool* ok = nullptr) const;
};
