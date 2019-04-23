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

namespace StormReflFileInfo
{
  struct GameData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameData::type_info<0>
  {
    using type = ::GameStatsData;
  };

}

