#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>

#include <cstdint>

#include <enum\enum.h>
#include <optional\optional.hpp>


template <class T>
using Optional = nonstd::optional<T>;

using RString = std::string;
using RFile = std::string;
using RHash = uint32_t;

#include "Foundation\Hash\Hash.h"
#include "Foundation\Reflection\ReflectionList.h"
#include "Foundation\Reflection\ReflectionMap.h"

template <class T>
using RList = RArrayList<T>;

template <class T>
using RDictionary = ReflectionMap<std::string, T>;

template <class T>
using RHashMap = ReflectionMap<RHash, T>;
