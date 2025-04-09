// QtArvEnumerationNode.h - Enumeration node implementation
#pragma once

#include "QtArvNode.h"
#include <QStringList>

class QtArvEnumerationNode : public QtArvNode {
    Q_OBJECT

public:
    explicit QtArvEnumerationNode(QtArvGenicam* genicam, const QDomElement& element, QObject* parent = nullptr);
    ~QtArvEnumerationNode();

    QVariant read() const override;
    bool write(const QVariant& value) override;

    QStringList availableEntryNames() const;
    int maxEntryNameLength() const;
};
