#include "QtArvGcStringReg.h"
#include <QByteArray>
#include <QDebug>
#include <cstring>

QtArvGcStringReg::QtArvGcStringReg() {}
QtArvGcStringReg::~QtArvGcStringReg() {}

QString QtArvGcStringReg::nodeName() const {
    return "StringReg";
}

QString QtArvGcStringReg::stringValue() const {
    QByteArray data = read();
    int maxLen = maxLength();
    if (data.size() > maxLen)
        data.truncate(maxLen);

    if (!data.endsWith('\0'))
        data.append('\0');

    return QString::fromUtf8(data.constData());
}

void QtArvGcStringReg::setStringValue(const QString& value) {
    int maxLen = maxLength();
    QByteArray utf8 = value.toUtf8();

    if (utf8.size() > maxLen) {
        qWarning() << "[QtArvGcStringReg] String too long for max length" << maxLen;
        return;
    }

    // Append null terminator if space allows
    if (utf8.size() < maxLen)
        utf8.append('\0');

    write(utf8);
}

int QtArvGcStringReg::maxLength() const {
    return static_cast<int>(length());
}
