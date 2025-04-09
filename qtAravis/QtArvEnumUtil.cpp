// QtArvEnumUtil.cpp - Implementation of enum-string conversions
#include "QtArvEnumUtil.h"

QString QtArvEnumUtil::toString(QtArvAuto value) {
    switch (value) {
    case QtArvAuto::Off: return "Off";
    case QtArvAuto::Once: return "Once";
    case QtArvAuto::Continuous: return "Continuous";
    }
    return "Off";
}

QtArvAuto QtArvEnumUtil::fromStringToAuto(const QString& str) {
    if (str == "Once") return QtArvAuto::Once;
    if (str == "Continuous") return QtArvAuto::Continuous;
    return QtArvAuto::Off;
}

QString QtArvEnumUtil::toString(QtArvAcquisitionMode mode) {
    switch (mode) {
    case QtArvAcquisitionMode::Continuous: return "Continuous";
    case QtArvAcquisitionMode::SingleFrame: return "SingleFrame";
    case QtArvAcquisitionMode::MultiFrame: return "MultiFrame";
    }
    return "Continuous";
}

QtArvAcquisitionMode QtArvEnumUtil::fromStringToAcquisitionMode(const QString& str) {
    if (str == "SingleFrame") return QtArvAcquisitionMode::SingleFrame;
    if (str == "MultiFrame") return QtArvAcquisitionMode::MultiFrame;
    return QtArvAcquisitionMode::Continuous;
}

QString QtArvEnumUtil::toString(QtArvExposureMode mode) {
    switch (mode) {
    case QtArvExposureMode::Off: return "Off";
    case QtArvExposureMode::Timed: return "Timed";
    case QtArvExposureMode::TriggerWidth: return "TriggerWidth";
    case QtArvExposureMode::TriggerControlled: return "TriggerControlled";
    }
    return "Timed";
}

QtArvExposureMode QtArvEnumUtil::fromStringToExposureMode(const QString& str) {
    if (str == "Off") return QtArvExposureMode::Off;
    if (str == "TriggerWidth") return QtArvExposureMode::TriggerWidth;
    if (str == "TriggerControlled") return QtArvExposureMode::TriggerControlled;
    return QtArvExposureMode::Timed;
}

QString QtArvEnumUtil::toString(QtArvGcAccessMode mode) {
    switch (mode) {
    case QtArvGcAccessMode::RO: return "RO";
    case QtArvGcAccessMode::WO: return "WO";
    case QtArvGcAccessMode::RW: return "RW";
    }
    return "RO";
}

QtArvGcAccessMode QtArvEnumUtil::fromStringToGcAccessMode(const QString& str) {
    if (str == "WO") return QtArvGcAccessMode::WO;
    if (str == "RW") return QtArvGcAccessMode::RW;
    return QtArvGcAccessMode::RO;
}
