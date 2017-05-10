#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PathDef.refl.h"


template <>
struct StormReflTypeInfo<PathDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PathDataBase"; }
  static constexpr auto GetNameHash() { return 0x3BD8C7EA; }
  static PathDataBase & GetDefault() { static PathDataBase def; return def; }
};

namespace StormReflFileInfo
{
  struct PathDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PathDef::type_info<0>
  {
    using type = ::PathDataBase;
  };

}

