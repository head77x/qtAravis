#pragma once
// QtArvChunkParser.h - Qt C++ chunk data parser
#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QSharedPointer>

class QtArvGenicam;
class QtArvBuffer;

class QtArvChunkParser : public QObject {
    Q_OBJECT

public:
    explicit QtArvChunkParser(QSharedPointer<QtArvGenicam> genicam, QObject* parent = nullptr);
    ~QtArvChunkParser();

    bool getBooleanValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok = nullptr) const;
    qint64 getIntegerValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok = nullptr) const;
    double getFloatValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok = nullptr) const;
    QString getStringValue(QSharedPointer<QtArvBuffer> buffer, const QString& chunkName, bool* ok = nullptr) const;

private:
    QSharedPointer<QtArvGenicam> genicam;
};
