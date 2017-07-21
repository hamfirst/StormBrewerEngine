#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ComponentInitData.refl.h"


template <>
struct StormReflTypeInfo<ComponentInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ComponentInitData"; }
  static constexpr auto GetNameHash() { return 0x6DB2F865; }
  static ComponentInitData & GetDefault() { static ComponentInitData def; return def; }
};

namespace StormReflFileInfo
{
  struct ComponentInitData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ComponentInitData::type_info<0>
  {
    using type = ::ComponentInitData;
  };

}

