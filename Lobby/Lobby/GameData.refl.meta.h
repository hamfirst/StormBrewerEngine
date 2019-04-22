#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameData.refl.h"


template <>
struct StormReflTypeInfo<GameStatsData>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameStatsData"; }
  static constexpr auto GetNameHash() { return 0x9CB3161C; }
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

};

template <>
struct StormReflTypeInfo<GameStatsData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesPlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_GamesPlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_GamesPlayed; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_GamesWon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_GamesWon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_GamesWon; }
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
  static constexpr auto GetName() { return "m_TimePlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2E922E2F; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameStatsData::m_TimePlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameStatsData *>(obj); return &ptr->m_TimePlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameStatsData *>(obj); return &ptr->m_TimePlayed; }
};

template <typename Self>
struct StormReflTypeInfo<GameStatsData>::field_data<2, Self> : public StormReflTypeInfo<GameStatsData>::field_data_static<2>
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
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserXPGain"; }
  static constexpr auto GetNameHash() { return 0x1F48ADC4; }
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
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWon"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD94F0D7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWon; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesWon; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesWon; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<0, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWon; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWon; }
  void SetDefault() { self.m_GamesWon = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWon; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesWonCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9C0C236E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesWonCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesWonCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesWonCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<1, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesWonCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesWonCount; }
  void SetDefault() { self.m_GamesWonCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesWonCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayed"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFB1633C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesPlayed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesPlayed; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<2, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayed; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayed; }
  void SetDefault() { self.m_GamesPlayed = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayed; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_GamesPlayedCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2F30C6E6; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_GamesPlayedCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_GamesPlayedCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_GamesPlayedCount; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<3, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_GamesPlayedCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_GamesPlayedCount; }
  void SetDefault() { self.m_GamesPlayedCount = StormReflTypeInfo<UserXPGain>::GetDefault().m_GamesPlayedCount; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Gifted"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x62CE8E45; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_Gifted; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_Gifted; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_Gifted; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<4, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Gifted; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Gifted; }
  void SetDefault() { self.m_Gifted = StormReflTypeInfo<UserXPGain>::GetDefault().m_Gifted; }
};

template <>
struct StormReflTypeInfo<UserXPGain>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_XP"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x96E11FE7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &UserXPGain::m_XP; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserXPGain *>(obj); return &ptr->m_XP; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserXPGain *>(obj); return &ptr->m_XP; }
};

template <typename Self>
struct StormReflTypeInfo<UserXPGain>::field_data<5, Self> : public StormReflTypeInfo<UserXPGain>::field_data_static<5>
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
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "UserRewards"; }
  static constexpr auto GetNameHash() { return 0x3C6254C2; }
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

};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<0>
{
  using member_type = std::vector<int>; // std::vector<int, std::allocator<int> >
  static constexpr auto GetName() { return "m_Icons"; }
  static constexpr auto GetType() { return "std::vector<int, std::allocator<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x875CC01E; }
  static constexpr unsigned GetTypeNameHash() { return 0x90559D98; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Icons; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Icons; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Icons; }
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<0, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<int>> & Get() { return self.m_Icons; }
  std::add_const_t<std::remove_reference_t<std::vector<int>>> & Get() const { return self.m_Icons; }
  void SetDefault() { self.m_Icons = StormReflTypeInfo<UserRewards>::GetDefault().m_Icons; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<1>
{
  using member_type = std::vector<int>; // std::vector<int, std::allocator<int> >
  static constexpr auto GetName() { return "m_Titles"; }
  static constexpr auto GetType() { return "std::vector<int, std::allocator<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8C7A166B; }
  static constexpr unsigned GetTypeNameHash() { return 0x90559D98; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Titles; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Titles; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Titles; }
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<1, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<int>> & Get() { return self.m_Titles; }
  std::add_const_t<std::remove_reference_t<std::vector<int>>> & Get() const { return self.m_Titles; }
  void SetDefault() { self.m_Titles = StormReflTypeInfo<UserRewards>::GetDefault().m_Titles; }
};

template <>
struct StormReflTypeInfo<UserRewards>::field_data_static<2>
{
  using member_type = std::vector<int>; // std::vector<int, std::allocator<int> >
  static constexpr auto GetName() { return "m_Celebrations"; }
  static constexpr auto GetType() { return "std::vector<int, std::allocator<int> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6E23B591; }
  static constexpr unsigned GetTypeNameHash() { return 0x90559D98; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &UserRewards::m_Celebrations; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UserRewards *>(obj); return &ptr->m_Celebrations; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UserRewards *>(obj); return &ptr->m_Celebrations; }
};

template <typename Self>
struct StormReflTypeInfo<UserRewards>::field_data<2, Self> : public StormReflTypeInfo<UserRewards>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<int>> & Get() { return self.m_Celebrations; }
  std::add_const_t<std::remove_reference_t<std::vector<int>>> & Get() const { return self.m_Celebrations; }
  void SetDefault() { self.m_Celebrations = StormReflTypeInfo<UserRewards>::GetDefault().m_Celebrations; }
};

namespace StormReflFileInfo
{
  struct GameData
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameData::type_info<0>
  {
    using type = ::GameStatsData;
  };

  template <>
  struct GameData::type_info<1>
  {
    using type = ::UserXPGain;
  };

  template <>
  struct GameData::type_info<2>
  {
    using type = ::UserRewards;
  };

}

