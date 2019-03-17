#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameData.refl.h"


template <>
<<<<<<< HEAD
=======
struct StormReflTypeInfo<GamePlayerData>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GamePlayerData"; }
  static constexpr auto GetNameHash() { return 0x20881F93; }
  static constexpr bool HasDefault() { return true; }
  static GamePlayerData & GetDefault() { static GamePlayerData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GamePlayerData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GamePlayerData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GamePlayerData *>(ptr);
    if(typeid(GamePlayerData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GamePlayerData *>(ptr);
    if(typeid(GamePlayerData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_UserId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x29891A04; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_UserId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_UserId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_UserId; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<0, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_UserId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_UserId; }
  void SetDefault() { self.m_UserId = StormReflTypeInfo<GamePlayerData>::GetDefault().m_UserId; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_EndpointId"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC70D3D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_EndpointId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_EndpointId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_EndpointId; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<1, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_EndpointId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_EndpointId; }
  void SetDefault() { self.m_EndpointId = StormReflTypeInfo<GamePlayerData>::GetDefault().m_EndpointId; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<2, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GamePlayerData>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Admin"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x05389D16; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_Admin; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_Admin; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_Admin; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<3, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Admin; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Admin; }
  void SetDefault() { self.m_Admin = StormReflTypeInfo<GamePlayerData>::GetDefault().m_Admin; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Celebration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47D906C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_Celebration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_Celebration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_Celebration; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<4, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Celebration; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Celebration; }
  void SetDefault() { self.m_Celebration = StormReflTypeInfo<GamePlayerData>::GetDefault().m_Celebration; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<5>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_NewPlayer"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x313BF109; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_NewPlayer; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_NewPlayer; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_NewPlayer; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<5, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_NewPlayer; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_NewPlayer; }
  void SetDefault() { self.m_NewPlayer = StormReflTypeInfo<GamePlayerData>::GetDefault().m_NewPlayer; }
};

template <>
struct StormReflTypeInfo<GamePlayerData>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Squad"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x42E66F87; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GamePlayerData::m_Squad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GamePlayerData *>(obj); return &ptr->m_Squad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GamePlayerData *>(obj); return &ptr->m_Squad; }
};

template <typename Self>
struct StormReflTypeInfo<GamePlayerData>::field_data<6, Self> : public StormReflTypeInfo<GamePlayerData>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Squad; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Squad; }
  void SetDefault() { self.m_Squad = StormReflTypeInfo<GamePlayerData>::GetDefault().m_Squad; }
};

template <>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
struct StormReflTypeInfo<GameInstanceData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInstanceData"; }
  static constexpr auto GetNameHash() { return 0xC7A440E6; }
<<<<<<< HEAD
  static GameInstanceData & GetDefault() { static GameInstanceData def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static GameInstanceData & GetDefault() { static GameInstanceData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameInstanceData *>(ptr);
    if(typeid(GameInstanceData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameInstanceData *>(ptr);
    if(typeid(GameInstanceData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Name; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_Name; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<0, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Map"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x604F6E5C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Map; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Map; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_Map; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_Map; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<1, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Map; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Map; }
  void SetDefault() { self.m_Map = StormReflTypeInfo<GameInstanceData>::GetDefault().m_Map; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TimeLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92EF9F49; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_TimeLimit; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_TimeLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_TimeLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_TimeLimit; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<2, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TimeLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TimeLimit; }
  void SetDefault() { self.m_TimeLimit = StormReflTypeInfo<GameInstanceData>::GetDefault().m_TimeLimit; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ScoreLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43D3DFC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_ScoreLimit; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_ScoreLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_ScoreLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_ScoreLimit; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<3, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ScoreLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ScoreLimit; }
  void SetDefault() { self.m_ScoreLimit = StormReflTypeInfo<GameInstanceData>::GetDefault().m_ScoreLimit; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PlayerLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA437E0A8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_PlayerLimit; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_PlayerLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameInstanceData *>(obj); return &ptr->m_PlayerLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameInstanceData *>(obj); return &ptr->m_PlayerLimit; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameInstanceData>::field_data<4, Self> : public StormReflTypeInfo<GameInstanceData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PlayerLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PlayerLimit; }
  void SetDefault() { self.m_PlayerLimit = StormReflTypeInfo<GameInstanceData>::GetDefault().m_PlayerLimit; }
};

template <>
struct StormReflTypeInfo<GameStatsData>
{
  using MyBase = void;
<<<<<<< HEAD
  static constexpr int fields_n = 7;
=======
  static constexpr int fields_n = 3;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStatsData"; }
  static constexpr auto GetNameHash() { return 0x9CB3161C; }
<<<<<<< HEAD
  static GameStatsData & GetDefault() { static GameStatsData def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static GameStatsData & GetDefault() { static GameStatsData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameStatsData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameStatsData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameStatsData *>(ptr);
    if(typeid(GameStatsData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameStatsData *>(ptr);
    if(typeid(GameStatsData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesPlayed; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesPlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_GamesPlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_GamesPlayed; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<0, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayed; }
  void SetDefault() { self.m_GamesPlayed = StormReflTypeInfo<GameStatsData>::GetDefault().m_GamesPlayed; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD94F0D7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesWon; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesWon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_GamesWon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_GamesWon; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<1, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWon; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWon; }
  void SetDefault() { self.m_GamesWon = StormReflTypeInfo<GameStatsData>::GetDefault().m_GamesWon; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<2>
{
  using member_type = int; // int
<<<<<<< HEAD
  static constexpr auto GetName() { return "m_UBGoals"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x34993876; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_UBGoals; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<2, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_UBGoals; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_UBGoals; }
  void SetDefault() { self.m_UBGoals = StormReflTypeInfo<GameStatsData>::GetDefault().m_UBGoals; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_UBAssists"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA8DB1FF6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_UBAssists; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<3, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_UBAssists; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_UBAssists; }
  void SetDefault() { self.m_UBAssists = StormReflTypeInfo<GameStatsData>::GetDefault().m_UBAssists; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DBGoals"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF530AF0C; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_DBGoals; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<4, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DBGoals; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DBGoals; }
  void SetDefault() { self.m_DBGoals = StormReflTypeInfo<GameStatsData>::GetDefault().m_DBGoals; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DBAssists"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x136049C4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_DBAssists; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<5, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DBAssists; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DBAssists; }
  void SetDefault() { self.m_DBAssists = StormReflTypeInfo<GameStatsData>::GetDefault().m_DBAssists; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<6>
{
  using member_type = int; // int
=======
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  static constexpr auto GetName() { return "m_TimePlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2E922E2F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_TimePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<6, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<6>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_TimePlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_TimePlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_TimePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<2, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<2>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TimePlayed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TimePlayed; }
  void SetDefault() { self.m_TimePlayed = StormReflTypeInfo<GameStatsData>::GetDefault().m_TimePlayed; }
};

template <>
struct StormReflTypeInfo<UserXPGain>
{
  using MyBase = void;
<<<<<<< HEAD
  static constexpr int fields_n = 10;
=======
  static constexpr int fields_n = 6;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserXPGain"; }
  static constexpr auto GetNameHash() { return 0x1F48ADC4; }
<<<<<<< HEAD
  static UserXPGain & GetDefault() { static UserXPGain def; return def; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Goals"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4A128E4F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Goals; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<0, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Goals; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Goals; }
  void SetDefault() { self.m_Goals = StormReflTypeInfo<UserXPGain>::GetDefault().m_Goals; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GoalsCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8609B567; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GoalsCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<1, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GoalsCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GoalsCount; }
  void SetDefault() { self.m_GoalsCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GoalsCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Assists"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x845DFA7E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Assists; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<2, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Assists; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Assists; }
  void SetDefault() { self.m_Assists = StormReflTypeInfo<UserXPGain>::GetDefault().m_Assists; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_AssistsCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0AA23A7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_AssistsCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<3, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_AssistsCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_AssistsCount; }
  void SetDefault() { self.m_AssistsCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_AssistsCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<4>
=======
  static constexpr bool HasDefault() { return true; }
  static UserXPGain & GetDefault() { static UserXPGain def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserXPGain *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserXPGain *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserXPGain *>(ptr);
    if(typeid(UserXPGain).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserXPGain *>(ptr);
    if(typeid(UserXPGain).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD94F0D7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWon; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<4, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<4>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesWon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesWon; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<0, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<0>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWon; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWon; }
  void SetDefault() { self.m_GamesWon = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWon; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserXPGain>::field_data_static<5>
=======
struct StormReflTypeInfo<UserXPGain>::field_data_static<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWonCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9C0C236E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWonCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<5, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<5>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWonCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesWonCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesWonCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<1, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<1>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWonCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWonCount; }
  void SetDefault() { self.m_GamesWonCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWonCount; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserXPGain>::field_data_static<6>
=======
struct StormReflTypeInfo<UserXPGain>::field_data_static<2>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<6, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<6>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesPlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesPlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<2, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<2>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayed; }
  void SetDefault() { self.m_GamesPlayed = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayed; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserXPGain>::field_data_static<7>
=======
struct StormReflTypeInfo<UserXPGain>::field_data_static<3>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayedCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2F30C6E6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayedCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<7, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<7>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayedCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesPlayedCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesPlayedCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<3, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<3>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayedCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayedCount; }
  void SetDefault() { self.m_GamesPlayedCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayedCount; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserXPGain>::field_data_static<8>
=======
struct StormReflTypeInfo<UserXPGain>::field_data_static<4>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Gifted"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x62CE8E45; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Gifted; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<8, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<8>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Gifted; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_Gifted; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_Gifted; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<4, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<4>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Gifted; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Gifted; }
  void SetDefault() { self.m_Gifted = StormReflTypeInfo<UserXPGain>::GetDefault().m_Gifted; }
};

template <>
<<<<<<< HEAD
struct StormReflTypeInfo<UserXPGain>::field_data_static<9>
=======
struct StormReflTypeInfo<UserXPGain>::field_data_static<5>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_XP"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96E11FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<9, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<9>
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_XP; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_XP; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<5, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<5>
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_XP; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_XP; }
  void SetDefault() { self.m_XP = StormReflTypeInfo<UserXPGain>::GetDefault().m_XP; }
};

template <>
struct StormReflTypeInfo<UserRewards>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserRewards"; }
  static constexpr auto GetNameHash() { return 0x3C6254C2; }
<<<<<<< HEAD
  static UserRewards & GetDefault() { static UserRewards def; return def; }
=======
  static constexpr bool HasDefault() { return true; }
  static UserRewards & GetDefault() { static UserRewards def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UserRewards *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UserRewards *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UserRewards *>(ptr);
    if(typeid(UserRewards).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UserRewards *>(ptr);
    if(typeid(UserRewards).hash_code() == type_id_hash) return c;
    return nullptr;
  }

>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<0>
{
  using member_type = std::vector<std::pair<std::string, std::string> >; // std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >
  static constexpr auto GetName() { return "m_Icons"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x875CC01E; }
  static constexpr unsigned GetTypeNameHash() { return 0xE3DEFE4C; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Icons; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Icons; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Icons; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Icons; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<0, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<std::string, std::string> >> & Get() { return self.m_Icons; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<std::string, std::string> >>> & Get() const { return self.m_Icons; }
  void SetDefault() { self.m_Icons = StormReflTypeInfo<UserRewards>::GetDefault().m_Icons; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<1>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_Titles"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8C7A166B; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Titles; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Titles; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Titles; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Titles; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<1, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_Titles; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_Titles; }
  void SetDefault() { self.m_Titles = StormReflTypeInfo<UserRewards>::GetDefault().m_Titles; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<2>
{
  using member_type = std::vector<std::pair<std::string, int> >; // std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int>, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int> > >
  static constexpr auto GetName() { return "m_Celebrations"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int>, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, int> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6E23B591; }
  static constexpr unsigned GetTypeNameHash() { return 0xC0C7027A; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Celebrations; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Celebrations; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Celebrations; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Celebrations; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<2, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<std::string, int> >> & Get() { return self.m_Celebrations; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<std::string, int> >>> & Get() const { return self.m_Celebrations; }
  void SetDefault() { self.m_Celebrations = StormReflTypeInfo<UserRewards>::GetDefault().m_Celebrations; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<3>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_AutoJoins"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x707647AC; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
<<<<<<< HEAD
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_AutoJoins; }
=======
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_AutoJoins; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_AutoJoins; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_AutoJoins; }
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<3, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_AutoJoins; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_AutoJoins; }
  void SetDefault() { self.m_AutoJoins = StormReflTypeInfo<UserRewards>::GetDefault().m_AutoJoins; }
};

namespace StormReflFileInfo
{
  struct GameData
  {
<<<<<<< HEAD
    static const int types_n = 4;
=======
    static const int types_n = 5;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameData::type_info<0>
  {
<<<<<<< HEAD
    using type = ::GameInstanceData;
=======
    using type = ::GamePlayerData;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  };

  template <>
  struct GameData::type_info<1>
  {
<<<<<<< HEAD
    using type = ::GameStatsData;
=======
    using type = ::GameInstanceData;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  };

  template <>
  struct GameData::type_info<2>
  {
<<<<<<< HEAD
    using type = ::UserXPGain;
=======
    using type = ::GameStatsData;
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
  };

  template <>
  struct GameData::type_info<3>
  {
<<<<<<< HEAD
=======
    using type = ::UserXPGain;
  };

  template <>
  struct GameData::type_info<4>
  {
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
    using type = ::UserRewards;
  };

}

