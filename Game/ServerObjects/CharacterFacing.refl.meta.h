#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "CharacterFacing.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflEnumInfo<CharacterFacing>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "CharacterFacing"; }
  static constexpr auto GetNameHash() { return 0x769239DF; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<CharacterFacing>::elems<0>
{
  static constexpr auto GetName() { return "kLeft"; }
  static constexpr auto GetNameHash() { return 0xD3D1260B; }
  static constexpr auto GetValue() { return CharacterFacing::kLeft; }
};

template <>
struct StormReflEnumInfo<CharacterFacing>::elems<1>
{
  static constexpr auto GetName() { return "kRight"; }
  static constexpr auto GetNameHash() { return 0x60D8F337; }
  static constexpr auto GetValue() { return CharacterFacing::kRight; }
};

template <>
struct StormReflEnumInfo<CharacterFacing>::elems<2>
{
  static constexpr auto GetName() { return "kNone"; }
  static constexpr auto GetNameHash() { return 0xD626C1AC; }
  static constexpr auto GetValue() { return CharacterFacing::kNone; }
};

namespace StormReflFileInfo
{
  struct CharacterFacing
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

