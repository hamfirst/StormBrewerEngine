#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateDefault.refl.h"


template <>
struct StormReflTypeInfo<PlayerStateDefault>
{
  using MyBase = PlayerStateBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerStateDefault"; }
  static constexpr auto GetNameHash() { return 0x9FE939CC; }
  static PlayerStateDefault & GetDefault() { static PlayerStateDefault def; return def; }
};

namespace StormReflFileInfo
{
  struct PlayerStateDefault
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateDefault::type_info<0>
  {
    using type = ::PlayerStateDefault;
  };

}

