#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QTARAVIS_LIB)
#  define QTARAVIS_EXPORT Q_DECL_EXPORT
# else
#  define QTARAVIS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTARAVIS_EXPORT
#endif
