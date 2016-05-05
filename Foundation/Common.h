#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include <cstdint>

#include <enum\enum.h>
#include <optional\optional.hpp>


template <class T>
using Optional = nonstd::optional<T>;

#include "Foundation\Singleton\Singleton.h"
#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\ReflectionCommon.h"

