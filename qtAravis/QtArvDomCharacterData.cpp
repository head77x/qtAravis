// QtArvDomCharacterData.cpp - Character data DOM wrapper implementation
#include "QtArvDomCharacterData.h"

QtArvDomCharacterData::QtArvDomCharacterData(QObject* parent)
    : QObject(parent), m_data() {
}

QtArvDomCharacterData::~QtArvDomCharacterData() {}

QString QtArvDomCharacterData::data() const {
    return m_data;
}

void QtArvDomCharacterData::setData(const QString& value) {
    if (m_data != value) {
        m_data = value;
        emit nodeChanged();
    }
}
