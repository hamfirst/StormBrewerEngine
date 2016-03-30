#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>

#include <stdint.h>
#include <enum/enum.h>

using r_string = std::string;
using r_file = std::string;
using r_hash = uint64_t;

template <class T>
using r_list = std::vector<T>;

template <class T>
using r_dictionary = std::unordered_map<r_hash, T>;

