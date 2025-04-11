// QtArvGcEnums.h - Enum definitions for GenICam compatibility
#pragma once

#include <QString>

enum class QtArvGcAccessMode {
    RO = 0,
    WO = 1,
    RW = 2
};

inline QString QtArvGcAccessModeToString(QtArvGcAccessMode mode) {
    switch (mode) {
    case QtArvGcAccessMode::RO: return "RO";
    case QtArvGcAccessMode::WO: return "WO";
    case QtArvGcAccessMode::RW: return "RW";
    default: return QString();
    }
}

inline QtArvGcAccessMode QtArvGcAccessModeFromString(const QString& str) {
    if (str == "RO") return QtArvGcAccessMode::RO;
    if (str == "WO") return QtArvGcAccessMode::WO;
    if (str == "RW") return QtArvGcAccessMode::RW;
    return QtArvGcAccessMode::RO; // Default fallback
}
