#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GamePlayListAsset.refl.h"
#include "Game/GameNetworkData.refl.meta.h"


template <>
struct StormReflTypeInfo<PlaylistAssetElement>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistAssetElement"; }
  static constexpr auto GetNameHash() { return 0xE65EB019; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistAssetElement & GetDefault() { static PlaylistAssetElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistAssetElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistAssetElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistAssetElement *>(ptr);
    if(typeid(PlaylistAssetElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistAssetElement *>(ptr);
    if(typeid(PlaylistAssetElement).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x60BEEB19; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistAssetElement::m_Name; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAssetElement *>(obj); return &ptr->m_Name; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAssetElement *>(obj); return &ptr->m_Name; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data<0, Self> : public StormReflTypeInfo<PlaylistAssetElement>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Name; }
  void SetDefault() { self.m_Name = StormReflTypeInfo<PlaylistAssetElement>::GetDefault().m_Name; }
};

template <>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data_static<1>
{
  using member_type = std::vector<GameInitSettings>; // std::vector<GameInitSettings, std::allocator<GameInitSettings> >
  static constexpr auto GetName() { return "m_GameModes"; }
  static constexpr auto GetType() { return "std::vector<GameInitSettings, std::allocator<GameInitSettings> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF14C6D04; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7D24044; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &PlaylistAssetElement::m_GameModes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAssetElement *>(obj); return &ptr->m_GameModes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAssetElement *>(obj); return &ptr->m_GameModes; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data<1, Self> : public StormReflTypeInfo<PlaylistAssetElement>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<GameInitSettings>> & Get() { return self.m_GameModes; }
  std::add_const_t<std::remove_reference_t<std::vector<GameInitSettings>>> & Get() const { return self.m_GameModes; }
  void SetDefault() { self.m_GameModes = StormReflTypeInfo<PlaylistAssetElement>::GetDefault().m_GameModes; }
};

template <>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data_static<2>
{
  using member_type = int [2]; // int [2]
  static constexpr auto GetName() { return "m_TeamSizes"; }
  static constexpr auto GetType() { return "int [2]"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27BB0D16; }
  static constexpr unsigned GetTypeNameHash() { return 0x859FE93A; }
  static constexpr bool HasDefault() { return false; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &PlaylistAssetElement::m_TeamSizes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAssetElement *>(obj); return &ptr->m_TeamSizes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAssetElement *>(obj); return &ptr->m_TeamSizes; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data<2, Self> : public StormReflTypeInfo<PlaylistAssetElement>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int [2]> & Get() { return self.m_TeamSizes; }
  std::add_const_t<std::remove_reference_t<int [2]>> & Get() const { return self.m_TeamSizes; }
};

template <>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_AllowParties"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCA485774; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &PlaylistAssetElement::m_AllowParties; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAssetElement *>(obj); return &ptr->m_AllowParties; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAssetElement *>(obj); return &ptr->m_AllowParties; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data<3, Self> : public StormReflTypeInfo<PlaylistAssetElement>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_AllowParties; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_AllowParties; }
  void SetDefault() { self.m_AllowParties = StormReflTypeInfo<PlaylistAssetElement>::GetDefault().m_AllowParties; }
};

template <>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TotalGameSize"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC97E526; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &PlaylistAssetElement::m_TotalGameSize; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAssetElement *>(obj); return &ptr->m_TotalGameSize; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAssetElement *>(obj); return &ptr->m_TotalGameSize; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAssetElement>::field_data<4, Self> : public StormReflTypeInfo<PlaylistAssetElement>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TotalGameSize; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TotalGameSize; }
  void SetDefault() { self.m_TotalGameSize = StormReflTypeInfo<PlaylistAssetElement>::GetDefault().m_TotalGameSize; }
};

template <>
struct StormReflTypeInfo<PlaylistAsset>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlaylistAsset"; }
  static constexpr auto GetNameHash() { return 0x8D2C79D4; }
  static constexpr bool HasDefault() { return true; }
  static PlaylistAsset & GetDefault() { static PlaylistAsset def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlaylistAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistAsset *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlaylistAsset *>(ptr);
    if(typeid(PlaylistAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlaylistAsset *>(ptr);
    if(typeid(PlaylistAsset).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlaylistAsset>::field_data_static<0>
{
  using member_type = std::vector<PlaylistAssetElement>; // std::vector<PlaylistAssetElement, std::allocator<PlaylistAssetElement> >
  static constexpr auto GetName() { return "m_Elements"; }
  static constexpr auto GetType() { return "std::vector<PlaylistAssetElement, std::allocator<PlaylistAssetElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB266D373; }
  static constexpr unsigned GetTypeNameHash() { return 0xF74E38C6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &PlaylistAsset::m_Elements; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlaylistAsset *>(obj); return &ptr->m_Elements; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlaylistAsset *>(obj); return &ptr->m_Elements; }
};

template <typename Self>
struct StormReflTypeInfo<PlaylistAsset>::field_data<0, Self> : public StormReflTypeInfo<PlaylistAsset>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<PlaylistAssetElement>> & Get() { return self.m_Elements; }
  std::add_const_t<std::remove_reference_t<std::vector<PlaylistAssetElement>>> & Get() const { return self.m_Elements; }
  void SetDefault() { self.m_Elements = StormReflTypeInfo<PlaylistAsset>::GetDefault().m_Elements; }
};

namespace StormReflFileInfo
{
  struct GamePlayListAsset
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GamePlayListAsset::type_info<0>
  {
    using type = ::PlaylistAssetElement;
  };

  template <>
  struct GamePlayListAsset::type_info<1>
  {
    using type = ::PlaylistAsset;
  };

}

