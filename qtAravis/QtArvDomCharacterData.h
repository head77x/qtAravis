// QtArvDomCharacterData.h - Character data DOM wrapper
#pragma once

#include <QObject>
#include <QString>

class QtArvDomCharacterData : public QObject {
    Q_OBJECT

public:
    explicit QtArvDomCharacterData(QObject* parent = nullptr);
    ~QtArvDomCharacterData();

    QString data() const;
    void setData(const QString& value);

signals:
    void nodeChanged();

private:
    QString m_data;
};
