// QtArvDomNode.h - Base class for all DOM nodes
#pragma once

#include <QObject>
#include <QString>
#include <QVector>

class QtArvDomDocument;

class QtArvDomNode : public QObject {
    Q_OBJECT

public:
    explicit QtArvDomNode(QObject* parent = nullptr);
    virtual ~QtArvDomNode();

    virtual QString nodeName() const = 0;
    virtual QString nodeValue() const = 0;
    virtual void setNodeValue(const QString& value) = 0;

    QtArvDomNode* parentNode() const;
    QtArvDomNode* firstChild() const;
    QtArvDomNode* lastChild() const;
    QtArvDomNode* previousSibling() const;
    QtArvDomNode* nextSibling() const;

    QVector<QtArvDomNode*> childNodes() const;
    QtArvDomDocument* ownerDocument() const;

    void appendChild(QtArvDomNode* child);
    void insertBefore(QtArvDomNode* newChild, QtArvDomNode* refChild);
    QtArvDomNode* removeChild(QtArvDomNode* child);
    QtArvDomNode* replaceChild(QtArvDomNode* newChild, QtArvDomNode* oldChild);

    bool hasChildNodes() const;

signals:
    void domChanged();

protected:
    void notifyDomChanged();

private:
    QtArvDomNode* m_parent = nullptr;
    QtArvDomNode* m_firstChild = nullptr;
    QtArvDomNode* m_lastChild = nullptr;
    QtArvDomNode* m_prevSibling = nullptr;
    QtArvDomNode* m_nextSibling = nullptr;

    QVector<QtArvDomNode*> m_children;
};
