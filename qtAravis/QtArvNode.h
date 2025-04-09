#pragma once
// QtArvNode.h - Base class for all GenICam feature nodes
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QDomElement>

class QtArvGenicam;

class QtArvNode : public QObject {
    Q_OBJECT

public:
    explicit QtArvNode(QtArvGenicam* genicam, const QDomElement& domElement, QObject* parent = nullptr);
    virtual ~QtArvNode();

    QString name() const;

    virtual QVariant read() const = 0;
    virtual bool write(const QVariant& value);

protected:
    QtArvGenicam* genicam;
    QDomElement element;
    QString nodeName;
};
