#pragma once

#include "QtArvGcFeatureNode.h"
#include <QString>

class QtArvGcPropertyNode;
class QtArvDevice;

class QtArvGcPort : public QtArvGcFeatureNode {
public:
    QtArvGcPort();
    ~QtArvGcPort();

    QString nodeName() const override;

    bool canAppendChild(QtArvDomNode* child) const override;

    QByteArray read(quint64 address, quint64 length);
    void write(quint64 address, const QByteArray& data);

private:
    bool useLegacyEndian(quint64 length) const;
    QtArvGcPropertyNode* m_chunkId = nullptr;
    QtArvGcPropertyNode* m_eventId = nullptr;

    mutable bool m_legacyChecked = false;
    mutable bool m_useLegacy = false;
};
