#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SharedTypes.refl.h"
#include "Game/NetworkEvents/GameNetworkData.refl.meta.h"


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
struct StormReflEnumInfo<LobbyGameState>
{
  static constexpr int elems_n = 6;
  static constexpr auto GetName() { return "LobbyGameState"; }
  static constexpr auto GetNameHash() { return 0xE5631489; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<0>
{
  static constexpr auto GetName() { return "kInitializing"; }
  static constexpr auto GetNameHash() { return 0xABC68A1A; }
  static constexpr auto GetValue() { return LobbyGameState::kInitializing; }
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<1>
{
  static constexpr auto GetName() { return "kWaiting"; }
  static constexpr auto GetNameHash() { return 0xD2A808C8; }
  static constexpr auto GetValue() { return LobbyGameState::kWaiting; }
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<2>
{
  static constexpr auto GetName() { return "kCountdown"; }
  static constexpr auto GetNameHash() { return 0x991E82AA; }
  static constexpr auto GetValue() { return LobbyGameState::kCountdown; }
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<3>
{
  static constexpr auto GetName() { return "kAssigningServer"; }
  static constexpr auto GetNameHash() { return 0xF998ACB1; }
  static constexpr auto GetValue() { return LobbyGameState::kAssigningServer; }
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<4>
{
  static constexpr auto GetName() { return "kStarted"; }
  static constexpr auto GetNameHash() { return 0x0EE413BC; }
  static constexpr auto GetValue() { return LobbyGameState::kStarted; }
};

template <>
struct StormReflEnumInfo<LobbyGameState>::elems<5>
{
  static constexpr auto GetName() { return "kPostGame"; }
  static constexpr auto GetNameHash() { return 0x335EBCD3; }
  static constexpr auto GetValue() { return LobbyGameState::kPostGame; }
};

template <>
struct StormReflEnumInfo<LobbyGameType>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "LobbyGameType"; }
  static constexpr auto GetNameHash() { return 0x15A65C86; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<LobbyGameType>::elems<0>
{
  static constexpr auto GetName() { return "kCasual"; }
  static constexpr auto GetNameHash() { return 0x2A113302; }
  static constexpr auto GetValue() { return LobbyGameType::kCasual; }
};

template <>
struct StormReflEnumInfo<LobbyGameType>::elems<1>
{
  static constexpr auto GetName() { return "kCompetitive"; }
  static constexpr auto GetNameHash() { return 0x76D66C73; }
  static constexpr auto GetValue() { return LobbyGameType::kCompetitive; }
};

template <>
struct StormReflEnumInfo<LobbyGameType>::elems<2>
{
  static constexpr auto GetName() { return "kPrivate"; }
  static constexpr auto GetNameHash() { return 0x687444B7; }
  static constexpr auto GetValue() { return LobbyGameType::kPrivate; }
};

template <>
struct StormReflTypeInfo<WelcomeInfoTab>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "WelcomeInfoTab"; }
  static constexpr auto GetNameHash() { return 0x53B1D070; }
  static constexpr bool HasDefault() { return true; }
  static WelcomeInfoTab & GetDefault() { static WelcomeInfoTab def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfoTab *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfoTab *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<WelcomeInfoTab *>(ptr);
    if(typeid(WelcomeInfoTab).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const WelcomeInfoTab *>(ptr);
    if(typeid(WelcomeInfoTab).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &WelcomeInfoTab::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<WelcomeInfoTab *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const WelcomeInfoTab *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data<0, Self> : public StormReflTypeInfo<WelcomeInfoTab>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<WelcomeInfoTab>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Info"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF514A448; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &WelcomeInfoTab::m_Info; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<WelcomeInfoTab *>(obj); return &ptr->m_Info; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const WelcomeInfoTab *>(obj); return &ptr->m_Info; }
};

template <typename Self>
struct StormReflTypeInfo<WelcomeInfoTab>::field_data<1, Self> : public StormReflTypeInfo<WelcomeInfoTab>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Info; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Info; }
  void SetDefault() { self.m_Info = StormReflTypeInfo<WelcomeInfoTab>::GetDefault().m_Info; }
};

template <>
struct StormReflTypeInfo<UserGameInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
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
struct StormReflTypeInfo<UserZoneInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserZoneInfo"; }
  static constexpr auto GetNameHash() { return 0xC19DFF86; }
  static constexpr bool HasDefault() { return true; }
  static UserZoneInfo & GetDefault() { static UserZoneInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserZoneInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserZoneInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserZoneInfo *>(ptr);
    if(typeid(UserZoneInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserZoneInfo *>(ptr);
    if(typeid(UserZoneInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserZoneInfo>::field_data_static<0>
{
  using member_type = int[7]; // int[7]
  static constexpr auto GetName() { return "m_Latencies"; }
  static constexpr auto GetType() { return "int[7]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x453053FB; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9524DFA; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserZoneInfo::m_Latencies; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserZoneInfo *>(obj); return &ptr->m_Latencies; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserZoneInfo *>(obj); return &ptr->m_Latencies; }
};

template <typename Self>
struct StormReflTypeInfo<UserZoneInfo>::field_data<0, Self> : public StormReflTypeInfo<UserZoneInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int[7]> & Get() { return self.m_Latencies; }
  std::add_const_t<std::remove_reference_t<int[7]>> & Get() const { return self.m_Latencies; }
};

template <>
struct StormReflTypeInfo<UserRankInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserRankInfo"; }
  static constexpr auto GetNameHash() { return 0xFD77210F; }
  static constexpr bool HasDefault() { return true; }
  static UserRankInfo & GetDefault() { static UserRankInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserRankInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserRankInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserRankInfo *>(ptr);
    if(typeid(UserRankInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserRankInfo *>(ptr);
    if(typeid(UserRankInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserRankInfo>::field_data_static<0>
{
  using member_type = RFloat; // RNumber<float>
  static constexpr auto GetName() { return "m_Rank"; }
  static constexpr auto GetType() { return "RNumber<float>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB6E47DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x17411E4A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserRankInfo::m_Rank; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRankInfo *>(obj); return &ptr->m_Rank; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRankInfo *>(obj); return &ptr->m_Rank; }
};

template <typename Self>
struct StormReflTypeInfo<UserRankInfo>::field_data<0, Self> : public StormReflTypeInfo<UserRankInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RFloat> & Get() { return self.m_Rank; }
  std::add_const_t<std::remove_reference_t<RFloat>> & Get() const { return self.m_Rank; }
  void SetDefault() { self.m_Rank = StormReflTypeInfo<UserRankInfo>::GetDefault().m_Rank; }
};

template <>
struct StormReflTypeInfo<UserInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
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
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Platform"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCF7E04E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Platform; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Platform; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Platform; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<1, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Platform; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Platform; }
  void SetDefault() { self.m_Platform = StormReflTypeInfo<UserInfo>::GetDefault().m_Platform; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<2, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserInfo>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<3, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserInfo>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<4, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserInfo>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserInfo>::field_data_static<5>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserInfo::m_Game; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserInfo *>(obj); return &ptr->m_Game; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserInfo *>(obj); return &ptr->m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<UserInfo>::field_data<5, Self> : public StormReflTypeInfo<UserInfo>::field_data_static<5>
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
  static constexpr int fields_n = 7;
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
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<1, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<ChannelMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<2, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<ChannelMember>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<3, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<ChannelMember>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<4, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<ChannelMember>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_MembershipFlags"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DCFBCE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_MembershipFlags; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_MembershipFlags; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_MembershipFlags; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<5, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_MembershipFlags; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_MembershipFlags; }
  void SetDefault() { self.m_MembershipFlags = StormReflTypeInfo<ChannelMember>::GetDefault().m_MembershipFlags; }
};

template <>
struct StormReflTypeInfo<ChannelMember>::field_data_static<6>
{
  using member_type = UserGameInfo; // UserGameInfo
  static constexpr auto GetName() { return "m_Game"; }
  static constexpr auto GetType() { return "UserGameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1DB6A493; }
  static constexpr unsigned GetTypeNameHash() { return 0xF088D28F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &ChannelMember::m_Game; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ChannelMember *>(obj); return &ptr->m_Game; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ChannelMember *>(obj); return &ptr->m_Game; }
};

template <typename Self>
struct StormReflTypeInfo<ChannelMember>::field_data<6, Self> : public StormReflTypeInfo<ChannelMember>::field_data_static<6>
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
struct StormReflTypeInfo<GameListGame>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameListGame"; }
  static constexpr auto GetNameHash() { return 0xDF3C3C99; }
  static constexpr bool HasDefault() { return true; }
  static GameListGame & GetDefault() { static GameListGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameListGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameListGame *>(ptr);
    if(typeid(GameListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameListGame *>(ptr);
    if(typeid(GameListGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameListGame>::field_data_static<0>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_JoinCode"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x50415C3C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameListGame::m_JoinCode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameListGame *>(obj); return &ptr->m_JoinCode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameListGame *>(obj); return &ptr->m_JoinCode; }
};

template <typename Self>
struct StormReflTypeInfo<GameListGame>::field_data<0, Self> : public StormReflTypeInfo<GameListGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_JoinCode; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_JoinCode; }
  void SetDefault() { self.m_JoinCode = StormReflTypeInfo<GameListGame>::GetDefault().m_JoinCode; }
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
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_Ready"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA5A315CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Ready; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Ready; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Ready; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<2, Self> : public StormReflTypeInfo<GameMember>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_Ready; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_Ready; }
  void SetDefault() { self.m_Ready = StormReflTypeInfo<GameMember>::GetDefault().m_Ready; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<3, Self> : public StormReflTypeInfo<GameMember>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<GameMember>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<4, Self> : public StormReflTypeInfo<GameMember>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<GameMember>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<5>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<5, Self> : public StormReflTypeInfo<GameMember>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<GameMember>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<6>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<6, Self> : public StormReflTypeInfo<GameMember>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<GameMember>::GetDefault().m_Title; }
};

template <>
struct StormReflTypeInfo<GameMember>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameMember::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameMember *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameMember *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<GameMember>::field_data<7, Self> : public StormReflTypeInfo<GameMember>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<GameMember>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<GameInfoTeamSizes>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInfoTeamSizes"; }
  static constexpr auto GetNameHash() { return 0x69C9BF6C; }
  static constexpr bool HasDefault() { return true; }
  static GameInfoTeamSizes & GetDefault() { static GameInfoTeamSizes def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInfoTeamSizes *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInfoTeamSizes *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInfoTeamSizes *>(ptr);
    if(typeid(GameInfoTeamSizes).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInfoTeamSizes *>(ptr);
    if(typeid(GameInfoTeamSizes).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameInfoTeamSizes>::field_data_static<0>
{
  using member_type = int[2]; // int[2]
  static constexpr auto GetName() { return "m_MaxTeamSizes"; }
  static constexpr auto GetType() { return "int[2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x810DE47B; }
  static constexpr unsigned GetTypeNameHash() { return 0xC425B9BF; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInfoTeamSizes::m_MaxTeamSizes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfoTeamSizes *>(obj); return &ptr->m_MaxTeamSizes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfoTeamSizes *>(obj); return &ptr->m_MaxTeamSizes; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfoTeamSizes>::field_data<0, Self> : public StormReflTypeInfo<GameInfoTeamSizes>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int[2]> & Get() { return self.m_MaxTeamSizes; }
  std::add_const_t<std::remove_reference_t<int[2]>> & Get() const { return self.m_MaxTeamSizes; }
};

template <>
struct StormReflTypeInfo<GameInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 9;
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
  using member_type = REnum<LobbyGameState>; // REnum<LobbyGameState>
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "REnum<LobbyGameState>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xB1845981; }
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
  match_const_t<Self, REnum<LobbyGameState>> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<REnum<LobbyGameState>>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<GameInfo>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<1>
{
  using member_type = REnum<LobbyGameType>; // REnum<LobbyGameType>
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "REnum<LobbyGameType>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x7214B3C5; }
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
  match_const_t<Self, REnum<LobbyGameType>> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<REnum<LobbyGameType>>> & Get() const { return self.m_Type; }
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
  using member_type = ROpaque<GameInfoTeamSizes>; // ROpaque<GameInfoTeamSizes>
  static constexpr auto GetName() { return "m_TeamSizes"; }
  static constexpr auto GetType() { return "ROpaque<GameInfoTeamSizes>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27BB0D16; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E117FD7; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_TeamSizes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_TeamSizes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_TeamSizes; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<7, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ROpaque<GameInfoTeamSizes>> & Get() { return self.m_TeamSizes; }
  std::add_const_t<std::remove_reference_t<ROpaque<GameInfoTeamSizes>>> & Get() const { return self.m_TeamSizes; }
  void SetDefault() { self.m_TeamSizes = StormReflTypeInfo<GameInfo>::GetDefault().m_TeamSizes; }
};

template <>
struct StormReflTypeInfo<GameInfo>::field_data_static<8>
{
  using member_type = RSparseList<GameMember>; // RSparseList<GameMember>
  static constexpr auto GetName() { return "m_Users"; }
  static constexpr auto GetType() { return "RSparseList<GameMember>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99B53589; }
  static constexpr unsigned GetTypeNameHash() { return 0xA023666F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameInfo::m_Users; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInfo *>(obj); return &ptr->m_Users; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInfo *>(obj); return &ptr->m_Users; }
};

template <typename Self>
struct StormReflTypeInfo<GameInfo>::field_data<8, Self> : public StormReflTypeInfo<GameInfo>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RSparseList<GameMember>> & Get() { return self.m_Users; }
  std::add_const_t<std::remove_reference_t<RSparseList<GameMember>>> & Get() const { return self.m_Users; }
  void SetDefault() { self.m_Users = StormReflTypeInfo<GameInfo>::GetDefault().m_Users; }
};

template <>
struct StormReflTypeInfo<UserPersistent>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserPersistent"; }
  static constexpr auto GetNameHash() { return 0x68592B2E; }
  static constexpr bool HasDefault() { return true; }
  static UserPersistent & GetDefault() { static UserPersistent def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserPersistent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserPersistent *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserPersistent *>(ptr);
    if(typeid(UserPersistent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserPersistent *>(ptr);
    if(typeid(UserPersistent).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserLocalData>
{
  using MyBase = void;
  static constexpr int fields_n = 13;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserLocalData"; }
  static constexpr auto GetNameHash() { return 0xA3E62FB5; }
  static constexpr bool HasDefault() { return true; }
  static UserLocalData & GetDefault() { static UserLocalData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserLocalData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserLocalData *>(ptr);
    if(typeid(UserLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserLocalData *>(ptr);
    if(typeid(UserLocalData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<0, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<UserLocalData>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<1>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<1, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<UserLocalData>::GetDefault().m_UserKey; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<2>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Platform"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCF7E04E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Platform; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Platform; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Platform; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<2, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Platform; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Platform; }
  void SetDefault() { self.m_Platform = StormReflTypeInfo<UserLocalData>::GetDefault().m_Platform; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<3>
{
  using member_type = RKey; // RNumber<unsigned long>
  static constexpr auto GetName() { return "m_PlatformId"; }
  static constexpr auto GetType() { return "RNumber<unsigned long>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0ED94F3C; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD825A3A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_PlatformId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_PlatformId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_PlatformId; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<3, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RKey> & Get() { return self.m_PlatformId; }
  std::add_const_t<std::remove_reference_t<RKey>> & Get() const { return self.m_PlatformId; }
  void SetDefault() { self.m_PlatformId = StormReflTypeInfo<UserLocalData>::GetDefault().m_PlatformId; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<4>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<4, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<UserLocalData>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<5>
{
  using member_type = RMap<uint32_t, UserRankInfo>; // RMap<unsigned int, UserRankInfo>
  static constexpr auto GetName() { return "m_RankInfo"; }
  static constexpr auto GetType() { return "RMap<unsigned int, UserRankInfo>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC659B3F8; }
  static constexpr unsigned GetTypeNameHash() { return 0xB9C97FF6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_RankInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_RankInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_RankInfo; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<5, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMap<uint32_t, UserRankInfo>> & Get() { return self.m_RankInfo; }
  std::add_const_t<std::remove_reference_t<RMap<uint32_t, UserRankInfo>>> & Get() const { return self.m_RankInfo; }
  void SetDefault() { self.m_RankInfo = StormReflTypeInfo<UserLocalData>::GetDefault().m_RankInfo; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<6>
{
  using member_type = UserPersistent; // UserPersistent
  static constexpr auto GetName() { return "m_Persistent"; }
  static constexpr auto GetType() { return "UserPersistent"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2DA59512; }
  static constexpr unsigned GetTypeNameHash() { return 0x68592B2E; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Persistent; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Persistent; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Persistent; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<6, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, UserPersistent> & Get() { return self.m_Persistent; }
  std::add_const_t<std::remove_reference_t<UserPersistent>> & Get() const { return self.m_Persistent; }
  void SetDefault() { self.m_Persistent = StormReflTypeInfo<UserLocalData>::GetDefault().m_Persistent; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<7>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Icon"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5B09BCC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Icon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Icon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Icon; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<7, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Icon; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Icon; }
  void SetDefault() { self.m_Icon = StormReflTypeInfo<UserLocalData>::GetDefault().m_Icon; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<8>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_IconList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFCEA1A36; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_IconList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_IconList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_IconList; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<8, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_IconList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_IconList; }
  void SetDefault() { self.m_IconList = StormReflTypeInfo<UserLocalData>::GetDefault().m_IconList; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<9>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Title"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA600E80B; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Title; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Title; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Title; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<9, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Title; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Title; }
  void SetDefault() { self.m_Title = StormReflTypeInfo<UserLocalData>::GetDefault().m_Title; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<10>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_TitleList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xABBF57E2; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_TitleList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_TitleList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_TitleList; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<10, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_TitleList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_TitleList; }
  void SetDefault() { self.m_TitleList = StormReflTypeInfo<UserLocalData>::GetDefault().m_TitleList; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<11>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<11, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<UserLocalData>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<UserLocalData>::field_data_static<12>
{
  using member_type = RMergeList<RInt>; // RMergeList<RNumber<int> >
  static constexpr auto GetName() { return "m_CelebrationList"; }
  static constexpr auto GetType() { return "RMergeList<RNumber<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8471A77C; }
  static constexpr unsigned GetTypeNameHash() { return 0xA536E2BA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &UserLocalData::m_CelebrationList; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserLocalData *>(obj); return &ptr->m_CelebrationList; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserLocalData *>(obj); return &ptr->m_CelebrationList; }
};

template <typename Self>
struct StormReflTypeInfo<UserLocalData>::field_data<12, Self> : public StormReflTypeInfo<UserLocalData>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RInt>> & Get() { return self.m_CelebrationList; }
  std::add_const_t<std::remove_reference_t<RMergeList<RInt>>> & Get() const { return self.m_CelebrationList; }
  void SetDefault() { self.m_CelebrationList = StormReflTypeInfo<UserLocalData>::GetDefault().m_CelebrationList; }
};

namespace StormReflFileInfo
{
  struct SharedTypes
  {
    static const int types_n = 18;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SharedTypes::type_info<0>
  {
    using type = ::WelcomeInfoTab;
  };

  template <>
  struct SharedTypes::type_info<1>
  {
    using type = ::UserGameInfo;
  };

  template <>
  struct SharedTypes::type_info<2>
  {
    using type = ::UserZoneInfo;
  };

  template <>
  struct SharedTypes::type_info<3>
  {
    using type = ::UserRankInfo;
  };

  template <>
  struct SharedTypes::type_info<4>
  {
    using type = ::UserInfo;
  };

  template <>
  struct SharedTypes::type_info<5>
  {
    using type = ::UserApplication;
  };

  template <>
  struct SharedTypes::type_info<6>
  {
    using type = ::ChannelMember;
  };

  template <>
  struct SharedTypes::type_info<7>
  {
    using type = ::ChannelBot;
  };

  template <>
  struct SharedTypes::type_info<8>
  {
    using type = ::ChannelInfo;
  };

  template <>
  struct SharedTypes::type_info<9>
  {
    using type = ::GameListGame;
  };

  template <>
  struct SharedTypes::type_info<10>
  {
    using type = ::SquadMember;
  };

  template <>
  struct SharedTypes::type_info<11>
  {
    using type = ::SquadApplication;
  };

  template <>
  struct SharedTypes::type_info<12>
  {
    using type = ::SquadInfo;
  };

  template <>
  struct SharedTypes::type_info<13>
  {
    using type = ::GameMember;
  };

  template <>
  struct SharedTypes::type_info<14>
  {
    using type = ::GameInfoTeamSizes;
  };

  template <>
  struct SharedTypes::type_info<15>
  {
    using type = ::GameInfo;
  };

  template <>
  struct SharedTypes::type_info<16>
  {
    using type = ::UserPersistent;
  };

  template <>
  struct SharedTypes::type_info<17>
  {
    using type = ::UserLocalData;
  };

}

