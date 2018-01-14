#pragma once

#include <cassert>

#define ASSERT(condition, ...) if(!(condition)) { printf("Assertion failed: %s\n", __VA_ARGS__); assert(false); }

