#ifndef STEELSAND_GLOBAL_H
#define STEELSAND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STEELSAND_LIBRARY)
#  define STEELSAND_EXPORT Q_DECL_EXPORT
#else
#  define STEELSAND_EXPORT Q_DECL_IMPORT
#endif

#endif // STEELSAND_GLOBAL_H
