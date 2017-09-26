#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerServerObject.refl.h"
#include "Server/ServerObject/ServerObjectInitData.refl.meta.h"


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
  using member_type = GameNetVal; // NetFixedPoint<long long, 32, 16>
  static constexpr auto GetName() { return "m_InputAngle"; }
  static constexpr auto GetType() { return "NetFixedPoint<long long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x55B148EC; }
  static constexpr unsigned GetTypeNameHash() { return 0xDF428045; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_InputAngle; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<2 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_InputAngle; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_InputAngle; }
  void SetDefault() { self.m_InputAngle = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_InputAngle; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVal; // NetFixedPoint<long long, 32, 16>
  static constexpr auto GetName() { return "m_InputStrength"; }
  static constexpr auto GetType() { return "NetFixedPoint<long long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEAE7BD27; }
  static constexpr unsigned GetTypeNameHash() { return 0xDF428045; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_InputStrength; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<3 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_InputStrength; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_InputStrength; }
  void SetDefault() { self.m_InputStrength = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_InputStrength; }
};

template <>
struct StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = uint8_t; // unsigned char
  static constexpr auto GetName() { return "m_Controls"; }
  static constexpr auto GetType() { return "unsigned char"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0CC15811; }
  static constexpr unsigned GetTypeNameHash() { return 0xF80DFA26; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayerServerObject::m_Controls; }
};

template <typename Self>
struct StormReflTypeInfo<PlayerServerObject>::field_data<4 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<PlayerServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint8_t> & Get() { return self.m_Controls; }
  std::add_const_t<std::remove_reference_t<uint8_t>> & Get() const { return self.m_Controls; }
  void SetDefault() { self.m_Controls = StormReflTypeInfo<PlayerServerObject>::GetDefault().m_Controls; }
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

