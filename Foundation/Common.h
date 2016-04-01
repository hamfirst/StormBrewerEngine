#pragma once

#include <new>
#include <vector>
#include <string>
#include <unordered_map>

#include <stdint.h>
#include <enum/enum.h>

typedef const char *(*annotation_f)();

using r_string = std::string;
using r_file = std::string;
using r_hash = uint64_t;

template <class T>
using r_list = std::vector<T>;

template <class T>
using r_dictionary = std::unordered_map<r_hash, T>;

template <int lower, int upper>
using r_int = int;

template <class T, annotation_f f>
struct annotation
{
  using type = T;
};

template <class T>
struct remove_annotation
{
  using type = T;
};

template <class T, annotation_f f>
struct remove_annotation<annotation<T, f>>
{
  using type = T;
};
