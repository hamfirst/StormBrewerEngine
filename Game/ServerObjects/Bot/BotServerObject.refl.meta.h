#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotServerObject.refl.h"
#include "Game/ServerObjects/CharacterFacing.refl.meta.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<BotServerObjectInitData>
{
  using MyBase = ServerObjectInitData;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObjectInitData"; }
  static constexpr auto GetNameHash() { return 0x1C601FCD; }
  static BotServerObjectInitData & GetDefault() { static BotServerObjectInitData def; return def; }
};

template <>
struct StormReflTypeInfo<BotServerObject>
{
  using MyBase = ServerObject;
  static constexpr int fields_n = 6 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "BotServerObject"; }
  static constexpr auto GetNameHash() { return 0xF3F6D91E; }
  static BotServerObject & GetDefault() { static BotServerObject def; return def; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Position"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB00030DB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Position; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<0 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<0 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Position; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Position; }
  void SetDefault() { self.m_Position = StormReflTypeInfo<BotServerObject>::GetDefault().m_Position; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = GameNetVec2; // IntersectionVecType<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Velocity"; }
  static constexpr auto GetType() { return "IntersectionVecType<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x48F40287; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D719CFC; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Velocity; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<1 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<1 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVec2> & Get() { return self.m_Velocity; }
  std::add_const_t<std::remove_reference_t<GameNetVec2>> & Get() const { return self.m_Velocity; }
  void SetDefault() { self.m_Velocity = StormReflTypeInfo<BotServerObject>::GetDefault().m_Velocity; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetRangedNumber<int, -1, 30>; // NetRangedNumber<int, -1, 30>
  static constexpr auto GetName() { return "m_AnimIndex"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, -1, 30>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9984B871; }
  static constexpr unsigned GetTypeNameHash() { return 0xB3BD22BD; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimIndex; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<2 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<2 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, -1, 30>> & Get() { return self.m_AnimIndex; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, -1, 30>>> & Get() const { return self.m_AnimIndex; }
  void SetDefault() { self.m_AnimIndex = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimIndex; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 31>; // NetRangedNumber<int, 0, 31>
  static constexpr auto GetName() { return "m_AnimFrame"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 31>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAC0FE3BD; }
  static constexpr unsigned GetTypeNameHash() { return 0x72324C82; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimFrame; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<3 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<3 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 31>> & Get() { return self.m_AnimFrame; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 31>>> & Get() const { return self.m_AnimFrame; }
  void SetDefault() { self.m_AnimFrame = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimFrame; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetRangedNumber<int, 0, 63>; // NetRangedNumber<int, 0, 63>
  static constexpr auto GetName() { return "m_AnimDelay"; }
  static constexpr auto GetType() { return "NetRangedNumber<int, 0, 63>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAB6D5FEB; }
  static constexpr unsigned GetTypeNameHash() { return 0x46CFECEB; }
  static constexpr auto GetFieldIndex() { return 4 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_AnimDelay; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<4 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<4 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetRangedNumber<int, 0, 63>> & Get() { return self.m_AnimDelay; }
  std::add_const_t<std::remove_reference_t<NetRangedNumber<int, 0, 63>>> & Get() const { return self.m_AnimDelay; }
  void SetDefault() { self.m_AnimDelay = StormReflTypeInfo<BotServerObject>::GetDefault().m_AnimDelay; }
};

template <>
struct StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<ServerObject>::fields_n>
{
  using member_type = NetEnum<CharacterFacing>; // NetEnum<CharacterFacing>
  static constexpr auto GetName() { return "m_Facing"; }
  static constexpr auto GetType() { return "NetEnum<CharacterFacing>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC03F5E41; }
  static constexpr unsigned GetTypeNameHash() { return 0x94981591; }
  static constexpr auto GetFieldIndex() { return 5 + StormReflTypeInfo<ServerObject>::fields_n; }
  static constexpr auto GetMemberPtr() { return &BotServerObject::m_Facing; }
};

template <typename Self>
struct StormReflTypeInfo<BotServerObject>::field_data<5 + StormReflTypeInfo<ServerObject>::fields_n, Self> : public StormReflTypeInfo<BotServerObject>::field_data_static<5 + StormReflTypeInfo<ServerObject>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, NetEnum<CharacterFacing>> & Get() { return self.m_Facing; }
  std::add_const_t<std::remove_reference_t<NetEnum<CharacterFacing>>> & Get() const { return self.m_Facing; }
  void SetDefault() { self.m_Facing = StormReflTypeInfo<BotServerObject>::GetDefault().m_Facing; }
};

template <>
struct StormReflFuncInfo<BotServerObject>
{
  using MyBase = ServerObject;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};

namespace StormReflFileInfo
{
  struct BotServerObject
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BotServerObject::type_info<0>
  {
    using type = ::BotServerObjectInitData;
  };

  template <>
  struct BotServerObject::type_info<1>
  {
    using type = ::BotServerObject;
  };

}
