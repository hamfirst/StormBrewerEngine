#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerServerObject.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflEnumInfo<PlayerFacing>
{
  static constexpr int elems_n = 4;
  static constexpr auto GetName() { return "PlayerFacing"; }
  static constexpr auto GetNameHash() { return 0xA7D7409D; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<PlayerFacing>::elems<0>
{
  static constexpr auto GetName() { return "kLeft"; }
  static constexpr auto GetNameHash() { return 0xD3D1260B; }
  static constexpr auto GetValue() { return PlayerFacing::kLeft; }
};

template <>
struct StormReflEnumInfo<PlayerFacing>::elems<1>
{
  static constexpr auto GetName() { return "kRight"; }
  static constexpr auto GetNameHash() { return 0x60D8F337; }
  static constexpr auto GetValue() { return PlayerFacing::kRight; }
};

template <>
struct StormReflEnumInfo<PlayerFacing>::elems<2>
{
  static constexpr auto GetName() { return "kDown"; }
  static constexpr auto GetNameHash() { return 0xB5495158; }
  static constexpr auto GetValue() { return PlayerFacing::kDown; }
};

template <>
struct StormReflEnumInfo<PlayerFacing>::elems<3>
{
  static constexpr auto GetName() { return "kUp"; }
  static constexpr auto GetNameHash() { return 0x2C0A25FE; }
  static constexpr auto GetValue() { return PlayerFacing::kUp; }
};

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
  static constexpr int fields_n = 8 + StormReflTypeInfo<MyBase>::fields_n;
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
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
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
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
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
  using member_type = NetRangedNumber<int, -1, 30>; // NetRangedNumber<int, -1, 30>
  static constexpr auto GetName() { return "m_AnimIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9984B871; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3BD22BD; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimIndex; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<2 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, 30>> & Get() { return self.m_AnimIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, 30>>> & Get() const { return self.m_AnimIndex; }
  void SetDefault() { self.m_AnimIndex = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimIndex; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AnimFrame"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAC0FE3BD; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimFrame; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<3 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AnimFrame; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AnimFrame; }
  void SetDefault() { self.m_AnimFrame = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimFrame; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 63>; // NetRangedNumber<int, 0, 63>
  static constexpr auto GetName() { return "m_AnimDelay"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 63>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB6D5FEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x46CFECEB; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_AnimDelay; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<4 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 63>> & Get() { return self.m_AnimDelay; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 63>>> & Get() const { return self.m_AnimDelay; }
  void SetDefault() { self.m_AnimDelay = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_AnimDelay; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<5 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetEnum<PlayerFacing>; // NetEnum<PlayerFacing>
  static constexpr auto GetName() { return "m_Facing"; }
  static constexpr auto GetType() { return "NetEnum<PlayerFacing>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC03F5E41; }
  static constexpr unsigned GetTypeNameHash() { return 0x9796B667; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Facing; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<5 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<5 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<PlayerFacing>> & Get() { return self.m_Facing; }
  std::add_const_t<std::remove_reference_t<NetEnum<PlayerFacing>>> & Get() const { return self.m_Facing; }
  void SetDefault() { self.m_Facing = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Facing; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<6 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = ClientInput; // ClientInput
  static constexpr auto GetName() { return "m_Input"; }
  static constexpr auto GetType() { return "ClientInput"; }
  static constexpr unsigned GetFieldNameHash() { return 0x551EA2B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x13CC217D; }
  static constexpr auto GetFieldIndex() { return 6 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Input; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<6 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<6 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ClientInput> & Get() { return self.m_Input; }
  std::add_const_t<std::remove_reference_t<ClientInput>> & Get() const { return self.m_Input; }
  void SetDefault() { self.m_Input = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Input; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<7 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetPolymorphic<PlayerStateBase>; // NetPolymorphic<PlayerStateBase>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "NetPolymorphic<PlayerStateBase>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x44373E80; }
  static constexpr auto GetFieldIndex() { return 7 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<7 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<7 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetPolymorphic<PlayerStateBase>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<NetPolymorphic<PlayerStateBase>>> & Get() const { return self.m_State; }
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
  using func_ptr_type = bool (PlayerServerObject::*)(PlaceholderEvent &, const EventMetaData &);
  using return_type = bool;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandlePlaceholderEvent"; }
  static constexpr auto GetReturnType() { return "bool"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB51A771F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFunctionIndex() { return 0 + StormReflFuncInfo<ServerObject>::funcs_n; }
  static constexpr func_ptr_type GetFunctionPtr() { return &PlayerServerObject::HandlePlaceholderEvent; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<ServerObject>::funcs_n>::param_info<0>
{
  using param_type = PlaceholderEvent &;
  static constexpr auto GetName() { return "ev"; }
  static constexpr auto GetType() { return "PlaceholderEvent &"; }
  static constexpr unsigned GetNameHash() { return 0xE0355914; }
  static constexpr unsigned GetTypeNameHash() { return 0xF8BBABC7; }
};

template <>
struct StormReflFuncInfo<PlayerServerObject>::func_data_static<0 + StormReflFuncInfo<ServerObject>::funcs_n>::param_info<1>
{
  using param_type = const EventMetaData &;
  static constexpr auto GetName() { return "meta"; }
  static constexpr auto GetType() { return "const EventMetaData &"; }
  static constexpr unsigned GetNameHash() { return 0xD7F21435; }
  static constexpr unsigned GetTypeNameHash() { return 0x039083D7; }
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

