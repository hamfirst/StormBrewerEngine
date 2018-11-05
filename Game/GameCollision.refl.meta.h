#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameCollision.refl.h"


template <>
struct StormReflEnumInfo<GameCollisionType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "GameCollisionType"; }
  static constexpr auto GetNameHash() { return 0x40F137B0; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameCollisionType>::elems<0>
{
  static constexpr auto GetName() { return "kCollisionSolid"; }
  static constexpr auto GetNameHash() { return 0xEF773474; }
  static constexpr auto GetValue() { return GameCollisionType::kCollisionSolid; }
};

template <>
struct StormReflEnumInfo<GameCollisionType>::elems<1>
{
  static constexpr auto GetName() { return "kCollisionOneWay"; }
  static constexpr auto GetNameHash() { return 0xCBA27C01; }
  static constexpr auto GetValue() { return GameCollisionType::kCollisionOneWay; }
};

template <>
struct StormReflEnumInfo<GameCollisionType>::elems<2>
{
  static constexpr auto GetName() { return "kCollisionDamagable"; }
  static constexpr auto GetNameHash() { return 0x5A464594; }
  static constexpr auto GetValue() { return GameCollisionType::kCollisionDamagable; }
};

namespace StormReflFileInfo
{
  struct GameCollision
  {
    static const int types_n = 0;
    template <int i> struct type_info { using type = void; };
  };

}

