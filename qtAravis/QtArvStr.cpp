// QtArvStr.cpp - Ported from arvstr.c
#include "QtArvStr.h"
#include <QString>
#include <QByteArray>
#include <QDir>
#include <QUrl>
#include <QTextStream>
#include <QDebug>
#include <cmath>

namespace QtArvStr {

    QString strip(QString str, const QString& illegalChars, QChar replacementChar) {
        QString result;
        QChar lastAppended;

        for (int i = 0; i < str.size(); ++i) {
            QChar ch = str[i];
            if (illegalChars.contains(ch)) {
                if (!result.isEmpty() && result.back() != replacementChar && replacementChar != QChar('\0')) {
                    result.append(replacementChar);
                    lastAppended = replacementChar;
                }
            }
            else {
                result.append(ch);
                lastAppended = ch;
            }
        }
        return result.trimmed();
    }

    bool isUri(const QString& str) {
        QUrl url(str);
        return url.isValid() && url.scheme().length() > 0;
    }

    QString toUri(const QString& path) {
        if (isUri(path))
            return path;

        QFileInfo info(path);
        return QUrl::fromLocalFile(info.absoluteFilePath()).toString();
    }

    bool parseDouble(QString& str, double& outVal) {
        bool ok;
        outVal = str.toDouble(&ok);
        return ok;
    }

    int parseDoubleList(QString& str, int nValues, QVector<double>& outValues) {
        QTextStream ts(&str);
        ts.skipWhiteSpace();
        int count = 0;
        while (!ts.atEnd() && count < nValues) {
            double val;
            ts >> val;
            if (ts.status() != QTextStream::Ok) break;
            outValues.append(val);
            count++;
            ts.skipWhiteSpace();
            if (ts.read(1) != ",")
                ts.seek(ts.pos() - 1);
        }
        return count;
    }

    QString hexDump(const QByteArray& data) {
        QString dump;
        QTextStream ts(&dump);
        for (int i = 0; i < data.size(); i += 16) {
            ts << QString("%1").arg(i, 8, 16, QLatin1Char('0'));
            for (int j = 0; j < 16; ++j) {
                if (i + j < data.size())
                    ts << QString(" %1").arg(static_cast<quint8>(data[i + j]), 2, 16, QLatin1Char('0'));
                else
                    ts << "   ";
            }
            ts << "  ";
            for (int j = 0; j < 16; ++j) {
                if (i + j < data.size()) {
                    char c = data[i + j];
                    ts << (c >= 32 && c < 127 ? c : '.');
                }
                else {
                    ts << ' ';
                }
            }
            ts << "\n";
        }
        return dump;
    }

} // namespace QtArvStr
