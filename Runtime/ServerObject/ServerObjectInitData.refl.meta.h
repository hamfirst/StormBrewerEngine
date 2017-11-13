#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ServerObjectInitData.refl.h"


template <>
struct StormReflTypeInfo<ServerObjectInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x2D36BDE7; }
  static ServerObjectInitData & GetDefault() { static ServerObjectInitData def; return def; }
};

namespace StormReflFileInfo
{
  struct ServerObjectInitData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ServerObjectInitData::type_info<0>
  {
    using type = ::ServerObjectInitData;
  };

}

