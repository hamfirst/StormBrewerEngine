#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "AnchorDef.refl.h"


template <>
struct StormReflTypeInfo<AnchorDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "AnchorDataBase"; }
  static constexpr auto GetNameHash() { return 0x474FD0AA; }
  static AnchorDataBase & GetDefault() { static AnchorDataBase def; return def; }
};

namespace StormReflFileInfo
{
  struct AnchorDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct AnchorDef::type_info<0>
  {
    using type = ::AnchorDataBase;
  };

}

