#pragma once
// QtArvCommandNode.h - Command node feature implementation
#pragma once

#include "QtArvNode.h"

class QtArvCommandNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvCommandNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvCommandNode();

    QVariant read() const override;
    bool write(const QVariant& value) override;

    bool execute();
};