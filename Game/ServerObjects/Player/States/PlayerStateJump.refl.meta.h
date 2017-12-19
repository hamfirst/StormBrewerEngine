#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateJump.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerStateJump>
{
  using MyBase = PlayerStateBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerStateJump"; }
  static constexpr auto GetNameHash() { return 0xEF7B4AE6; }
  static PlayerStateJump & GetDefault() { static PlayerStateJump def; return def; }
};

template <>
struct StormReflFuncInfo<PlayerStateJump>
{
  using MyBase = PlayerStateBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct PlayerStateJump
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateJump::type_info<0>
  {
    using type = ::PlayerStateJump;
  };

}

