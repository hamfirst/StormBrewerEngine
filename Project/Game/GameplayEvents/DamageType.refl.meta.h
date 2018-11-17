#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DamageType.refl.h"


template <>
struct StormReflEnumInfo<DamageType>
{
  static constexpr int elems_n = 2;
  static constexpr auto GetName() { return "DamageType"; }
  static constexpr auto GetNameHash() { return 0x106748A4; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DamageType>::elems<0>
{
  static constexpr auto GetName() { return "kMelee"; }
  static constexpr auto GetNameHash() { return 0x1BF5FD82; }
  static constexpr auto GetValue() { return DamageType::kMelee; }
};

template <>
struct StormReflEnumInfo<DamageType>::elems<1>
{
  static constexpr auto GetName() { return "kFall"; }
  static constexpr auto GetNameHash() { return 0x52E61E6F; }
  static constexpr auto GetValue() { return DamageType::kFall; }
};

namespace StormReflFileInfo
{
  struct DamageType
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

