// QtArvZip.cpp - Implementation of Qt C++ zip archive reader
#include "QtArvZip.h"
#include <QDebug>
#include <QtGlobal>
#include <QtEndian>
#include <zlib.h>
#include <cstring>

QtArvZip::QtArvZip(const QByteArray& buffer, QObject* parent)
    : QObject(parent), m_buffer(buffer) {
    parse();
}

QtArvZip::~QtArvZip() {
    qDeleteAll(m_files);
    m_files.clear();
}

QStringList QtArvZip::fileNames() const {
    return m_files.keys();
}

QByteArray QtArvZip::getFile(const QString& name) {
    QtArvZipFile* file = findFile(name);
    if (!file) return QByteArray();

    qint64 offset = getFileDataOffset(file);
    if (offset < 0 || offset + file->compressedSize > m_buffer.size()) return QByteArray();

    QByteArray raw = m_buffer.mid(offset, file->compressedSize);
    if (file->compressedSize < file->uncompressedSize) {
        QByteArray out;
        out.resize(file->uncompressedSize);
        z_stream zs{};
        zs.next_in = reinterpret_cast<Bytef*>(raw.data());
        zs.avail_in = file->compressedSize;
        zs.next_out = reinterpret_cast<Bytef*>(out.data());
        zs.avail_out = file->uncompressedSize;
        inflateInit2(&zs, -MAX_WBITS);
        inflate(&zs, Z_FINISH);
        inflateEnd(&zs);
        return out;
    }
    return raw;
}

bool QtArvZip::parse() {
    // search for end of central directory
    for (int i = m_buffer.size() - 4; i >= 0; --i) {
        if (m_buffer[i] == 0x50 && m_buffer[i + 1] == 0x4b && m_buffer[i + 2] == 0x05 && m_buffer[i + 3] == 0x06) {
            m_directoryPosition = i;
            break;
        }
    }
    if (m_directoryPosition < 0) return false;

    const char* ptr = m_buffer.constData() + m_directoryPosition;
    m_numFiles = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 10));
    m_directorySize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr + 12));
    m_directoryOffset = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr + 16));
    m_headerSize = m_directoryPosition - (m_directoryOffset + m_directorySize);

    return extractHeaderInfo();
}

bool QtArvZip::extractHeaderInfo() {
    const char* base = m_buffer.constData() + m_headerSize + m_directoryOffset;
    qint64 offset = 0;

    for (int i = 0; i < m_numFiles; ++i) {
        const char* ptr = base + offset;
        if (qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr)) != 0x02014b50) return false;

        auto* zipFile = new QtArvZipFile();
        zipFile->compressedSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr + 20));
        zipFile->uncompressedSize = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr + 24));
        zipFile->offset = qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr + 42));
        quint16 nameLen = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 28));
        zipFile->name = QString::fromUtf8(ptr + 46, nameLen);
        m_files[zipFile->name] = zipFile;

        offset += 46 + nameLen +
            qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 30)) +
            qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 32));
    }

    return true;
}

QtArvZipFile* QtArvZip::findFile(const QString& name) {
    return m_files.value(name, nullptr);
}

qint64 QtArvZip::getFileDataOffset(QtArvZipFile* file) {
    const char* ptr = m_buffer.constData() + m_headerSize + file->offset;
    if (qFromLittleEndian<quint32>(reinterpret_cast<const uchar*>(ptr)) != 0x04034b50) return -1;
    quint16 nameLen = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 26));
    quint16 extraLen = qFromLittleEndian<quint16>(reinterpret_cast<const uchar*>(ptr + 28));
    return file->offset + m_headerSize + 30 + nameLen + extraLen;
}
