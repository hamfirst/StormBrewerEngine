#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SharedTypes.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflEnumInfo<ChannelJoinResult>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "ChannelJoinResult"; }
  static constexpr auto GetNameHash() { return 0x94A3601C; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<0>
{
  static constexpr auto GetName() { return "kSuccess"; }
  static constexpr auto GetNameHash() { return 0xD5725AD4; }
  static constexpr auto GetValue() { return ChannelJoinResult::kSuccess; }
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<1>
{
  static constexpr auto GetName() { return "kLocked"; }
  static constexpr auto GetNameHash() { return 0x4861AB65; }
  static constexpr auto GetValue() { return ChannelJoinResult::kLocked; }
};

template <>
struct StormReflEnumInfo<ChannelJoinResult>::elems<2>
{
  static constexpr auto GetName() { return "kAlreadyIn"; }
  static constexpr auto GetNameHash() { return 0x6769BFCF; }
  static constexpr auto GetValue() { return ChannelJoinResult::kAlreadyIn; }
};

template <>
struct StormReflEnumInfo<GameState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "GameState"; }
  static constexpr auto GetNameHash() { return 0x5693636B; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameState>::elems<0>
{
  static constexpr auto GetName() { return "kWaiting"; }
  static constexpr auto GetNameHash() { return 0xD2A808C8; }
  static constexpr auto GetValue() { return GameState::kWaiting; }
};

template <>
struct StormReflEnumInfo<GameState>::elems<1>
{
  static constexpr auto GetName() { return "kCountdown"; }
  static constexpr auto GetNameHash() { return 0x991E82AA; }
  static constexpr auto GetValue() { return GameState::kCountdown; }
};

template <>
struct StormReflEnumInfo<GameState>::elems<2>
{
  static constexpr auto GetName() { return "kStarted"; }
  static constexpr auto GetNameHash() { return 0x0EE413BC; }
  static constexpr auto GetValue() { return GameState::kStarted; }
};

template <>
struct StormReflEnumInfo<GameType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "GameType"; }
  static constexpr auto GetNameHash() { return 0x83AB907E; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameType>::elems<0>
{
  static constexpr auto GetName() { return "kCasual"; }
  static constexpr auto GetNameHash() { return 0x2A113302; }
  static constexpr auto GetValue() { return GameType::kCasual; }
};

template <>
struct StormReflEnumInfo<GameType>::elems<1>
{
  static constexpr auto GetName() { return "kCompetitive"; }
  static constexpr auto GetNameHash() { return 0x76D66C73; }
  static constexpr auto GetValue() { return GameType::kCompetitive; }
};

template <>
struct StormReflEnumInfo<GameType>::elems<2>
{
  static constexpr auto GetName() { return "kPrivate"; }
  static constexpr auto GetNameHash() { return 0x687444B7; }
  static constexpr auto GetValue() { return GameType::kPrivate; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserGameInfo"; }
  static constexpr auto GetNameHash() { return 0xF088D28F; }
  static constexpr bool HasDefault() { return true; }
  static UserGameInfo & GetDefault() { static UserGameInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserGameInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserGameInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserGameInfo *>(ptr);
    if(typeid(UserGameInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserGameInfo *>(ptr);
    if(typeid(UserGameInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserGameInfo>::field_data_static<0>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserGameInfo::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameInfo *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameInfo *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfo>::field_data<0, Self> : public StormReflTypeInfo<UserGameInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<UserGameInfo>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>::field_data_static<1>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_GameServerId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x219CFC9D; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserGameInfo::m_GameServerId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserGameInfo *>(obj); return &ptr->m_GameServerId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserGameInfo *>(obj); return &ptr->m_GameServerId; }
};

template <typename Self>
struct StormReflTypeInfo<UserGameInfo>::field_data<1, Self> : public StormReflTypeInfo<UserGameInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_GameServerId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_GameServerId; }
  void SetDefault() { self.m_GameServerId = StormReflTypeInfo<UserGameInfo>::GetDefault().m_GameServerId; }
};

template <>
struct StormReflTypeInfo<UserInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserInfo"; }
  static constexpr auto GetNameHash() { return 0x34B0844E; }
  static constexpr bool HasDefault() { return true; }
  static UserInfo & GetDefault() { static UserInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserInfo *>(ptr);
    if(typeid(UserInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserInfo *>(ptr);
    if(typeid(UserInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<0, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UserInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<1, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserInfo>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Squad"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x42E66F87; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Squad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Squad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Squad; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<2, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Squad; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Squad; }
  void SetDefault() { self.m_Squad = StormReflTypeInfo<UserInfo>::GetDefault().m_Squad; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_SquadTag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_SquadTag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<3, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<UserInfo>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<4, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserInfo>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_VisibleFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B00BCD9; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_VisibleFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_VisibleFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_VisibleFlags; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<5, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_VisibleFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_VisibleFlags; }
  void SetDefault() { self.m_VisibleFlags = StormReflTypeInfo<UserInfo>::GetDefault().m_VisibleFlags; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<6, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserInfo>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<7>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Game; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Game; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<7, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserGameInfo> & Get() { return self.m_Game; }
  std::add_const_t<std::remove_reference_t<UserGameInfo>> & Get() const { return self.m_Game; }
  void SetDefault() { self.m_Game = StormReflTypeInfo<UserInfo>::GetDefault().m_Game; }
};

template <>
struct StormReflTypeInfo<UserApplication>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserApplication"; }
  static constexpr auto GetNameHash() { return 0x6E2E5A1C; }
  static constexpr bool HasDefault() { return true; }
  static UserApplication & GetDefault() { static UserApplication def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserApplication *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserApplication *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserApplication *>(ptr);
    if(typeid(UserApplication).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserApplication *>(ptr);
    if(typeid(UserApplication).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DE2A771; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserApplication *>(obj); return &ptr->m_SquadName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserApplication *>(obj); return &ptr->m_SquadName; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<0, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadName; }
  void SetDefault() { self.m_SquadName = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadName; }
};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadTag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserApplication *>(obj); return &ptr->m_SquadTag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserApplication *>(obj); return &ptr->m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<1, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<UserApplication>::field_data_static<2>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_SquadId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83727351; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserApplication::m_SquadId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserApplication *>(obj); return &ptr->m_SquadId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserApplication *>(obj); return &ptr->m_SquadId; }
};

template <typename Self>
struct StormReflTypeInfo<UserApplication>::field_data<2, Self> : public StormReflTypeInfo<UserApplication>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_SquadId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_SquadId; }
  void SetDefault() { self.m_SquadId = StormReflTypeInfo<UserApplication>::GetDefault().m_SquadId; }
};

template <>
struct StormReflTypeInfo<ChannelMember>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelMember"; }
  static constexpr auto GetNameHash() { return 0xF92F50BF; }
  static constexpr bool HasDefault() { return true; }
  static ChannelMember & GetDefault() { static ChannelMember def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChannelMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChannelMember *>(ptr);
    if(typeid(ChannelMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelMember *>(ptr);
    if(typeid(ChannelMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<0, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelMember>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_SquadTag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_SquadTag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<1, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<ChannelMember>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_VisibleFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B00BCD9; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_VisibleFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_VisibleFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_VisibleFlags; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<2, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_VisibleFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_VisibleFlags; }
  void SetDefault() { self.m_VisibleFlags = StormReflTypeInfo<ChannelMember>::GetDefault().m_VisibleFlags; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<3, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<ChannelMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<4, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<ChannelMember>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<5, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<ChannelMember>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<6, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<ChannelMember>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_MembershipFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_MembershipFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_MembershipFlags; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<7, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<ChannelMember>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<8>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Game; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_Game; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<8, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserGameInfo> & Get() { return self.m_Game; }
  std::add_const_t<std::remove_reference_t<UserGameInfo>> & Get() const { return self.m_Game; }
  void SetDefault() { self.m_Game = StormReflTypeInfo<ChannelMember>::GetDefault().m_Game; }
};

template <>
struct StormReflTypeInfo<ChannelBot>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelBot"; }
  static constexpr auto GetNameHash() { return 0x62BB25BB; }
  static constexpr bool HasDefault() { return true; }
  static ChannelBot & GetDefault() { static ChannelBot def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChannelBot *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelBot *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChannelBot *>(ptr);
    if(typeid(ChannelBot).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelBot *>(ptr);
    if(typeid(ChannelBot).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChannelBot>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelBot::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelBot *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelBot *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelBot>::field_data<0, Self> : public StormReflTypeInfo<ChannelBot>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelBot>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelBot>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_BotKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B62BB36; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelBot::m_BotKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelBot *>(obj); return &ptr->m_BotKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelBot *>(obj); return &ptr->m_BotKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelBot>::field_data<1, Self> : public StormReflTypeInfo<ChannelBot>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_BotKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_BotKey; }
  void SetDefault() { self.m_BotKey = StormReflTypeInfo<ChannelBot>::GetDefault().m_BotKey; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ChannelInfo"; }
  static constexpr auto GetNameHash() { return 0xFDE9DF80; }
  static constexpr bool HasDefault() { return true; }
  static ChannelInfo & GetDefault() { static ChannelInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ChannelInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ChannelInfo *>(ptr);
    if(typeid(ChannelInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ChannelInfo *>(ptr);
    if(typeid(ChannelInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<0, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Motd"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9492F073; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Motd; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_Motd; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_Motd; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<1, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Motd; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Motd; }
  void SetDefault() { self.m_Motd = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Motd; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<2>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_ChannelKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CD0601E; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_ChannelKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_ChannelKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_ChannelKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<2, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_ChannelKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_ChannelKey; }
  void SetDefault() { self.m_ChannelKey = StormReflTypeInfo<ChannelInfo>::GetDefault().m_ChannelKey; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Locked"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7ED9F59; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Locked; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_Locked; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_Locked; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<3, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Locked; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Locked; }
  void SetDefault() { self.m_Locked = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Locked; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<4>
{
  using member_type = RSparseList<ChannelMember>; // RSparseList<ChannelMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<ChannelMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0x3532E9AF; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<4, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<ChannelMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<ChannelMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<ChannelInfo>::field_data_static<5>
{
  using member_type = RMergeList<ChannelBot>; // RMergeList<ChannelBot>
  static constexpr auto GetName() { return "m_Bots"; }
  static constexpr auto GetType() { return "RMergeList<ChannelBot>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4F2265E2; }
  static constexpr unsigned GetTypeNameHash() { return 0x54EF326B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ChannelInfo::m_Bots; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelInfo *>(obj); return &ptr->m_Bots; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelInfo *>(obj); return &ptr->m_Bots; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelInfo>::field_data<5, Self> : public StormReflTypeInfo<ChannelInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<ChannelBot>> & Get() { return self.m_Bots; }
  std::add_const_t<std::remove_reference_t<RMergeList<ChannelBot>>> & Get() const { return self.m_Bots; }
  void SetDefault() { self.m_Bots = StormReflTypeInfo<ChannelInfo>::GetDefault().m_Bots; }
};

template <>
struct StormReflTypeInfo<SquadMember>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadMember"; }
  static constexpr auto GetNameHash() { return 0x8C56F4CB; }
  static constexpr bool HasDefault() { return true; }
  static SquadMember & GetDefault() { static SquadMember def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadMember *>(ptr);
    if(typeid(SquadMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadMember *>(ptr);
    if(typeid(SquadMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<0>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadMember *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadMember *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<0, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadMember *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadMember *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<1, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SquadMember>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Joined"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x18C25ECB; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_Joined; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadMember *>(obj); return &ptr->m_Joined; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadMember *>(obj); return &ptr->m_Joined; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<2, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Joined; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Joined; }
  void SetDefault() { self.m_Joined = StormReflTypeInfo<SquadMember>::GetDefault().m_Joined; }
};

template <>
struct StormReflTypeInfo<SquadMember>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadMember::m_MembershipFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadMember *>(obj); return &ptr->m_MembershipFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadMember *>(obj); return &ptr->m_MembershipFlags; }
};

template <typename Self>
struct StormReflTypeInfo<SquadMember>::field_data<3, Self> : public StormReflTypeInfo<SquadMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<SquadMember>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<SquadApplication>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadApplication"; }
  static constexpr auto GetNameHash() { return 0x6D305CF9; }
  static constexpr bool HasDefault() { return true; }
  static SquadApplication & GetDefault() { static SquadApplication def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadApplication *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadApplication *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadApplication *>(ptr);
    if(typeid(SquadApplication).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadApplication *>(ptr);
    if(typeid(SquadApplication).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SquadApplication>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_UserName"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAE407D67; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadApplication::m_UserName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadApplication *>(obj); return &ptr->m_UserName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadApplication *>(obj); return &ptr->m_UserName; }
};

template <typename Self>
struct StormReflTypeInfo<SquadApplication>::field_data<0, Self> : public StormReflTypeInfo<SquadApplication>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_UserName; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_UserName; }
  void SetDefault() { self.m_UserName = StormReflTypeInfo<SquadApplication>::GetDefault().m_UserName; }
};

template <>
struct StormReflTypeInfo<SquadApplication>::field_data_static<1>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadApplication::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadApplication *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadApplication *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadApplication>::field_data<1, Self> : public StormReflTypeInfo<SquadApplication>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<SquadApplication>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<SquadInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SquadInfo"; }
  static constexpr auto GetNameHash() { return 0x96994B98; }
  static constexpr bool HasDefault() { return true; }
  static SquadInfo & GetDefault() { static SquadInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SquadInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SquadInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SquadInfo *>(ptr);
    if(typeid(SquadInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SquadInfo *>(ptr);
    if(typeid(SquadInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<0, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<SquadInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Tag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF06B7364; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Tag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Tag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Tag; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<1, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Tag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Tag; }
  void SetDefault() { self.m_Tag = StormReflTypeInfo<SquadInfo>::GetDefault().m_Tag; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Motd"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9492F073; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Motd; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Motd; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Motd; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<2, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Motd; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Motd; }
  void SetDefault() { self.m_Motd = StormReflTypeInfo<SquadInfo>::GetDefault().m_Motd; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_SquadKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFDABD02B; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_SquadKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_SquadKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_SquadKey; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<3, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_SquadKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_SquadKey; }
  void SetDefault() { self.m_SquadKey = StormReflTypeInfo<SquadInfo>::GetDefault().m_SquadKey; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<4>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Locked"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA7ED9F59; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Locked; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Locked; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Locked; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<4, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Locked; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Locked; }
  void SetDefault() { self.m_Locked = StormReflTypeInfo<SquadInfo>::GetDefault().m_Locked; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<5>
{
  using member_type = RSparseList<SquadMember>; // RSparseList<SquadMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<SquadMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xAAA9B9AE; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<5, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<SquadInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<6>
{
  using member_type = RSparseList<SquadApplication>; // RSparseList<SquadApplication>
  static constexpr auto GetName() { return "m_Applicants"; }
  static constexpr auto GetType() { return "RSparseList<SquadApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF5162316; }
  static constexpr unsigned GetTypeNameHash() { return 0x730100BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Applicants; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Applicants; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Applicants; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<6, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadApplication>> & Get() { return self.m_Applicants; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadApplication>>> & Get() const { return self.m_Applicants; }
  void SetDefault() { self.m_Applicants = StormReflTypeInfo<SquadInfo>::GetDefault().m_Applicants; }
};

template <>
struct StormReflTypeInfo<SquadInfo>::field_data_static<7>
{
  using member_type = RSparseList<SquadApplication>; // RSparseList<SquadApplication>
  static constexpr auto GetName() { return "m_Requests"; }
  static constexpr auto GetType() { return "RSparseList<SquadApplication>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8DA9027F; }
  static constexpr unsigned GetTypeNameHash() { return 0x730100BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &SquadInfo::m_Requests; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SquadInfo *>(obj); return &ptr->m_Requests; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SquadInfo *>(obj); return &ptr->m_Requests; }
};

template <typename Self>
struct StormReflTypeInfo<SquadInfo>::field_data<7, Self> : public StormReflTypeInfo<SquadInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<SquadApplication>> & Get() { return self.m_Requests; }
  std::add_const_t<std::remove_reference_t<RSparseList<SquadApplication>>> & Get() const { return self.m_Requests; }
  void SetDefault() { self.m_Requests = StormReflTypeInfo<SquadInfo>::GetDefault().m_Requests; }
};

template <>
struct StormReflTypeInfo<GameMember>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameMember"; }
  static constexpr auto GetNameHash() { return 0x801E698D; }
  static constexpr bool HasDefault() { return true; }
  static GameMember & GetDefault() { static GameMember def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameMember *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameMember *>(ptr);
    if(typeid(GameMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameMember *>(ptr);
    if(typeid(GameMember).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<0, Self> : public StormReflTypeInfo<GameMember>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameMember>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<1>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<1, Self> : public StormReflTypeInfo<GameMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameMember>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_SquadTag"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x74B2CC01; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_SquadTag; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_SquadTag; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_SquadTag; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<2, Self> : public StormReflTypeInfo<GameMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_SquadTag; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_SquadTag; }
  void SetDefault() { self.m_SquadTag = StormReflTypeInfo<GameMember>::GetDefault().m_SquadTag; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<3>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Ready"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5A315CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Ready; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Ready; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Ready; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<3, Self> : public StormReflTypeInfo<GameMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Ready; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Ready; }
  void SetDefault() { self.m_Ready = StormReflTypeInfo<GameMember>::GetDefault().m_Ready; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<4>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<4, Self> : public StormReflTypeInfo<GameMember>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<GameMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<5>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<5, Self> : public StormReflTypeInfo<GameMember>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<GameMember>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<6>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<6, Self> : public StormReflTypeInfo<GameMember>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<GameMember>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<7>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<7, Self> : public StormReflTypeInfo<GameMember>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<GameMember>::GetDefault().m_Title; }
};

template <>
struct StormReflTypeInfo<GameInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInfo"; }
  static constexpr auto GetNameHash() { return 0xC4FCF600; }
  static constexpr bool HasDefault() { return true; }
  static GameInfo & GetDefault() { static GameInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInfo *>(ptr);
    if(typeid(GameInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInfo *>(ptr);
    if(typeid(GameInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<0>
{
  using member_type = REnum<GameState>; // REnum<GameState>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "REnum<GameState>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x04F17344; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<0, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<GameState>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<REnum<GameState>>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<GameInfo>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<1>
{
  using member_type = REnum<GameType>; // REnum<GameType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<GameType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xD7F14778; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<1, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<GameType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<GameType>>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<GameInfo>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<2>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Countdown"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEB4BA24D; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Countdown; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Countdown; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Countdown; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<2, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Countdown; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Countdown; }
  void SetDefault() { self.m_Countdown = StormReflTypeInfo<GameInfo>::GetDefault().m_Countdown; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_GameLeader"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC0FD933F; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_GameLeader; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_GameLeader; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_GameLeader; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<3, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_GameLeader; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_GameLeader; }
  void SetDefault() { self.m_GameLeader = StormReflTypeInfo<GameInfo>::GetDefault().m_GameLeader; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<4>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_JoinCode"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50415C3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_JoinCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_JoinCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_JoinCode; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<4, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_JoinCode; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_JoinCode; }
  void SetDefault() { self.m_JoinCode = StormReflTypeInfo<GameInfo>::GetDefault().m_JoinCode; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<5>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Password"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC3EE92FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Password; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Password; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Password; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<5, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Password; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Password; }
  void SetDefault() { self.m_Password = StormReflTypeInfo<GameInfo>::GetDefault().m_Password; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<6>
{
  using member_type = ROpaque<GameInitSettings>; // ROpaque<GameInitSettings>
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "ROpaque<GameInitSettings>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0x8A38B67D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<6, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<GameInitSettings>> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<ROpaque<GameInitSettings>>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<GameInfo>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<7>
{
  using member_type = RSparseList<GameMember>; // RSparseList<GameMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<GameMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xA023666F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<7, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<GameMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<GameMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<GameInfo>::GetDefault().m_Users; }
};

namespace StormReflFileInfo
{
  struct SharedTypes
  {
    static const int types_n = 11;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SharedTypes::type_info<0>
  {
    using type = ::UserGameInfo;
  };

  template <>
  struct SharedTypes::type_info<1>
  {
    using type = ::UserInfo;
  };

  template <>
  struct SharedTypes::type_info<2>
  {
    using type = ::UserApplication;
  };

  template <>
  struct SharedTypes::type_info<3>
  {
    using type = ::ChannelMember;
  };

  template <>
  struct SharedTypes::type_info<4>
  {
    using type = ::ChannelBot;
  };

  template <>
  struct SharedTypes::type_info<5>
  {
    using type = ::ChannelInfo;
  };

  template <>
  struct SharedTypes::type_info<6>
  {
    using type = ::SquadMember;
  };

  template <>
  struct SharedTypes::type_info<7>
  {
    using type = ::SquadApplication;
  };

  template <>
  struct SharedTypes::type_info<8>
  {
    using type = ::SquadInfo;
  };

  template <>
  struct SharedTypes::type_info<9>
  {
    using type = ::GameMember;
  };

  template <>
  struct SharedTypes::type_info<10>
  {
    using type = ::GameInfo;
  };

}

