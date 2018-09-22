#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameServerObjectBase.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/ServerObjects/CharacterFacing.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<GameServerObjectBaseInitData>
{
  using MyBase = ServerObjectInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GameServerObjectBaseInitData"; }
  static constexpr auto GetNameHash() { return 0xE8EFD458; }
  static GameServerObjectBaseInitData & GetDefault() { static GameServerObjectBaseInitData def; return def; }
};

template <>
struct StormReflTypeInfo<GameServerObjectBase>
{
  using MyBase = ServerObject;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "GameServerObjectBase"; }
  static constexpr auto GetNameHash() { return 0x25DA07B6; }
  static GameServerObjectBase & GetDefault() { static GameServerObjectBase def; return def; }
};

template <>
struct StormReflTypeInfo<GameServerObjectBase>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &GameServerObjectBase::m_Position; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerObjectBase>::field_data<0 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<GameServerObjectBase>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Position; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Position; }
  void SetDefault() { self.m_Position = StormReflTypeInfo<GameServerObjectBase>::GetDefault().m_Position; }
};

template <>
struct StormReflFuncInfo<GameServerObjectBase>
{
  using MyBase = ServerObject;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct GameServerObjectBase
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameServerObjectBase::type_info<0>
  {
    using type = ::GameServerObjectBaseInitData;
  };

  template <>
  struct GameServerObjectBase::type_info<1>
  {
    using type = ::GameServerObjectBase;
  };

}

