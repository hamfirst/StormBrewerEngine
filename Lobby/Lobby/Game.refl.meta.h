#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "Game.refl.h"
#include "SharedTypes.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<GameToken>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameToken"; }
  static constexpr auto GetNameHash() { return 0xAA3710AB; }
  static constexpr bool HasDefault() { return true; }
  static GameToken & GetDefault() { static GameToken def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameToken *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameToken *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameToken *>(ptr);
    if(typeid(GameToken).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameToken *>(ptr);
    if(typeid(GameToken).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameToken>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6008E39; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameToken::m_UserKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameToken *>(obj); return &ptr->m_UserKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameToken *>(obj); return &ptr->m_UserKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameToken>::field_data<0, Self> : public StormReflTypeInfo<GameToken>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserKey; }
  void SetDefault() { self.m_UserKey = StormReflTypeInfo<GameToken>::GetDefault().m_UserKey; }
};

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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameUserJoinInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameUserJoinInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameUserJoinInfo *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameUserJoinInfo>::field_data<2, Self> : public StormReflTypeInfo<GameUserJoinInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameUserJoinInfo>::GetDefault().m_Name; }
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
  using member_type = GameInfo; // GameInfo
  static constexpr auto GetName() { return "m_GameInfo"; }
  static constexpr auto GetType() { return "GameInfo"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCBA64078; }
  static constexpr unsigned GetTypeNameHash() { return 0xC4FCF600; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<1, Self> : public StormReflTypeInfo<Game>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInfo> & Get() { return self.m_GameInfo; }
  std::add_const_t<std::remove_reference_t<GameInfo>> & Get() const { return self.m_GameInfo; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GameCreateTime"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x575F4BA1; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameCreateTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameCreateTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameCreateTime; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<2, Self> : public StormReflTypeInfo<Game>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GameCreateTime; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GameCreateTime; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_GameRandomId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0F8ADA3B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &Game::m_GameRandomId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_GameRandomId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_GameRandomId; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<3, Self> : public StormReflTypeInfo<Game>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_GameRandomId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_GameRandomId; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<4>
{
  using member_type = std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >; // std::vector<std::pair<GameUserJoinInfo, DDSResponderData>, std::allocator<std::pair<GameUserJoinInfo, DDSResponderData> > >
  static constexpr auto GetName() { return "m_PendingJoins"; }
  static constexpr auto GetType() { return "std::vector<std::pair<GameUserJoinInfo, DDSResponderData>, std::allocator<std::pair<GameUserJoinInfo, DDSResponderData> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1291629B; }
  static constexpr unsigned GetTypeNameHash() { return 0xA6725ABE; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &Game::m_PendingJoins; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_PendingJoins; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_PendingJoins; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<4, Self> : public StormReflTypeInfo<Game>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >> & Get() { return self.m_PendingJoins; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<GameUserJoinInfo, DDSResponderData> >>> & Get() const { return self.m_PendingJoins; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<5>
{
  using member_type = std::vector<DDSKey>; // std::vector<unsigned long, std::allocator<unsigned long> >
  static constexpr auto GetName() { return "m_LockedUsers"; }
  static constexpr auto GetType() { return "std::vector<unsigned long, std::allocator<unsigned long> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x451EBF78; }
  static constexpr unsigned GetTypeNameHash() { return 0x940F60C3; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &Game::m_LockedUsers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_LockedUsers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_LockedUsers; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<5, Self> : public StormReflTypeInfo<Game>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSKey>> & Get() { return self.m_LockedUsers; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSKey>>> & Get() const { return self.m_LockedUsers; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<6>
{
  using member_type = std::map<DDSKey, DDSKey>; // std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >
  static constexpr auto GetName() { return "m_MemberSubscriptionIds"; }
  static constexpr auto GetType() { return "std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8369B12E; }
  static constexpr unsigned GetTypeNameHash() { return 0x9D5C622D; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &Game::m_MemberSubscriptionIds; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_MemberSubscriptionIds; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_MemberSubscriptionIds; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<6, Self> : public StormReflTypeInfo<Game>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, DDSKey>> & Get() { return self.m_MemberSubscriptionIds; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, DDSKey>>> & Get() const { return self.m_MemberSubscriptionIds; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<7>
{
  using member_type = std::map<DDSKey, GameToken>; // std::map<unsigned long, GameToken, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameToken> > >
  static constexpr auto GetName() { return "m_Tokens"; }
  static constexpr auto GetType() { return "std::map<unsigned long, GameToken, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, GameToken> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE7654646; }
  static constexpr unsigned GetTypeNameHash() { return 0x3BCA3037; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &Game::m_Tokens; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_Tokens; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_Tokens; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<7, Self> : public StormReflTypeInfo<Game>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, GameToken>> & Get() { return self.m_Tokens; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, GameToken>>> & Get() const { return self.m_Tokens; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<8>
{
  using member_type = std::map<std::size_t, UserZoneInfo>; // std::map<unsigned long, UserZoneInfo, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, UserZoneInfo> > >
  static constexpr auto GetName() { return "m_UserZoneInfo"; }
  static constexpr auto GetType() { return "std::map<unsigned long, UserZoneInfo, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, UserZoneInfo> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7E2E5D18; }
  static constexpr unsigned GetTypeNameHash() { return 0x7E9EF307; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &Game::m_UserZoneInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_UserZoneInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_UserZoneInfo; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<8, Self> : public StormReflTypeInfo<Game>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<std::size_t, UserZoneInfo>> & Get() { return self.m_UserZoneInfo; }
  std::add_const_t<std::remove_reference_t<std::map<std::size_t, UserZoneInfo>>> & Get() const { return self.m_UserZoneInfo; }
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
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_RemoteIp"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD002B980; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &Game::m_RemoteIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_RemoteIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_RemoteIp; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<10, Self> : public StormReflTypeInfo<Game>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_RemoteIp; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_RemoteIp; }
};

template <>
struct StormReflTypeInfo<Game>::field_data_static<11>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_RemotePort"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8ED0397; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &Game::m_RemotePort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<Game *>(obj); return &ptr->m_RemotePort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const Game *>(obj); return &ptr->m_RemotePort; }
};

template <typename Self>
struct StormReflTypeInfo<Game>::field_data<11, Self> : public StormReflTypeInfo<Game>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_RemotePort; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_RemotePort; }
};

template <>
struct StormReflFuncInfo<Game>
{
  using MyBase = void;
  static constexpr int funcs_n = 21;
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
  using func_ptr_type = void (Game::*)(const GameInitSettings &);
  using return_type = void;
  static constexpr int params_n = 1;
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
struct StormReflFuncInfo<Game>::func_data_static<2>
{
  using func_ptr_type = void (Game::*)(const GameInitSettings &, std::vector<DDSKey>, int);
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
  using param_type = std::vector<DDSKey>;
  static constexpr auto GetName() { return "users"; }
  static constexpr auto GetType() { return "std::vector<DDSKey>"; }
  static constexpr unsigned GetNameHash() { return 0x1483A5E9; }
  static constexpr unsigned GetTypeNameHash() { return 0x3788A734; }
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
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "Cleanup"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x05F50D45; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 4; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Cleanup; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<5>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "Update"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x9F89304E; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 5; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::Update; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>
{
  using func_ptr_type = void (Game::*)(uint32_t);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "SetJoinCode"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x2A636209; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 6; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SetJoinCode; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<6>::param_info<0>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "join_code"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xE64D7D01; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>
{
  using func_ptr_type = void (Game::*)(DDSResponder &, const GameUserJoinInfo &);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "AddUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C229B19; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 7; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::AddUser; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>::param_info<0>
{
  using param_type = DDSResponder &;
  static constexpr auto GetName() { return "responder"; }
  static constexpr auto GetType() { return "DDSResponder &"; }
  static constexpr unsigned GetNameHash() { return 0x5F311AF7; }
  static constexpr unsigned GetTypeNameHash() { return 0xF2AB2E46; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<7>::param_info<1>
{
  using param_type = const GameUserJoinInfo &;
  static constexpr auto GetName() { return "join_info"; }
  static constexpr auto GetType() { return "const GameUserJoinInfo &"; }
  static constexpr unsigned GetNameHash() { return 0x5AD17CCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x79EF8F7E; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<8>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RemoveUser"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xFEC3C304; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 8; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RemoveUser; }
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
struct StormReflFuncInfo<Game>::func_data_static<9>
{
  using func_ptr_type = void (Game::*)(DDSKey, bool);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "ChangeReady"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x513A1CDC; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 9; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::ChangeReady; }
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
  using param_type = bool;
  static constexpr auto GetName() { return "ready"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetNameHash() { return 0x289585AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<10>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "BeginCountdown"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x895E2F74; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 10; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::BeginCountdown; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<11>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "StartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x40E81A4D; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 11; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::StartGame; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<12>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "RequestStartGame"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x8C32C475; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 12; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestStartGame; }
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
struct StormReflFuncInfo<Game>::func_data_static<13>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, int);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "RequestTeamSwitch"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x42E88A62; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 13; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RequestTeamSwitch; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "requesting_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x2C06AEC6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "target_user"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x408BC0F8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<13>::param_info<2>
{
  using param_type = int;
  static constexpr auto GetName() { return "team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetNameHash() { return 0xC4E0A61F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<14>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "RandomizeTeams"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x26B146D3; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 14; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RandomizeTeams; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 3;
  static constexpr auto GetName() { return "SendChat"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xDDA27521; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 15; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::SendChat; }
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
  using param_type = DDSKey;
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<15>::param_info<2>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "message"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xB6BD307F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<16>
{
  using func_ptr_type = void (Game::*)(DDSKey, GameInitSettings);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "UpdateSettings"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xE2AE42CF; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 16; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::UpdateSettings; }
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
  using param_type = GameInitSettings;
  static constexpr auto GetName() { return "settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetNameHash() { return 0xE545A0C5; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<17>
{
  using func_ptr_type = void (Game::*)();
  using return_type = void;
  static constexpr int params_n = 0;
  static constexpr auto GetName() { return "UpdateGameList"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xB520BF13; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 17; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::UpdateGameList; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>
{
  using func_ptr_type = void (Game::*)(DDSKey, DDSKey, uint32_t, DDSKey);
  using return_type = void;
  static constexpr int params_n = 4;
  static constexpr auto GetName() { return "RedeemToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0xD02F62AE; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 18; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::RedeemToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>::param_info<1>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>::param_info<2>
{
  using param_type = uint32_t;
  static constexpr auto GetName() { return "response_id"; }
  static constexpr auto GetType() { return "uint32_t"; }
  static constexpr unsigned GetNameHash() { return 0xFBF32840; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E2AF381; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<18>::param_info<3>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "server_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0xB459A1F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<19>
{
  using func_ptr_type = void (Game::*)(DDSKey);
  using return_type = void;
  static constexpr int params_n = 1;
  static constexpr auto GetName() { return "ExpireToken"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x6D1B9FA1; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 19; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::ExpireToken; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<19>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "token"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x5F37A13B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<20>
{
  using func_ptr_type = void (Game::*)(DDSKey, std::string);
  using return_type = void;
  static constexpr int params_n = 2;
  static constexpr auto GetName() { return "HandleMemberUpdate"; }
  static constexpr auto GetReturnType() { return "void"; }
  static constexpr unsigned GetFunctionNameHash() { return 0x4E85F53F; }
  static constexpr unsigned GetReturnTypeNameHash() { return 0xD27BD9EE; }
  static constexpr auto GetFunctionIndex() { return 20; }
  static constexpr func_ptr_type GetFunctionPtr() { return &Game::HandleMemberUpdate; }
  template <int i>
  struct param_info { };
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<20>::param_info<0>
{
  using param_type = DDSKey;
  static constexpr auto GetName() { return "user_key"; }
  static constexpr auto GetType() { return "DDSKey"; }
  static constexpr unsigned GetNameHash() { return 0x6186CA22; }
  static constexpr unsigned GetTypeNameHash() { return 0x1C5C8347; }
};

template <>
struct StormReflFuncInfo<Game>::func_data_static<20>::param_info<1>
{
  using param_type = std::string;
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::string"; }
  static constexpr unsigned GetNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0xC508D6F7; }
};

namespace StormReflFileInfo
{
  struct Game
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct Game::type_info<0>
  {
    using type = ::GameToken;
  };

  template <>
  struct Game::type_info<1>
  {
    using type = ::GameUserJoinInfo;
  };

  template <>
  struct Game::type_info<2>
  {
    using type = ::Game;
  };

}

