#ifndef GLWIDGET_GLOBAL_H
#define GLWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GLWIDGET_LIBRARY)
#  define GLWIDGET_EXPORT Q_DECL_EXPORT
#else
#  define GLWIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // GLWIDGET_GLOBAL_H
