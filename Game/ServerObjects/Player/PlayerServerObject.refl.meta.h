#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerServerObject.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/ServerObjects/Player/States/PlayerStateDefault.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayerServerObjectInitData>
{
  using MyBase = ServerObjectInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x3EDBCEE8; }
  static PlayerServerObjectInitData & GetDefault() { static PlayerServerObjectInitData def; return def; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>
{
  using MyBase = ServerObject;
  static constexpr int fields_n = 5 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayerServerObject"; }
  static constexpr auto GetNameHash() { return 0xC64518EC; }
  static PlayerServerObject & GetDefault() { static PlayerServerObject def; return def; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Position; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<0 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Position; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Position; }
  void SetDefault() { self.m_Position = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Position; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<1 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9DD48B4; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Velocity; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<1 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<1 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Velocity; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Velocity; }
  void SetDefault() { self.m_Velocity = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Velocity; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_OnGround"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50DDA915; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_OnGround; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<2 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_OnGround; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_OnGround; }
  void SetDefault() { self.m_OnGround = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_OnGround; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<3 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientInput> & Get() { return self.m_Input; }
  std::add_const_t<std::remove_reference_t<ClientInput>> & Get() const { return self.m_Input; }
  void SetDefault() { self.m_Input = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Input; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetPolymorphic<PlayerStateDefault>; // NetPolymorphic<PlayerStateDefault>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "NetPolymorphic<PlayerStateDefault>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xF45D28F9; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<4 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<PlayerStateDefault>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<PlayerStateDefault>>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_State; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>
{
  using MyBase = ServerObject;
  static constexpr int funcs_n = 1 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<ServerObject>::funcs_n>
{
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandlePlaceholderEvent"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB51A771F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<ServerObject>::funcs_n; }
  static constexpr auto GetFunctionPtr() { return &PlayerServerObject::HandlePlaceholderEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<ServerObject>::funcs_n>::param_info<0>
{
  using param_type = const PlaceholderEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "const PlaceholderEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xB0413EBA; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<ServerObject>::funcs_n>::param_info<1>
{
  using param_type = GameLogicContainer &;
  static constexpr auto GetName() { return "game_container"; }
  static constexpr auto GetType() { return "GameLogicContainer &"; }
  static constexpr unsigned GetNameHash() { return 0x15042D19; }
  static constexpr unsigned GetTypeNameHash() { return 0xBFBDFC4E; }
};

namespace StormReflFileInfo
{
  struct PlayerServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerServerObject::type_info<0>
  {
    using type = ::PlayerServerObjectInitData;
  };

  template <>
  struct PlayerServerObject::type_info<1>
  {
    using type = ::PlayerServerObject;
  };

}

