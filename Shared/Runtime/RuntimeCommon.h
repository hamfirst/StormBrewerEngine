#pragma once

#include "Foundation/Common.h"

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#ifdef RUNTIME_BUILD
//#define RUNTIME_EXPORT __declspec(dllexport)
#define RUNTIME_EXPORT
#else
//#define RUNTIME_EXPORT __declspec(dllimport)
#define RUNTIME_EXPORT
#endif


