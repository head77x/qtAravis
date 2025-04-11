// QtArvZip.h - Qt C++ class for extracting files from memory-resident zip archives
#pragma once

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QMap>

class QtArvZipFile {
public:
    QString name;
    size_t compressedSize;
    size_t uncompressedSize;
    qint64 offset;
};

class QtArvZip : public QObject {
    Q_OBJECT

public:
    explicit QtArvZip(const QByteArray& buffer, QObject* parent = nullptr);
    ~QtArvZip();

    QStringList fileNames() const;
    QByteArray getFile(const QString& name);

private:
    bool parse();
    bool extractHeaderInfo();
    QtArvZipFile* findFile(const QString& name);
    qint64 getFileDataOffset(QtArvZipFile* file);

private:
    QByteArray m_buffer;
    QMap<QString, QtArvZipFile*> m_files;

    qint64 m_directoryPosition = -1;
    qint64 m_directoryOffset = -1;
    qint64 m_directorySize = -1;
    int m_numFiles = 0;
    qint64 m_headerSize = 0;
};
