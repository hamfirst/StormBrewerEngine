#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapEffectLayerDef.refl.h"


template <>
struct StormReflTypeInfo<MapEffectLayerInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapEffectLayerInitData"; }
  static constexpr auto GetNameHash() { return 0x14A370F8; }
  static MapEffectLayerInitData & GetDefault() { static MapEffectLayerInitData def; return def; }
};

namespace StormReflFileInfo
{
  struct MapEffectLayerDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapEffectLayerDef::type_info<0>
  {
    using type = ::MapEffectLayerInitData;
  };

}

