#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>

#include <stdint.h>
#include <enum/enum.h>

#include "Foundation\Hash\Hash.h"

using RString = std::string;
using RFile = std::string;
using RHash = uint32_t;

template <class T>
using RList = std::vector<T>;

template <class T>
using RDictionary = std::unordered_map<RHash, T>;
