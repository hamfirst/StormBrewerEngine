#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameServerMessages.refl.h"
#include "Game/GameNetworkData.refl.meta.h"
#include "Lobby/GameData.refl.meta.h"


template <>
struct StormReflEnumInfo<GameServerMessageType>
{
  static constexpr int elems_n = 21;
  static constexpr auto GetName() { return "GameServerMessageType"; }
  static constexpr auto GetNameHash() { return 0x51112183; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kIdentifyNew"; }
  static constexpr auto GetNameHash() { return 0x1FFFE78D; }
  static constexpr auto GetValue() { return GameServerMessageType::kIdentifyNew; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kIdentifyRelocate"; }
  static constexpr auto GetNameHash() { return 0xF85426B3; }
  static constexpr auto GetValue() { return GameServerMessageType::kIdentifyRelocate; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kRelocated"; }
  static constexpr auto GetNameHash() { return 0xE733AC14; }
  static constexpr auto GetValue() { return GameServerMessageType::kRelocated; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kPing"; }
  static constexpr auto GetNameHash() { return 0x8C63FC9E; }
  static constexpr auto GetValue() { return GameServerMessageType::kPing; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kAuthRequest"; }
  static constexpr auto GetNameHash() { return 0xE2B4C630; }
  static constexpr auto GetValue() { return GameServerMessageType::kAuthRequest; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kAuthResponse"; }
  static constexpr auto GetNameHash() { return 0x78CB96CB; }
  static constexpr auto GetValue() { return GameServerMessageType::kAuthResponse; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kAuthUser"; }
  static constexpr auto GetNameHash() { return 0x564CE318; }
  static constexpr auto GetValue() { return GameServerMessageType::kAuthUser; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kAuthUserSuccess"; }
  static constexpr auto GetNameHash() { return 0x1739B89D; }
  static constexpr auto GetValue() { return GameServerMessageType::kAuthUserSuccess; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kAuthUserFail"; }
  static constexpr auto GetNameHash() { return 0xC6D86136; }
  static constexpr auto GetValue() { return GameServerMessageType::kAuthUserFail; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kRequestTeamSwitch"; }
  static constexpr auto GetNameHash() { return 0xF6000FAC; }
  static constexpr auto GetValue() { return GameServerMessageType::kRequestTeamSwitch; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kTeamSwitch"; }
  static constexpr auto GetNameHash() { return 0x91DE20C4; }
  static constexpr auto GetValue() { return GameServerMessageType::kTeamSwitch; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kRandomizeTeams"; }
  static constexpr auto GetNameHash() { return 0xBC13DFEE; }
  static constexpr auto GetValue() { return GameServerMessageType::kRandomizeTeams; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kResetGame"; }
  static constexpr auto GetNameHash() { return 0x25940320; }
  static constexpr auto GetValue() { return GameServerMessageType::kResetGame; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kForceDisconnect"; }
  static constexpr auto GetNameHash() { return 0xB5631445; }
  static constexpr auto GetValue() { return GameServerMessageType::kForceDisconnect; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<14>
{
  static constexpr auto GetName() { return "kUserDisconnected"; }
  static constexpr auto GetNameHash() { return 0x814B2937; }
  static constexpr auto GetValue() { return GameServerMessageType::kUserDisconnected; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<15>
{
  static constexpr auto GetName() { return "kKillGame"; }
  static constexpr auto GetNameHash() { return 0xD34FC899; }
  static constexpr auto GetValue() { return GameServerMessageType::kKillGame; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<16>
{
  static constexpr auto GetName() { return "kGameScore"; }
  static constexpr auto GetNameHash() { return 0xEB1D059E; }
  static constexpr auto GetValue() { return GameServerMessageType::kGameScore; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<17>
{
  static constexpr auto GetName() { return "kUserStats"; }
  static constexpr auto GetNameHash() { return 0x1F577580; }
  static constexpr auto GetValue() { return GameServerMessageType::kUserStats; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<18>
{
  static constexpr auto GetName() { return "kRelocate"; }
  static constexpr auto GetNameHash() { return 0x84EB634C; }
  static constexpr auto GetValue() { return GameServerMessageType::kRelocate; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<19>
{
  static constexpr auto GetName() { return "kChangeCreator"; }
  static constexpr auto GetNameHash() { return 0x2CED1998; }
  static constexpr auto GetValue() { return GameServerMessageType::kChangeCreator; }
};

template <>
struct StormReflEnumInfo<GameServerMessageType>::elems<20>
{
  static constexpr auto GetName() { return "kGameResult"; }
  static constexpr auto GetNameHash() { return 0x18689A00; }
  static constexpr auto GetValue() { return GameServerMessageType::kGameResult; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerMapData"; }
  static constexpr auto GetNameHash() { return 0x0756853B; }
  static constexpr bool HasDefault() { return true; }
  static GameServerMapData & GetDefault() { static GameServerMapData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerMapData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerMapData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerMapData *>(ptr);
    if(typeid(GameServerMapData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerMapData *>(ptr);
    if(typeid(GameServerMapData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Map"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x604F6E5C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_Map; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_Map; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_Map; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<0, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Map; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Map; }
  void SetDefault() { self.m_Map = StormReflTypeInfo<GameServerMapData>::GetDefault().m_Map; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_Creator; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_Creator; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_Creator; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<1, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Creator; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Creator; }
  void SetDefault() { self.m_Creator = StormReflTypeInfo<GameServerMapData>::GetDefault().m_Creator; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GameMode"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x97E53684; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_GameMode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_GameMode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_GameMode; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<2, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GameMode; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GameMode; }
  void SetDefault() { self.m_GameMode = StormReflTypeInfo<GameServerMapData>::GetDefault().m_GameMode; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ScoreLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43D3DFC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_ScoreLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_ScoreLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_ScoreLimit; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<3, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ScoreLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ScoreLimit; }
  void SetDefault() { self.m_ScoreLimit = StormReflTypeInfo<GameServerMapData>::GetDefault().m_ScoreLimit; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TimeLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92EF9F49; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_TimeLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_TimeLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_TimeLimit; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<4, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TimeLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TimeLimit; }
  void SetDefault() { self.m_TimeLimit = StormReflTypeInfo<GameServerMapData>::GetDefault().m_TimeLimit; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_MaxPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_MaxPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_MaxPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<5, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxPlayers; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxPlayers; }
  void SetDefault() { self.m_MaxPlayers = StormReflTypeInfo<GameServerMapData>::GetDefault().m_MaxPlayers; }
};

template <>
struct StormReflTypeInfo<GameServerMapData>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxTeams"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x83718C91; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameServerMapData::m_MaxTeams; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMapData *>(obj); return &ptr->m_MaxTeams; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMapData *>(obj); return &ptr->m_MaxTeams; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMapData>::field_data<6, Self> : public StormReflTypeInfo<GameServerMapData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxTeams; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxTeams; }
  void SetDefault() { self.m_MaxTeams = StormReflTypeInfo<GameServerMapData>::GetDefault().m_MaxTeams; }
};

template <>
struct StormReflTypeInfo<GameServerIdentifyNew>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerIdentifyNew"; }
  static constexpr auto GetNameHash() { return 0xC9529D5D; }
  static constexpr bool HasDefault() { return true; }
  static GameServerIdentifyNew & GetDefault() { static GameServerIdentifyNew def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerIdentifyNew *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerIdentifyNew *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerIdentifyNew *>(ptr);
    if(typeid(GameServerIdentifyNew).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerIdentifyNew *>(ptr);
    if(typeid(GameServerIdentifyNew).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerIdentifyNew>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEEA616; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerIdentifyNew::m_Version; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerIdentifyNew *>(obj); return &ptr->m_Version; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerIdentifyNew *>(obj); return &ptr->m_Version; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerIdentifyNew>::field_data<0, Self> : public StormReflTypeInfo<GameServerIdentifyNew>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Version; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Version; }
  void SetDefault() { self.m_Version = StormReflTypeInfo<GameServerIdentifyNew>::GetDefault().m_Version; }
};

template <>
struct StormReflTypeInfo<GameServerIdentifyRelocate>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerIdentifyRelocate"; }
  static constexpr auto GetNameHash() { return 0x73E1B5B8; }
  static constexpr bool HasDefault() { return true; }
  static GameServerIdentifyRelocate & GetDefault() { static GameServerIdentifyRelocate def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerIdentifyRelocate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerIdentifyRelocate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerIdentifyRelocate *>(ptr);
    if(typeid(GameServerIdentifyRelocate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerIdentifyRelocate *>(ptr);
    if(typeid(GameServerIdentifyRelocate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerIdentifyRelocate>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_RelocationKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x780D6A5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerIdentifyRelocate::m_RelocationKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerIdentifyRelocate *>(obj); return &ptr->m_RelocationKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerIdentifyRelocate *>(obj); return &ptr->m_RelocationKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerIdentifyRelocate>::field_data<0, Self> : public StormReflTypeInfo<GameServerIdentifyRelocate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_RelocationKey; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_RelocationKey; }
  void SetDefault() { self.m_RelocationKey = StormReflTypeInfo<GameServerIdentifyRelocate>::GetDefault().m_RelocationKey; }
};

template <>
struct StormReflTypeInfo<GameServerRelocated>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerRelocated"; }
  static constexpr auto GetNameHash() { return 0x8F20A2DE; }
  static constexpr bool HasDefault() { return true; }
  static GameServerRelocated & GetDefault() { static GameServerRelocated def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerRelocated *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRelocated *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerRelocated *>(ptr);
    if(typeid(GameServerRelocated).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRelocated *>(ptr);
    if(typeid(GameServerRelocated).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerPing>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerPing"; }
  static constexpr auto GetNameHash() { return 0xEB469A74; }
  static constexpr bool HasDefault() { return true; }
  static GameServerPing & GetDefault() { static GameServerPing def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerPing *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerPing *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerPing *>(ptr);
    if(typeid(GameServerPing).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerPing *>(ptr);
    if(typeid(GameServerPing).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateRequest>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerAuthenticateRequest"; }
  static constexpr auto GetNameHash() { return 0x475F48B5; }
  static constexpr bool HasDefault() { return true; }
  static GameServerAuthenticateRequest & GetDefault() { static GameServerAuthenticateRequest def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateRequest *>(ptr);
    if(typeid(GameServerAuthenticateRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateRequest *>(ptr);
    if(typeid(GameServerAuthenticateRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateRequest>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateRequest::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateRequest *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateRequest *>(obj); return &ptr->m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateRequest>::field_data<0, Self> : public StormReflTypeInfo<GameServerAuthenticateRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<GameServerAuthenticateRequest>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerAuthenticateResponse"; }
  static constexpr auto GetNameHash() { return 0xE5BC0AEA; }
  static constexpr bool HasDefault() { return true; }
  static GameServerAuthenticateResponse & GetDefault() { static GameServerAuthenticateResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateResponse *>(ptr);
    if(typeid(GameServerAuthenticateResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateResponse *>(ptr);
    if(typeid(GameServerAuthenticateResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateResponse::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateResponse *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateResponse *>(obj); return &ptr->m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data<0, Self> : public StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<GameServerAuthenticateResponse>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateResponse::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateResponse *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateResponse *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data<1, Self> : public StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameServerAuthenticateResponse>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Zone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9E765518; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateResponse::m_Zone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateResponse *>(obj); return &ptr->m_Zone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateResponse *>(obj); return &ptr->m_Zone; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data<2, Self> : public StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Zone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Zone; }
  void SetDefault() { self.m_Zone = StormReflTypeInfo<GameServerAuthenticateResponse>::GetDefault().m_Zone; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ResourceId"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x064C957C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateResponse::m_ResourceId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateResponse *>(obj); return &ptr->m_ResourceId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateResponse *>(obj); return &ptr->m_ResourceId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data<3, Self> : public StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ResourceId; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ResourceId; }
  void SetDefault() { self.m_ResourceId = StormReflTypeInfo<GameServerAuthenticateResponse>::GetDefault().m_ResourceId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ExternalIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x371391DE; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateResponse::m_ExternalIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateResponse *>(obj); return &ptr->m_ExternalIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateResponse *>(obj); return &ptr->m_ExternalIp; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateResponse>::field_data<4, Self> : public StormReflTypeInfo<GameServerAuthenticateResponse>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ExternalIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ExternalIp; }
  void SetDefault() { self.m_ExternalIp = StormReflTypeInfo<GameServerAuthenticateResponse>::GetDefault().m_ExternalIp; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUser>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerAuthenticateUser"; }
  static constexpr auto GetNameHash() { return 0x95DB5230; }
  static constexpr bool HasDefault() { return true; }
  static GameServerAuthenticateUser & GetDefault() { static GameServerAuthenticateUser def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUser *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUser *>(ptr);
    if(typeid(GameServerAuthenticateUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUser *>(ptr);
    if(typeid(GameServerAuthenticateUser).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUser>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserToken"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x657293F6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUser::m_UserToken; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUser *>(obj); return &ptr->m_UserToken; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUser *>(obj); return &ptr->m_UserToken; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUser>::field_data<0, Self> : public StormReflTypeInfo<GameServerAuthenticateUser>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserToken; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserToken; }
  void SetDefault() { self.m_UserToken = StormReflTypeInfo<GameServerAuthenticateUser>::GetDefault().m_UserToken; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUser>::field_data_static<1>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_ResponseId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC09E75BA; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUser::m_ResponseId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUser *>(obj); return &ptr->m_ResponseId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUser *>(obj); return &ptr->m_ResponseId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUser>::field_data<1, Self> : public StormReflTypeInfo<GameServerAuthenticateUser>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_ResponseId; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_ResponseId; }
  void SetDefault() { self.m_ResponseId = StormReflTypeInfo<GameServerAuthenticateUser>::GetDefault().m_ResponseId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>
{
  using MyBase = void;
  static constexpr int fields_n = 13;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerAuthenticateUserSuccess"; }
  static constexpr auto GetNameHash() { return 0x3D23B55E; }
  static constexpr bool HasDefault() { return true; }
  static GameServerAuthenticateUserSuccess & GetDefault() { static GameServerAuthenticateUserSuccess def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUserSuccess *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUserSuccess *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUserSuccess *>(ptr);
    if(typeid(GameServerAuthenticateUserSuccess).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUserSuccess *>(ptr);
    if(typeid(GameServerAuthenticateUserSuccess).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<0>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_ResponseId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC09E75BA; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_ResponseId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_ResponseId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_ResponseId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<0, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_ResponseId; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_ResponseId; }
  void SetDefault() { self.m_ResponseId = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_ResponseId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<1, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<2>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_AccountId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBEFE92F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_AccountId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_AccountId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_AccountId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<2, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_AccountId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_AccountId; }
  void SetDefault() { self.m_AccountId = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_AccountId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<3>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<3, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<4, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<5>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Squad"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x42E66F87; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_Squad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Squad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Squad; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<5, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Squad; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Squad; }
  void SetDefault() { self.m_Squad = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_Squad; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_Creator; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Creator; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Creator; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<6, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Creator; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Creator; }
  void SetDefault() { self.m_Creator = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_Creator; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<7>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_RequiredPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF4027F0B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_RequiredPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_RequiredPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_RequiredPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<7, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_RequiredPlayers; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_RequiredPlayers; }
  void SetDefault() { self.m_RequiredPlayers = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_RequiredPlayers; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<8>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<8, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<9>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AdminLevel"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xACAEF821; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_AdminLevel; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_AdminLevel; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_AdminLevel; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<9, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AdminLevel; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AdminLevel; }
  void SetDefault() { self.m_AdminLevel = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_AdminLevel; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<10>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<10, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<11>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_NewPlayer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x313BF109; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_NewPlayer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_NewPlayer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_NewPlayer; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<11, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_NewPlayer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_NewPlayer; }
  void SetDefault() { self.m_NewPlayer = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_NewPlayer; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<12>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_GameData"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADDC824C; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserSuccess::m_GameData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_GameData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserSuccess *>(obj); return &ptr->m_GameData; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data<12, Self> : public StormReflTypeInfo<GameServerAuthenticateUserSuccess>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_GameData; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_GameData; }
  void SetDefault() { self.m_GameData = StormReflTypeInfo<GameServerAuthenticateUserSuccess>::GetDefault().m_GameData; }
};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserFailure>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerAuthenticateUserFailure"; }
  static constexpr auto GetNameHash() { return 0x73B8692D; }
  static constexpr bool HasDefault() { return true; }
  static GameServerAuthenticateUserFailure & GetDefault() { static GameServerAuthenticateUserFailure def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUserFailure *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUserFailure *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerAuthenticateUserFailure *>(ptr);
    if(typeid(GameServerAuthenticateUserFailure).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerAuthenticateUserFailure *>(ptr);
    if(typeid(GameServerAuthenticateUserFailure).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerAuthenticateUserFailure>::field_data_static<0>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_ResponseId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC09E75BA; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerAuthenticateUserFailure::m_ResponseId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerAuthenticateUserFailure *>(obj); return &ptr->m_ResponseId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerAuthenticateUserFailure *>(obj); return &ptr->m_ResponseId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerAuthenticateUserFailure>::field_data<0, Self> : public StormReflTypeInfo<GameServerAuthenticateUserFailure>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_ResponseId; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_ResponseId; }
  void SetDefault() { self.m_ResponseId = StormReflTypeInfo<GameServerAuthenticateUserFailure>::GetDefault().m_ResponseId; }
};

template <>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerRequestTeamSwitch"; }
  static constexpr auto GetNameHash() { return 0x615963B7; }
  static constexpr bool HasDefault() { return true; }
  static GameServerRequestTeamSwitch & GetDefault() { static GameServerRequestTeamSwitch def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerRequestTeamSwitch *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRequestTeamSwitch *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerRequestTeamSwitch *>(ptr);
    if(typeid(GameServerRequestTeamSwitch).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRequestTeamSwitch *>(ptr);
    if(typeid(GameServerRequestTeamSwitch).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerRequestTeamSwitch::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRequestTeamSwitch *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRequestTeamSwitch *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data<0, Self> : public StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameServerRequestTeamSwitch>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerRequestTeamSwitch::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRequestTeamSwitch *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRequestTeamSwitch *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data<1, Self> : public StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerRequestTeamSwitch>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerRequestTeamSwitch::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRequestTeamSwitch *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRequestTeamSwitch *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data<2, Self> : public StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameServerRequestTeamSwitch>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Force"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1A5E1348; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerRequestTeamSwitch::m_Force; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRequestTeamSwitch *>(obj); return &ptr->m_Force; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRequestTeamSwitch *>(obj); return &ptr->m_Force; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data<3, Self> : public StormReflTypeInfo<GameServerRequestTeamSwitch>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Force; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Force; }
  void SetDefault() { self.m_Force = StormReflTypeInfo<GameServerRequestTeamSwitch>::GetDefault().m_Force; }
};

template <>
struct StormReflTypeInfo<GameServerRandomizeTeams>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerRandomizeTeams"; }
  static constexpr auto GetNameHash() { return 0x4C2DA421; }
  static constexpr bool HasDefault() { return true; }
  static GameServerRandomizeTeams & GetDefault() { static GameServerRandomizeTeams def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerRandomizeTeams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRandomizeTeams *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerRandomizeTeams *>(ptr);
    if(typeid(GameServerRandomizeTeams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRandomizeTeams *>(ptr);
    if(typeid(GameServerRandomizeTeams).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerRandomizeTeams>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerRandomizeTeams::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRandomizeTeams *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRandomizeTeams *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRandomizeTeams>::field_data<0, Self> : public StormReflTypeInfo<GameServerRandomizeTeams>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerRandomizeTeams>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerResetGame>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerResetGame"; }
  static constexpr auto GetNameHash() { return 0x4D870DEA; }
  static constexpr bool HasDefault() { return true; }
  static GameServerResetGame & GetDefault() { static GameServerResetGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerResetGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerResetGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerResetGame *>(ptr);
    if(typeid(GameServerResetGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerResetGame *>(ptr);
    if(typeid(GameServerResetGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerResetGame>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerResetGame::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerResetGame *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerResetGame *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerResetGame>::field_data<0, Self> : public StormReflTypeInfo<GameServerResetGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerResetGame>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerTeamSwitch>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerTeamSwitch"; }
  static constexpr auto GetNameHash() { return 0xEA071864; }
  static constexpr bool HasDefault() { return true; }
  static GameServerTeamSwitch & GetDefault() { static GameServerTeamSwitch def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerTeamSwitch *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerTeamSwitch *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerTeamSwitch *>(ptr);
    if(typeid(GameServerTeamSwitch).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerTeamSwitch *>(ptr);
    if(typeid(GameServerTeamSwitch).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerTeamSwitch::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerTeamSwitch *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerTeamSwitch *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data<0, Self> : public StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameServerTeamSwitch>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerTeamSwitch::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerTeamSwitch *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerTeamSwitch *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data<1, Self> : public StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerTeamSwitch>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerTeamSwitch::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerTeamSwitch *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerTeamSwitch *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerTeamSwitch>::field_data<2, Self> : public StormReflTypeInfo<GameServerTeamSwitch>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameServerTeamSwitch>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameServerForceUserDisconnect>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerForceUserDisconnect"; }
  static constexpr auto GetNameHash() { return 0xF18DF355; }
  static constexpr bool HasDefault() { return true; }
  static GameServerForceUserDisconnect & GetDefault() { static GameServerForceUserDisconnect def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerForceUserDisconnect *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerForceUserDisconnect *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerForceUserDisconnect *>(ptr);
    if(typeid(GameServerForceUserDisconnect).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerForceUserDisconnect *>(ptr);
    if(typeid(GameServerForceUserDisconnect).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerForceUserDisconnect>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerForceUserDisconnect::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerForceUserDisconnect *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerForceUserDisconnect *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerForceUserDisconnect>::field_data<0, Self> : public StormReflTypeInfo<GameServerForceUserDisconnect>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameServerForceUserDisconnect>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameServerForceUserDisconnect>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerForceUserDisconnect::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerForceUserDisconnect *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerForceUserDisconnect *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerForceUserDisconnect>::field_data<1, Self> : public StormReflTypeInfo<GameServerForceUserDisconnect>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerForceUserDisconnect>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerUserDisconnected>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerUserDisconnected"; }
  static constexpr auto GetNameHash() { return 0x0AFEBA3C; }
  static constexpr bool HasDefault() { return true; }
  static GameServerUserDisconnected & GetDefault() { static GameServerUserDisconnected def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerUserDisconnected *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerUserDisconnected *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerUserDisconnected *>(ptr);
    if(typeid(GameServerUserDisconnected).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerUserDisconnected *>(ptr);
    if(typeid(GameServerUserDisconnected).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerUserDisconnected>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerUserDisconnected::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerUserDisconnected *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerUserDisconnected *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerUserDisconnected>::field_data<0, Self> : public StormReflTypeInfo<GameServerUserDisconnected>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GameServerUserDisconnected>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GameServerUserDisconnected>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerUserDisconnected::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerUserDisconnected *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerUserDisconnected *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerUserDisconnected>::field_data<1, Self> : public StormReflTypeInfo<GameServerUserDisconnected>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerUserDisconnected>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerRelocate>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerRelocate"; }
  static constexpr auto GetNameHash() { return 0x4A56519E; }
  static constexpr bool HasDefault() { return true; }
  static GameServerRelocate & GetDefault() { static GameServerRelocate def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerRelocate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRelocate *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerRelocate *>(ptr);
    if(typeid(GameServerRelocate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerRelocate *>(ptr);
    if(typeid(GameServerRelocate).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerRelocate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_HostAddr"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBFF65732; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerRelocate::m_HostAddr; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRelocate *>(obj); return &ptr->m_HostAddr; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRelocate *>(obj); return &ptr->m_HostAddr; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRelocate>::field_data<0, Self> : public StormReflTypeInfo<GameServerRelocate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_HostAddr; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_HostAddr; }
  void SetDefault() { self.m_HostAddr = StormReflTypeInfo<GameServerRelocate>::GetDefault().m_HostAddr; }
};

template <>
struct StormReflTypeInfo<GameServerRelocate>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7D0CC8D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerRelocate::m_Port; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRelocate *>(obj); return &ptr->m_Port; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRelocate *>(obj); return &ptr->m_Port; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRelocate>::field_data<1, Self> : public StormReflTypeInfo<GameServerRelocate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Port; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Port; }
  void SetDefault() { self.m_Port = StormReflTypeInfo<GameServerRelocate>::GetDefault().m_Port; }
};

template <>
struct StormReflTypeInfo<GameServerRelocate>::field_data_static<2>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_RelocationKey"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x780D6A5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerRelocate::m_RelocationKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerRelocate *>(obj); return &ptr->m_RelocationKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerRelocate *>(obj); return &ptr->m_RelocationKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerRelocate>::field_data<2, Self> : public StormReflTypeInfo<GameServerRelocate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_RelocationKey; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_RelocationKey; }
  void SetDefault() { self.m_RelocationKey = StormReflTypeInfo<GameServerRelocate>::GetDefault().m_RelocationKey; }
};

template <>
struct StormReflTypeInfo<GameServerKillGame>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerKillGame"; }
  static constexpr auto GetNameHash() { return 0x1DF2FA4B; }
  static constexpr bool HasDefault() { return true; }
  static GameServerKillGame & GetDefault() { static GameServerKillGame def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerKillGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerKillGame *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerKillGame *>(ptr);
    if(typeid(GameServerKillGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerKillGame *>(ptr);
    if(typeid(GameServerKillGame).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerKillGame>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerKillGame::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerKillGame *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerKillGame *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerKillGame>::field_data<0, Self> : public StormReflTypeInfo<GameServerKillGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerKillGame>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerScore>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerScore"; }
  static constexpr auto GetNameHash() { return 0xA6339F72; }
  static constexpr bool HasDefault() { return true; }
  static GameServerScore & GetDefault() { static GameServerScore def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerScore *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerScore *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerScore *>(ptr);
    if(typeid(GameServerScore).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerScore *>(ptr);
    if(typeid(GameServerScore).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerScore>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerScore::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerScore *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerScore *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerScore>::field_data<0, Self> : public StormReflTypeInfo<GameServerScore>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerScore>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerScore>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Score"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBFAFA731; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerScore::m_Score; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerScore *>(obj); return &ptr->m_Score; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerScore *>(obj); return &ptr->m_Score; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerScore>::field_data<1, Self> : public StormReflTypeInfo<GameServerScore>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Score; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Score; }
  void SetDefault() { self.m_Score = StormReflTypeInfo<GameServerScore>::GetDefault().m_Score; }
};

template <>
struct StormReflTypeInfo<GameServerStats>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerStats"; }
  static constexpr auto GetNameHash() { return 0xC3EDCF89; }
  static constexpr bool HasDefault() { return true; }
  static GameServerStats & GetDefault() { static GameServerStats def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerStats *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerStats *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerStats *>(ptr);
    if(typeid(GameServerStats).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerStats *>(ptr);
    if(typeid(GameServerStats).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerStats>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_AccountId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBEFE92F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerStats::m_AccountId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerStats *>(obj); return &ptr->m_AccountId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerStats *>(obj); return &ptr->m_AccountId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerStats>::field_data<0, Self> : public StormReflTypeInfo<GameServerStats>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_AccountId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_AccountId; }
  void SetDefault() { self.m_AccountId = StormReflTypeInfo<GameServerStats>::GetDefault().m_AccountId; }
};

template <>
struct StormReflTypeInfo<GameServerStats>::field_data_static<1>
{
  using member_type = GameStatsData; // GameStatsData
  static constexpr auto GetName() { return "m_Stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA71F7CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerStats::m_Stats; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerStats *>(obj); return &ptr->m_Stats; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerStats *>(obj); return &ptr->m_Stats; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerStats>::field_data<1, Self> : public StormReflTypeInfo<GameServerStats>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameStatsData> & Get() { return self.m_Stats; }
  std::add_const_t<std::remove_reference_t<GameStatsData>> & Get() const { return self.m_Stats; }
  void SetDefault() { self.m_Stats = StormReflTypeInfo<GameServerStats>::GetDefault().m_Stats; }
};

template <>
struct StormReflTypeInfo<GameServerStats>::field_data_static<2>
{
  using member_type = GameInitSettings; // GameInitSettings
  static constexpr auto GetName() { return "m_Settings"; }
  static constexpr auto GetType() { return "GameInitSettings"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136974EB; }
  static constexpr unsigned GetTypeNameHash() { return 0xBAC6DD28; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerStats::m_Settings; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerStats *>(obj); return &ptr->m_Settings; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerStats *>(obj); return &ptr->m_Settings; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerStats>::field_data<2, Self> : public StormReflTypeInfo<GameServerStats>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInitSettings> & Get() { return self.m_Settings; }
  std::add_const_t<std::remove_reference_t<GameInitSettings>> & Get() const { return self.m_Settings; }
  void SetDefault() { self.m_Settings = StormReflTypeInfo<GameServerStats>::GetDefault().m_Settings; }
};

template <>
struct StormReflTypeInfo<GameServerChangeCreator>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerChangeCreator"; }
  static constexpr auto GetNameHash() { return 0x1D059208; }
  static constexpr bool HasDefault() { return true; }
  static GameServerChangeCreator & GetDefault() { static GameServerChangeCreator def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerChangeCreator *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerChangeCreator *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerChangeCreator *>(ptr);
    if(typeid(GameServerChangeCreator).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerChangeCreator *>(ptr);
    if(typeid(GameServerChangeCreator).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerChangeCreator>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerChangeCreator::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerChangeCreator *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerChangeCreator *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerChangeCreator>::field_data<0, Self> : public StormReflTypeInfo<GameServerChangeCreator>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerChangeCreator>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerChangeCreator>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Creator"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29F49FB6; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerChangeCreator::m_Creator; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerChangeCreator *>(obj); return &ptr->m_Creator; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerChangeCreator *>(obj); return &ptr->m_Creator; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerChangeCreator>::field_data<1, Self> : public StormReflTypeInfo<GameServerChangeCreator>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Creator; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Creator; }
  void SetDefault() { self.m_Creator = StormReflTypeInfo<GameServerChangeCreator>::GetDefault().m_Creator; }
};

template <>
struct StormReflTypeInfo<GameServerResultPlayer>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerResultPlayer"; }
  static constexpr auto GetNameHash() { return 0x87D68505; }
  static constexpr bool HasDefault() { return true; }
  static GameServerResultPlayer & GetDefault() { static GameServerResultPlayer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerResultPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerResultPlayer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerResultPlayer *>(ptr);
    if(typeid(GameServerResultPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerResultPlayer *>(ptr);
    if(typeid(GameServerResultPlayer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_AccountId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBEFE92F3; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerResultPlayer::m_AccountId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerResultPlayer *>(obj); return &ptr->m_AccountId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerResultPlayer *>(obj); return &ptr->m_AccountId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data<0, Self> : public StormReflTypeInfo<GameServerResultPlayer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_AccountId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_AccountId; }
  void SetDefault() { self.m_AccountId = StormReflTypeInfo<GameServerResultPlayer>::GetDefault().m_AccountId; }
};

template <>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Team"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFA7D3300; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerResultPlayer::m_Team; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerResultPlayer *>(obj); return &ptr->m_Team; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerResultPlayer *>(obj); return &ptr->m_Team; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data<1, Self> : public StormReflTypeInfo<GameServerResultPlayer>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Team; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Team; }
  void SetDefault() { self.m_Team = StormReflTypeInfo<GameServerResultPlayer>::GetDefault().m_Team; }
};

template <>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data_static<2>
{
  using member_type = GameStatsData; // GameStatsData
  static constexpr auto GetName() { return "m_Stats"; }
  static constexpr auto GetType() { return "GameStatsData"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDA71F7CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x9CB3161C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerResultPlayer::m_Stats; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerResultPlayer *>(obj); return &ptr->m_Stats; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerResultPlayer *>(obj); return &ptr->m_Stats; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerResultPlayer>::field_data<2, Self> : public StormReflTypeInfo<GameServerResultPlayer>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameStatsData> & Get() { return self.m_Stats; }
  std::add_const_t<std::remove_reference_t<GameStatsData>> & Get() const { return self.m_Stats; }
  void SetDefault() { self.m_Stats = StormReflTypeInfo<GameServerResultPlayer>::GetDefault().m_Stats; }
};

template <>
struct StormReflTypeInfo<GameServerGameResult>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerGameResult"; }
  static constexpr auto GetNameHash() { return 0x63B1A2A0; }
  static constexpr bool HasDefault() { return true; }
  static GameServerGameResult & GetDefault() { static GameServerGameResult def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerGameResult *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerGameResult *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerGameResult *>(ptr);
    if(typeid(GameServerGameResult).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerGameResult *>(ptr);
    if(typeid(GameServerGameResult).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerGameResult>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long
  static constexpr auto GetName() { return "m_GameId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA16AE06C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerGameResult::m_GameId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerGameResult *>(obj); return &ptr->m_GameId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerGameResult *>(obj); return &ptr->m_GameId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerGameResult>::field_data<0, Self> : public StormReflTypeInfo<GameServerGameResult>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_GameId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_GameId; }
  void SetDefault() { self.m_GameId = StormReflTypeInfo<GameServerGameResult>::GetDefault().m_GameId; }
};

template <>
struct StormReflTypeInfo<GameServerGameResult>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_GameCompleted"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x99FB229F; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerGameResult::m_GameCompleted; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerGameResult *>(obj); return &ptr->m_GameCompleted; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerGameResult *>(obj); return &ptr->m_GameCompleted; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerGameResult>::field_data<1, Self> : public StormReflTypeInfo<GameServerGameResult>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_GameCompleted; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_GameCompleted; }
  void SetDefault() { self.m_GameCompleted = StormReflTypeInfo<GameServerGameResult>::GetDefault().m_GameCompleted; }
};

template <>
struct StormReflTypeInfo<GameServerGameResult>::field_data_static<2>
{
  using member_type = std::vector<int>; // std::vector<int, std::allocator<int> >
  static constexpr auto GetName() { return "m_TeamScores"; }
  static constexpr auto GetType() { return "std::vector<int, std::allocator<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC77B7E79; }
  static constexpr unsigned GetTypeNameHash() { return 0x90559D98; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerGameResult::m_TeamScores; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerGameResult *>(obj); return &ptr->m_TeamScores; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerGameResult *>(obj); return &ptr->m_TeamScores; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerGameResult>::field_data<2, Self> : public StormReflTypeInfo<GameServerGameResult>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<int>> & Get() { return self.m_TeamScores; }
  std::add_const_t<std::remove_reference_t<std::vector<int>>> & Get() const { return self.m_TeamScores; }
  void SetDefault() { self.m_TeamScores = StormReflTypeInfo<GameServerGameResult>::GetDefault().m_TeamScores; }
};

template <>
struct StormReflTypeInfo<GameServerGameResult>::field_data_static<3>
{
  using member_type = std::vector<GameServerResultPlayer>; // std::vector<GameServerResultPlayer, std::allocator<GameServerResultPlayer> >
  static constexpr auto GetName() { return "m_ConnectedUsers"; }
  static constexpr auto GetType() { return "std::vector<GameServerResultPlayer, std::allocator<GameServerResultPlayer> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF28AC28C; }
  static constexpr unsigned GetTypeNameHash() { return 0x68E7D85C; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerGameResult::m_ConnectedUsers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerGameResult *>(obj); return &ptr->m_ConnectedUsers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerGameResult *>(obj); return &ptr->m_ConnectedUsers; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerGameResult>::field_data<3, Self> : public StormReflTypeInfo<GameServerGameResult>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GameServerResultPlayer>> & Get() { return self.m_ConnectedUsers; }
  std::add_const_t<std::remove_reference_t<std::vector<GameServerResultPlayer>>> & Get() const { return self.m_ConnectedUsers; }
  void SetDefault() { self.m_ConnectedUsers = StormReflTypeInfo<GameServerGameResult>::GetDefault().m_ConnectedUsers; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameServerMeta"; }
  static constexpr auto GetNameHash() { return 0x1961B3BC; }
  static constexpr bool HasDefault() { return true; }
  static GameServerMeta & GetDefault() { static GameServerMeta def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameServerMeta *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerMeta *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameServerMeta *>(ptr);
    if(typeid(GameServerMeta).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameServerMeta *>(ptr);
    if(typeid(GameServerMeta).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_LobbyServerIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC4B0ECD; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_LobbyServerIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_LobbyServerIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_LobbyServerIp; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<0, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_LobbyServerIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_LobbyServerIp; }
  void SetDefault() { self.m_LobbyServerIp = StormReflTypeInfo<GameServerMeta>::GetDefault().m_LobbyServerIp; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerKey"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10F8EFD5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_ServerKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_ServerKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_ServerKey; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<1, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerKey; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerKey; }
  void SetDefault() { self.m_ServerKey = StormReflTypeInfo<GameServerMeta>::GetDefault().m_ServerKey; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x070A2B55; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_ServerName; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_ServerName; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_ServerName; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<2, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerName; }
  void SetDefault() { self.m_ServerName = StormReflTypeInfo<GameServerMeta>::GetDefault().m_ServerName; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerZone"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF9C29554; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_ServerZone; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_ServerZone; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_ServerZone; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<3, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerZone; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerZone; }
  void SetDefault() { self.m_ServerZone = StormReflTypeInfo<GameServerMeta>::GetDefault().m_ServerZone; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ServerResourceId"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x484BB3D8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_ServerResourceId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_ServerResourceId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_ServerResourceId; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<4, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ServerResourceId; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ServerResourceId; }
  void SetDefault() { self.m_ServerResourceId = StormReflTypeInfo<GameServerMeta>::GetDefault().m_ServerResourceId; }
};

template <>
struct StormReflTypeInfo<GameServerMeta>::field_data_static<5>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ExternalIp"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x371391DE; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameServerMeta::m_ExternalIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameServerMeta *>(obj); return &ptr->m_ExternalIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameServerMeta *>(obj); return &ptr->m_ExternalIp; }
};

template <typename Self>
struct StormReflTypeInfo<GameServerMeta>::field_data<5, Self> : public StormReflTypeInfo<GameServerMeta>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ExternalIp; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ExternalIp; }
  void SetDefault() { self.m_ExternalIp = StormReflTypeInfo<GameServerMeta>::GetDefault().m_ExternalIp; }
};

namespace StormReflFileInfo
{
  struct GameServerMessages
  {
    static const int types_n = 24;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameServerMessages::type_info<0>
  {
    using type = ::GameServerMapData;
  };

  template <>
  struct GameServerMessages::type_info<1>
  {
    using type = ::GameServerIdentifyNew;
  };

  template <>
  struct GameServerMessages::type_info<2>
  {
    using type = ::GameServerIdentifyRelocate;
  };

  template <>
  struct GameServerMessages::type_info<3>
  {
    using type = ::GameServerRelocated;
  };

  template <>
  struct GameServerMessages::type_info<4>
  {
    using type = ::GameServerPing;
  };

  template <>
  struct GameServerMessages::type_info<5>
  {
    using type = ::GameServerAuthenticateRequest;
  };

  template <>
  struct GameServerMessages::type_info<6>
  {
    using type = ::GameServerAuthenticateResponse;
  };

  template <>
  struct GameServerMessages::type_info<7>
  {
    using type = ::GameServerAuthenticateUser;
  };

  template <>
  struct GameServerMessages::type_info<8>
  {
    using type = ::GameServerAuthenticateUserSuccess;
  };

  template <>
  struct GameServerMessages::type_info<9>
  {
    using type = ::GameServerAuthenticateUserFailure;
  };

  template <>
  struct GameServerMessages::type_info<10>
  {
    using type = ::GameServerRequestTeamSwitch;
  };

  template <>
  struct GameServerMessages::type_info<11>
  {
    using type = ::GameServerRandomizeTeams;
  };

  template <>
  struct GameServerMessages::type_info<12>
  {
    using type = ::GameServerResetGame;
  };

  template <>
  struct GameServerMessages::type_info<13>
  {
    using type = ::GameServerTeamSwitch;
  };

  template <>
  struct GameServerMessages::type_info<14>
  {
    using type = ::GameServerForceUserDisconnect;
  };

  template <>
  struct GameServerMessages::type_info<15>
  {
    using type = ::GameServerUserDisconnected;
  };

  template <>
  struct GameServerMessages::type_info<16>
  {
    using type = ::GameServerRelocate;
  };

  template <>
  struct GameServerMessages::type_info<17>
  {
    using type = ::GameServerKillGame;
  };

  template <>
  struct GameServerMessages::type_info<18>
  {
    using type = ::GameServerScore;
  };

  template <>
  struct GameServerMessages::type_info<19>
  {
    using type = ::GameServerStats;
  };

  template <>
  struct GameServerMessages::type_info<20>
  {
    using type = ::GameServerChangeCreator;
  };

  template <>
  struct GameServerMessages::type_info<21>
  {
    using type = ::GameServerResultPlayer;
  };

  template <>
  struct GameServerMessages::type_info<22>
  {
    using type = ::GameServerGameResult;
  };

  template <>
  struct GameServerMessages::type_info<23>
  {
    using type = ::GameServerMeta;
  };

}

