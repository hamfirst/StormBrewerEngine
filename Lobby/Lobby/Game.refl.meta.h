#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Game.refl.h"
#include "SharedTypes.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<GameUserJoinInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameUserJoinInfo"; }
  static constexpr auto GetNameHash() { return 0x40244485; }
  static constexpr bool HasDefault() { return true; }
  static GameUserJoinInfo & GetDefault() { static GameUserJoinInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameUserJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameUserJoinInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameUserJoinInfo *>(ptr);
    if(typeid(GameUserJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameUserJoinInfo *>(ptr);
    if(typeid(GameUserJoinInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<0, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<1, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<2>
{
  using member_type = UserInfo; // UserInfo
  static constexpr auto GetName() { return "m_UserInfo"; }
  static constexpr auto GetType() { return "UserInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3BEA3236; }
  static constexpr unsigned GetTypeNameHash() { return 0x34B0844E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_UserInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_UserInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_UserInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<2, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserInfo> & Get() { return self.m_UserInfo; }
  std::add_const_t<std::remove_reference_t<UserInfo>> & Get() const { return self.m_UserInfo; }
  void SetDefault() { self.m_UserInfo = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_UserInfo; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3EE92FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_Password; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_Password; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_Password; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<3, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Password; }
  void SetDefault() { self.m_Password = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_Password; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Observer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6D4390C9; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_Observer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_Observer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_Observer; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<4, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Observer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Observer; }
  void SetDefault() { self.m_Observer = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_Observer; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<5>
{
  using member_type = LobbyGameType; // LobbyGameType
  static constexpr auto GetName() { return "m_IntendedType"; }
  static constexpr auto GetType() { return "LobbyGameType"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01E307B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x15A65C86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_IntendedType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_IntendedType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_IntendedType; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<5, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, LobbyGameType> & Get() { return self.m_IntendedType; }
  std::add_const_t<std::remove_reference_t<LobbyGameType>> & Get() const { return self.m_IntendedType; }
  void SetDefault() { self.m_IntendedType = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_IntendedType; }
};

template <>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data_static<6>
{
  using member_type = UserZoneInfo; // UserZoneInfo
  static constexpr auto GetName() { return "m_ZoneInfo"; }
  static constexpr auto GetType() { return "UserZoneInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFAB36D71; }
  static constexpr unsigned GetTypeNameHash() { return 0xC19DFF86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_ZoneInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_ZoneInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_ZoneInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<6, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserZoneInfo> & Get() { return self.m_ZoneInfo; }
  std::add_const_t<std::remove_reference_t<UserZoneInfo>> & Get() const { return self.m_ZoneInfo; }
  void SetDefault() { self.m_ZoneInfo = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_ZoneInfo; }
};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameUserPrivateInfo"; }
  static constexpr auto GetNameHash() { return 0xB1FB5896; }
  static constexpr bool HasDefault() { return true; }
  static GameUserPrivateInfo & GetDefault() { static GameUserPrivateInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameUserPrivateInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameUserPrivateInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameUserPrivateInfo *>(ptr);
    if(typeid(GameUserPrivateInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameUserPrivateInfo *>(ptr);
    if(typeid(GameUserPrivateInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameUserPrivateInfo::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserPrivateInfo *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserPrivateInfo *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data<0, Self> : public StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<GameUserPrivateInfo>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameUserPrivateInfo::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserPrivateInfo *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserPrivateInfo *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data<1, Self> : public StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<GameUserPrivateInfo>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_Token"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD201315B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameUserPrivateInfo::m_Token; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserPrivateInfo *>(obj); return &ptr->m_Token; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserPrivateInfo *>(obj); return &ptr->m_Token; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data<2, Self> : public StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Token; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Token; }
  void SetDefault() { self.m_Token = StormReflTypeInfo<GameUserPrivateInfo>::GetDefault().m_Token; }
};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<3>
{
  using member_type = time_t; // long
  static constexpr auto GetName() { return "m_TokenAssigned"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCCDD1026; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameUserPrivateInfo::m_TokenAssigned; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserPrivateInfo *>(obj); return &ptr->m_TokenAssigned; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserPrivateInfo *>(obj); return &ptr->m_TokenAssigned; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data<3, Self> : public StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, time_t> & Get() { return self.m_TokenAssigned; }
  std::add_const_t<std::remove_reference_t<time_t>> & Get() const { return self.m_TokenAssigned; }
  void SetDefault() { self.m_TokenAssigned = StormReflTypeInfo<GameUserPrivateInfo>::GetDefault().m_TokenAssigned; }
};

template <>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<4>
{
  using member_type = UserZoneInfo; // UserZoneInfo
  static constexpr auto GetName() { return "m_UserZoneInfo"; }
  static constexpr auto GetType() { return "UserZoneInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7E2E5D18; }
  static constexpr unsigned GetTypeNameHash() { return 0xC19DFF86; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameUserPrivateInfo::m_UserZoneInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserPrivateInfo *>(obj); return &ptr->m_UserZoneInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserPrivateInfo *>(obj); return &ptr->m_UserZoneInfo; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserPrivateInfo>::field_data<4, Self> : public StormReflTypeInfo<GameUserPrivateInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserZoneInfo> & Get() { return self.m_UserZoneInfo; }
  std::add_const_t<std::remove_reference_t<UserZoneInfo>> & Get() const { return self.m_UserZoneInfo; }
  void SetDefault() { self.m_UserZoneInfo = StormReflTypeInfo<GameUserPrivateInfo>::GetDefault().m_UserZoneInfo; }
};

template <>
struct StormReflTypeInfo<GeneratedGameUser>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GeneratedGameUser"; }
  static constexpr auto GetNameHash() { return 0xA6311D73; }
  static constexpr bool HasDefault() { return true; }
  static GeneratedGameUser & GetDefault() { static GeneratedGameUser def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GeneratedGameUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GeneratedGameUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GeneratedGameUser *>(ptr);
    if(typeid(GeneratedGameUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GeneratedGameUser *>(ptr);
    if(typeid(GeneratedGameUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GeneratedGameUser>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GeneratedGameUser::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GeneratedGameUser *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GeneratedGameUser *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GeneratedGameUser>::field_data<0, Self> : public StormReflTypeInfo<GeneratedGameUser>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GeneratedGameUser>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GeneratedGameUser>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GeneratedGameUser::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GeneratedGameUser *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GeneratedGameUser *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<GeneratedGameUser>::field_data<1, Self> : public StormReflTypeInfo<GeneratedGameUser>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<GeneratedGameUser>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<GeneratedGame>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GeneratedGame"; }
  static constexpr auto GetNameHash() { return 0x06F209E7; }
  static constexpr bool HasDefault() { return true; }
  static GeneratedGame & GetDefault() { static GeneratedGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GeneratedGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GeneratedGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GeneratedGame *>(ptr);
    if(typeid(GeneratedGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GeneratedGame *>(ptr);
    if(typeid(GeneratedGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GeneratedGame>::field_data_static<0>
{
  using member_type = std::vector<GeneratedGameUser> [2]; // std::vector<GeneratedGameUser, std::allocator<GeneratedGameUser> > [2]
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "std::vector<GeneratedGameUser, std::allocator<GeneratedGameUser> > [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xB5AD626D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GeneratedGame::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GeneratedGame *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GeneratedGame *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<GeneratedGame>::field_data<0, Self> : public StormReflTypeInfo<GeneratedGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GeneratedGameUser> [2]> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<std::vector<GeneratedGameUser> [2]>> & Get() const { return self.m_Users; }
};

template <>
struct StormReflTypeInfo<Game>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "Game"; }
  static constexpr auto GetNameHash() { return 0x83199EB2; }
  static constexpr bool HasDefault() { return false; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<Game *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const Game *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<Game *>(ptr);
    if(typeid(Game).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const Game *>(ptr);
    if(typeid(Game).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<Game>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_AssignedServer"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x090FAC25; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &Game::m_AssignedServer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_AssignedServer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_AssignedServer; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<0, Self> : public StormReflTypeInfo<Game>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_AssignedServer; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_AssignedServer; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<1>
{
  using member_type = time_t; // long
  static constexpr auto GetName() { return "m_InitTime"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4A687795; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Game::m_InitTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_InitTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_InitTime; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<1, Self> : public StormReflTypeInfo<Game>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, time_t> & Get() { return self.m_InitTime; }
  std::add_const_t<std::remove_reference_t<time_t>> & Get() const { return self.m_InitTime; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<2>
{
  using member_type = GameInfo; // GameInfo
  static constexpr auto GetName() { return "m_GameInfo"; }
  static constexpr auto GetType() { return "GameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCBA64078; }
  static constexpr unsigned GetTypeNameHash() { return 0xC4FCF600; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<2, Self> : public StormReflTypeInfo<Game>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInfo> & Get() { return self.m_GameInfo; }
  std::add_const_t<std::remove_reference_t<GameInfo>> & Get() const { return self.m_GameInfo; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<3>
{
  using member_type = time_t; // long
  static constexpr auto GetName() { return "m_GameCreateTime"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x575F4BA1; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameCreateTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameCreateTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameCreateTime; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<3, Self> : public StormReflTypeInfo<Game>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, time_t> & Get() { return self.m_GameCreateTime; }
  std::add_const_t<std::remove_reference_t<time_t>> & Get() const { return self.m_GameCreateTime; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<4>
{
  using member_type = time_t; // long
  static constexpr auto GetName() { return "m_GameEndTime"; }
  static constexpr auto GetType() { return "long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5AA89FCF; }
  static constexpr unsigned GetTypeNameHash() { return 0x3B97A968; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameEndTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameEndTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameEndTime; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<4, Self> : public StormReflTypeInfo<Game>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, time_t> & Get() { return self.m_GameEndTime; }
  std::add_const_t<std::remove_reference_t<time_t>> & Get() const { return self.m_GameEndTime; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F8ADA3B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<5, Self> : public StormReflTypeInfo<Game>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameRandomId; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<6>
{
  using member_type = std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >; // std::vector<std::pair<GameUserJoinInfo, DDSResponderData>, std::allocator<std::pair<GameUserJoinInfo, DDSResponderData> > >
  static constexpr auto GetName() { return "m_PendingJoins"; }
  static constexpr auto GetType() { return "std::vector<std::pair<GameUserJoinInfo, DDSResponderData>, std::allocator<std::pair<GameUserJoinInfo, DDSResponderData> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1291629B; }
  static constexpr unsigned GetTypeNameHash() { return 0xA6725ABE; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &Game::m_PendingJoins; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_PendingJoins; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_PendingJoins; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<6, Self> : public StormReflTypeInfo<Game>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >> & Get() { return self.m_PendingJoins; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >>> & Get() const { return self.m_PendingJoins; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<7>
{
  using member_type = GeneratedGame; // GeneratedGame
  static constexpr auto GetName() { return "m_CompetitiveGameInfo"; }
  static constexpr auto GetType() { return "GeneratedGame"; }
  static constexpr unsigned GetFieldNameHash() { return 0x293E04B4; }
  static constexpr unsigned GetTypeNameHash() { return 0x06F209E7; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &Game::m_CompetitiveGameInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_CompetitiveGameInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_CompetitiveGameInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<7, Self> : public StormReflTypeInfo<Game>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GeneratedGame> & Get() { return self.m_CompetitiveGameInfo; }
  std::add_const_t<std::remove_reference_t<GeneratedGame>> & Get() const { return self.m_CompetitiveGameInfo; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<8>
{
  using member_type = std::map<DDSKey, GameUserPrivateInfo>; // std::map<unsigned long, GameUserPrivateInfo, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameUserPrivateInfo> > >
  static constexpr auto GetName() { return "m_UserPrivateInfo"; }
  static constexpr auto GetType() { return "std::map<unsigned long, GameUserPrivateInfo, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameUserPrivateInfo> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA8188659; }
  static constexpr unsigned GetTypeNameHash() { return 0xBC1BBB77; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &Game::m_UserPrivateInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_UserPrivateInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_UserPrivateInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<8, Self> : public StormReflTypeInfo<Game>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, GameUserPrivateInfo>> & Get() { return self.m_UserPrivateInfo; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, GameUserPrivateInfo>>> & Get() const { return self.m_UserPrivateInfo; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<9>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ZoneIndex"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x524FD8A0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &Game::m_ZoneIndex; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_ZoneIndex; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_ZoneIndex; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<9, Self> : public StormReflTypeInfo<Game>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ZoneIndex; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ZoneIndex; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<10>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x721479AC; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &Game::m_ServerIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_ServerIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_ServerIp; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<10, Self> : public StormReflTypeInfo<Game>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerIp; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<11>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ServerPort"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1AB8089F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &Game::m_ServerPort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_ServerPort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_ServerPort; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<11, Self> : public StormReflTypeInfo<Game>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ServerPort; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ServerPort; }
};

template <>
struct StormReflFuncInfo<Game>
{
  using MyBase = void;
  static constexpr int funcs_n = 19;
  template <int N> struct func_data_static {};
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>
{
  using func_ptr_type = void (Game::*)(const GameInitSettings &, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "InitPrivateGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDC36491D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 0; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::InitPrivateGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<0>
{
  using param_type = const GameInitSettings &;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "const GameInitSettings &"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB959CD8; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<0>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>
{
  using func_ptr_type = void (Game::*)(const GameInitSettings &, int);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "InitCasualGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xAE6C97D6; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 1; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::InitCasualGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>::param_info<0>
{
  using param_type = const GameInitSettings &;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "const GameInitSettings &"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB959CD8; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<1>::param_info<1>
{
  using param_type = int;
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>
{
  using func_ptr_type = void (Game::*)(const GameInitSettings &, const GeneratedGame &, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "InitCompetitiveGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xF4DAB675; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 2; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::InitCompetitiveGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<0>
{
  using param_type = const GameInitSettings &;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "const GameInitSettings &"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xEB959CD8; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<1>
{
  using param_type = const GeneratedGame &;
  static constexpr auto GetName() { return "game"; }
  static constexpr auto GetType() { return "const GeneratedGame &"; }
  static constexpr unsigned GetNameHash() { return 0x232B318C; }
  static constexpr unsigned GetTypeNameHash() { return 0x6F549306; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<2>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "zone"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xA0EBC007; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<3>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "Destroy"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB3F7BFE7; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 3; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Destroy; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>
{
  using func_ptr_type = void (Game::*)(uint32_t);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetJoinCode"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2A636209; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SetJoinCode; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<4>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>
{
  using func_ptr_type = void (Game::*)(DDSKey, const std::string &, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "AssignGameServer"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x7391CC0F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::AssignGameServer; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>::param_info<1>
{
  using param_type = const std::string &;
  static constexpr auto GetName() { return "server_ip"; }
  static constexpr auto GetType() { return "const std::string &"; }
  static constexpr unsigned GetNameHash() { return 0x029E32CA; }
  static constexpr unsigned GetTypeNameHash() { return 0xBB24E617; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0x43915DCC; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>
{
  using func_ptr_type = void (Game::*)(DDSResponder &, const GameUserJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AddUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C229B19; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::AddUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>::param_info<1>
{
  using param_type = const GameUserJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const GameUserJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x79EF8F7E; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFEC3C304; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RemoveUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>
{
  using func_ptr_type = void (Game::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "ChangeReady"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x513A1CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::ChangeReady; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x289585AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<9>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "RequestReconnect"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x07DF2BD8; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestReconnect; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<9>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<9>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RequestStartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C32C475; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestStartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RequestTeamSwitch"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x42E88A62; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestTeamSwitch; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "requesting_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x2C06AEC6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "target_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x408BC0F8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC4E0A61F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDDA27521; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SendChat; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>
{
  using func_ptr_type = void (Game::*)(DDSKey, GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateSettings"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE2AE42CF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::UpdateSettings; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<1>
{
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, uint32_t, DDSKey);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "RedeemToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD02F62AE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RedeemToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "response_id"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xFBF32840; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>
{
  using func_ptr_type = void (Game::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E85F53F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleMemberUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<16>
{
  using func_ptr_type = void (Game::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleUserQuitGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD65AC9E7; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleUserQuitGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<16>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<16>::param_info<1>
{
  using param_type = bool;
  static constexpr auto GetName() { return "ban"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x62FED0E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<17>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HandleGameComplete"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x638E9039; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 17; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleGameComplete; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "HandleServerDisconnected"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x34A264B4; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 18; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleServerDisconnected; }
  template <int i>
  struct param_info { };
};

namespace StormReflFileInfo
{
  struct Game
  {
    static const int types_n = 5;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Game::type_info<0>
  {
    using type = ::GameUserJoinInfo;
  };

  template <>
  struct Game::type_info<1>
  {
    using type = ::GameUserPrivateInfo;
  };

  template <>
  struct Game::type_info<2>
  {
    using type = ::GeneratedGameUser;
  };

  template <>
  struct Game::type_info<3>
  {
    using type = ::GeneratedGame;
  };

  template <>
  struct Game::type_info<4>
  {
    using type = ::Game;
  };

}

