// QtArvEnumUtil.h - Enum-to-string utilities for qtAravis
#pragma once

#include <QString>

enum class QtArvAuto {
    Off,
    Once,
    Continuous
};

enum class QtArvAcquisitionMode {
    Continuous,
    SingleFrame,
    MultiFrame
};

enum class QtArvExposureMode {
    Off,
    Timed,
    TriggerWidth,
    TriggerControlled
};

enum class QtArvGcAccessMode {
    RO,
    WO,
    RW
};

class QtArvEnumUtil {
public:
    static QString toString(QtArvAuto value);
    static QtArvAuto fromStringToAuto(const QString& str);

    static QString toString(QtArvAcquisitionMode mode);
    static QtArvAcquisitionMode fromStringToAcquisitionMode(const QString& str);

    static QString toString(QtArvExposureMode mode);
    static QtArvExposureMode fromStringToExposureMode(const QString& str);

    static QString toString(QtArvGcAccessMode mode);
    static QtArvGcAccessMode fromStringToGcAccessMode(const QString& str);
};