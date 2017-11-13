#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapPropertiesDef.refl.h"


template <>
struct StormReflTypeInfo<MapPropertiesDef>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPropertiesDef"; }
  static constexpr auto GetNameHash() { return 0x02766CB4; }
  static MapPropertiesDef & GetDefault() { static MapPropertiesDef def; return def; }
};

namespace StormReflFileInfo
{
  struct MapPropertiesDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapPropertiesDef::type_info<0>
  {
    using type = ::MapPropertiesDef;
  };

}

