#pragma once

#define _SCL_SECURE_NO_WARNINGS  

#include "Foundation/Common.h"

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#ifdef ENGINE_BUILD
//#define ENGINE_EXPORT __declspec(dllexport)
#define ENGINE_EXPORT
#else
//#define ENGINE_EXPORT __declspec(dllimport)
#define ENGINE_EXPORT
#endif

