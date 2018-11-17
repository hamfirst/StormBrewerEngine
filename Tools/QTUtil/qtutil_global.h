#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(QTUTIL_LIB)
#  define QTUTIL_EXPORT Q_DECL_EXPORT
# else
#  define QTUTIL_EXPORT Q_DECL_IMPORT
# endif
#else
# define QTUTIL_EXPORT
#endif
