#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameLevelListAsset.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<GameLevelInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLevelInfo"; }
  static constexpr auto GetNameHash() { return 0xB1E21B10; }
  static GameLevelInfo & GetDefault() { static GameLevelInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLevelInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLevelInfo *>(ptr);
    if(typeid(GameLevelInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelInfo *>(ptr);
    if(typeid(GameLevelInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLevelInfo>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C91E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLevelInfo::m_Path; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelInfo *>(obj); return &ptr->m_Path; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelInfo *>(obj); return &ptr->m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelInfo>::field_data<0, Self> : public StormReflTypeInfo<GameLevelInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<GameLevelInfo>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<GameLevelInfo>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &GameLevelInfo::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelInfo *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelInfo *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelInfo>::field_data<1, Self> : public StormReflTypeInfo<GameLevelInfo>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<GameLevelInfo>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<GameLevelInfo>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Description"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x88BB47C2; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &GameLevelInfo::m_Description; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelInfo *>(obj); return &ptr->m_Description; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelInfo *>(obj); return &ptr->m_Description; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelInfo>::field_data<2, Self> : public StormReflTypeInfo<GameLevelInfo>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Description; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Description; }
  void SetDefault() { self.m_Description = StormReflTypeInfo<GameLevelInfo>::GetDefault().m_Description; }
};

template <>
struct StormReflTypeInfo<GameLevelInfo>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_MapImage"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3CDD28FB; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &GameLevelInfo::m_MapImage; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelInfo *>(obj); return &ptr->m_MapImage; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelInfo *>(obj); return &ptr->m_MapImage; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelInfo>::field_data<3, Self> : public StormReflTypeInfo<GameLevelInfo>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_MapImage; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_MapImage; }
  void SetDefault() { self.m_MapImage = StormReflTypeInfo<GameLevelInfo>::GetDefault().m_MapImage; }
};

template <>
struct StormReflTypeInfo<GameLevelInfo>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MaxPlayers"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D18B4FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &GameLevelInfo::m_MaxPlayers; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelInfo *>(obj); return &ptr->m_MaxPlayers; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelInfo *>(obj); return &ptr->m_MaxPlayers; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelInfo>::field_data<4, Self> : public StormReflTypeInfo<GameLevelInfo>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MaxPlayers; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MaxPlayers; }
  void SetDefault() { self.m_MaxPlayers = StormReflTypeInfo<GameLevelInfo>::GetDefault().m_MaxPlayers; }
};

template <>
struct StormReflTypeInfo<GameLevelListAsset>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameLevelListAsset"; }
  static constexpr auto GetNameHash() { return 0x6F8BA414; }
  static GameLevelListAsset & GetDefault() { static GameLevelListAsset def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<GameLevelListAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelListAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<GameLevelListAsset *>(ptr);
    if(typeid(GameLevelListAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const GameLevelListAsset *>(ptr);
    if(typeid(GameLevelListAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  using member_type = std::vector<GameLevelInfo>; // std::vector<GameLevelInfo, std::allocator<GameLevelInfo> >
  static constexpr auto GetName() { return "m_Levels"; }
  static constexpr auto GetType() { return "std::vector<GameLevelInfo, std::allocator<GameLevelInfo> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD21533D1; }
  static constexpr unsigned GetTypeNameHash() { return 0x25C8650B; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &GameLevelListAsset::m_Levels; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<GameLevelListAsset *>(obj); return &ptr->m_Levels; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const GameLevelListAsset *>(obj); return &ptr->m_Levels; }
};

template <typename Self>
struct StormReflTypeInfo<GameLevelListAsset>::field_data<0, Self> : public StormReflTypeInfo<GameLevelListAsset>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GameLevelInfo>> & Get() { return self.m_Levels; }
  std::add_const_t<std::remove_reference_t<std::vector<GameLevelInfo>>> & Get() const { return self.m_Levels; }
  void SetDefault() { self.m_Levels = StormReflTypeInfo<GameLevelListAsset>::GetDefault().m_Levels; }
};

namespace StormReflFileInfo
{
  struct GameLevelListAsset
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameLevelListAsset::type_info<0>
  {
    using type = ::GameLevelInfo;
  };

  template <>
  struct GameLevelListAsset::type_info<1>
  {
    using type = ::GameLevelListAsset;
  };

}

