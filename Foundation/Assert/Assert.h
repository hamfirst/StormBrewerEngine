#pragma once

#include <cassert>

#ifdef _MSC_VER
#define ASSERT(condition, ...) if(!(condition)) { printf("Assertion failed: %s\n", __VA_ARGS__); assert(false); }
#else
#define ASSERT(condition, ...) assert(condition)
#endif
