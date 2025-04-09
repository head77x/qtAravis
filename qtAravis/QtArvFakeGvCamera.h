// qtArvFakeGvCamera.h - Entry point declarations for Fake GVSP camera CLI
#pragma once

#include <QString>

class QtArvFakeDevice;

namespace QtArvFakeGvCameraConfig {
    extern QString interfaceAddress;
    extern QString serialNumber;
    extern QString genicamXmlPath;
    extern int gvspLossRatio;
    void parseCommandLine(int argc, char* argv[]);
    void printHelp();
}
