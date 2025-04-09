// QtArvEnumEntryNode.h - EnumEntry node feature
#pragma once

#include "QtArvNode.h"

class QtArvEnumEntryNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvEnumEntryNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvEnumEntryNode();

    qint64 getValue(bool* ok = nullptr) const;

    QVariant read() const override;
    bool write(const QVariant& value) override;
};