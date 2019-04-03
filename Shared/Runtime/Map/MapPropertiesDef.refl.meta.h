#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapPropertiesDef.refl.h"


template <>
struct StormReflTypeInfo<MapPropertiesDef>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapPropertiesDef"; }
  static constexpr auto GetNameHash() { return 0x02766CB4; }
  static constexpr bool HasDefault() { return true; }
  static MapPropertiesDef & GetDefault() { static MapPropertiesDef def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapPropertiesDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapPropertiesDef *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapPropertiesDef *>(ptr);
    if(typeid(MapPropertiesDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapPropertiesDef *>(ptr);
    if(typeid(MapPropertiesDef).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapPropertiesDef>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PlayerCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E784CAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapPropertiesDef::m_PlayerCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<MapPropertiesDef *>(obj); return &ptr->m_PlayerCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const MapPropertiesDef *>(obj); return &ptr->m_PlayerCount; }
};

template <typename Self>
struct StormReflTypeInfo<MapPropertiesDef>::field_data<0, Self> : public StormReflTypeInfo<MapPropertiesDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PlayerCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PlayerCount; }
  void SetDefault() { self.m_PlayerCount = StormReflTypeInfo<MapPropertiesDef>::GetDefault().m_PlayerCount; }
};

template <>
struct StormReflTypeInfo<MapPropertiesDef>::field_data_static<1>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_ScoreLimit"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43D3DFC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapPropertiesDef::m_ScoreLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<MapPropertiesDef *>(obj); return &ptr->m_ScoreLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const MapPropertiesDef *>(obj); return &ptr->m_ScoreLimit; }
};

template <typename Self>
struct StormReflTypeInfo<MapPropertiesDef>::field_data<1, Self> : public StormReflTypeInfo<MapPropertiesDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_ScoreLimit; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_ScoreLimit; }
  void SetDefault() { self.m_ScoreLimit = StormReflTypeInfo<MapPropertiesDef>::GetDefault().m_ScoreLimit; }
};

template <>
struct StormReflTypeInfo<MapPropertiesDef>::field_data_static<2>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_TimeLimit"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92EF9F49; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &MapPropertiesDef::m_TimeLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<MapPropertiesDef *>(obj); return &ptr->m_TimeLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const MapPropertiesDef *>(obj); return &ptr->m_TimeLimit; }
};

template <typename Self>
struct StormReflTypeInfo<MapPropertiesDef>::field_data<2, Self> : public StormReflTypeInfo<MapPropertiesDef>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_TimeLimit; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_TimeLimit; }
  void SetDefault() { self.m_TimeLimit = StormReflTypeInfo<MapPropertiesDef>::GetDefault().m_TimeLimit; }
};

namespace StormReflFileInfo
{
  struct MapPropertiesDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapPropertiesDef::type_info<0>
  {
    using type = ::MapPropertiesDef;
  };

}

