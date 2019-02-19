#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameData.refl.h"


template <>
struct StormReflTypeInfo<GameInstanceData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameInstanceData"; }
  static constexpr auto GetNameHash() { return 0xC7A440E6; }
  static GameInstanceData & GetDefault() { static GameInstanceData def; return def; }
};

template <>
struct StormReflTypeInfo<GameInstanceData>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Name; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_Map; }
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
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_TimeLimit; }
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
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_ScoreLimit; }
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
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameInstanceData::m_PlayerLimit; }
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
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStatsData"; }
  static constexpr auto GetNameHash() { return 0x9CB3161C; }
  static GameStatsData & GetDefault() { static GameStatsData def; return def; }
};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesPlayed; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesWon; }
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
  static constexpr auto GetName() { return "m_TimePlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2E922E2F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_TimePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<6, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<6>
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
  static constexpr int fields_n = 10;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserXPGain"; }
  static constexpr auto GetNameHash() { return 0x1F48ADC4; }
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
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD94F0D7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWon; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<4, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWon; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWon; }
  void SetDefault() { self.m_GamesWon = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWon; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWonCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9C0C236E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWonCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<5, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWonCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWonCount; }
  void SetDefault() { self.m_GamesWonCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWonCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<6, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayed; }
  void SetDefault() { self.m_GamesPlayed = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayed; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<7>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayedCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2F30C6E6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayedCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<7, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayedCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayedCount; }
  void SetDefault() { self.m_GamesPlayedCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayedCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<8>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Gifted"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x62CE8E45; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Gifted; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<8, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Gifted; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Gifted; }
  void SetDefault() { self.m_Gifted = StormReflTypeInfo<UserXPGain>::GetDefault().m_Gifted; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<9>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_XP"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96E11FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<9, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<9>
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
  static UserRewards & GetDefault() { static UserRewards def; return def; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<0>
{
  using member_type = std::vector<std::pair<std::string, std::string> >; // std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >
  static constexpr auto GetName() { return "m_Icons"; }
  static constexpr auto GetType() { return "std::vector<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x875CC01E; }
  static constexpr unsigned GetTypeNameHash() { return 0xE3DEFE4C; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Icons; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Titles; }
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
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Celebrations; }
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
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_AutoJoins; }
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
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameData::type_info<0>
  {
    using type = ::GameInstanceData;
  };

  template <>
  struct GameData::type_info<1>
  {
    using type = ::GameStatsData;
  };

  template <>
  struct GameData::type_info<2>
  {
    using type = ::UserXPGain;
  };

  template <>
  struct GameData::type_info<3>
  {
    using type = ::UserRewards;
  };

}

