#pragma once
// QtArvGenicam.h - Qt C++ wrapper for GenICam XML
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QMap>
#include <QSharedPointer>
#include <QDomDocument>

class QtArvDevice;
class QtArvNode;

class QtArvGenicam : public QObject {
    Q_OBJECT

public:
    enum class CachePolicy {
        Disabled,
        Enabled
    };

    explicit QtArvGenicam(QtArvDevice* device, const QByteArray& xmlData, QObject* parent = nullptr);
    ~QtArvGenicam();

    QtArvNode* getNode(const QString& name) const;
    void registerFeatureNode(const QString& name, QtArvNode* node);

    void setCachePolicy(CachePolicy policy);
    CachePolicy getCachePolicy() const;

    QStringList getAllFeatureNames() const;

private:
    bool parseXml(const QByteArray& xml);

    QtArvDevice* device = nullptr;
    QByteArray xml;
    QMap<QString, QSharedPointer<QtArvNode>> nodeMap;
    QDomDocument dom;
    CachePolicy cachePolicy = CachePolicy::Disabled;
};
