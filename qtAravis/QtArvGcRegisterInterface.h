#pragma once

#include <QByteArray>

class QtArvGcRegisterInterface {
public:
    virtual ~QtArvGcRegisterInterface() {}

    virtual QByteArray read() const = 0;
    virtual void write(const QByteArray& buffer) = 0;

    virtual quint64 address() const = 0;
    virtual quint64 length() const = 0;
};
