// QtArvStringNode.h - String node feature implementation
#pragma once

#include "QtArvNode.h"

class QtArvStringNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvStringNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvStringNode();

    QVariant read() const override;
    bool write(const QVariant& value) override;

    int maxLength(bool* ok = nullptr) const;
};