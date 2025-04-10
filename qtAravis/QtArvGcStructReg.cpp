#include "QtArvGcStructReg.h"

QtArvGcStructReg::QtArvGcStructReg() {
    setCachable("NoCache");
}

QtArvGcStructReg::~QtArvGcStructReg() {}

QString QtArvGcStructReg::nodeName() const {
    return "StructReg";
}
