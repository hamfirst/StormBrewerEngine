#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "LobbyLevelList.refl.h"


template <>
struct StormReflTypeInfo<LobbyMapProperties>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "LobbyMapProperties"; }
  static constexpr auto GetNameHash() { return 0xF8086B4F; }
  static constexpr bool HasDefault() { return true; }
  static LobbyMapProperties & GetDefault() { static LobbyMapProperties def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapProperties *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapProperties *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapProperties *>(ptr);
    if(typeid(LobbyMapProperties).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapProperties *>(ptr);
    if(typeid(LobbyMapProperties).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<LobbyMapProperties>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_PlayerCount"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5E784CAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &LobbyMapProperties::m_PlayerCount; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LobbyMapProperties *>(obj); return &ptr->m_PlayerCount; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LobbyMapProperties *>(obj); return &ptr->m_PlayerCount; }
};

template <typename Self>
struct StormReflTypeInfo<LobbyMapProperties>::field_data<0, Self> : public StormReflTypeInfo<LobbyMapProperties>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_PlayerCount; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_PlayerCount; }
  void SetDefault() { self.m_PlayerCount = StormReflTypeInfo<LobbyMapProperties>::GetDefault().m_PlayerCount; }
};

template <>
struct StormReflTypeInfo<LobbyMapProperties>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ScoreLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43D3DFC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &LobbyMapProperties::m_ScoreLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LobbyMapProperties *>(obj); return &ptr->m_ScoreLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LobbyMapProperties *>(obj); return &ptr->m_ScoreLimit; }
};

template <typename Self>
struct StormReflTypeInfo<LobbyMapProperties>::field_data<1, Self> : public StormReflTypeInfo<LobbyMapProperties>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ScoreLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ScoreLimit; }
  void SetDefault() { self.m_ScoreLimit = StormReflTypeInfo<LobbyMapProperties>::GetDefault().m_ScoreLimit; }
};

template <>
struct StormReflTypeInfo<LobbyMapProperties>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TimeLimit"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92EF9F49; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &LobbyMapProperties::m_TimeLimit; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LobbyMapProperties *>(obj); return &ptr->m_TimeLimit; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LobbyMapProperties *>(obj); return &ptr->m_TimeLimit; }
};

template <typename Self>
struct StormReflTypeInfo<LobbyMapProperties>::field_data<2, Self> : public StormReflTypeInfo<LobbyMapProperties>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TimeLimit; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TimeLimit; }
  void SetDefault() { self.m_TimeLimit = StormReflTypeInfo<LobbyMapProperties>::GetDefault().m_TimeLimit; }
};

template <>
struct StormReflTypeInfo<LobbyMapPropertiesContainer>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "LobbyMapPropertiesContainer"; }
  static constexpr auto GetNameHash() { return 0x03D7CB90; }
  static constexpr bool HasDefault() { return true; }
  static LobbyMapPropertiesContainer & GetDefault() { static LobbyMapPropertiesContainer def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapPropertiesContainer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapPropertiesContainer *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapPropertiesContainer *>(ptr);
    if(typeid(LobbyMapPropertiesContainer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapPropertiesContainer *>(ptr);
    if(typeid(LobbyMapPropertiesContainer).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<LobbyMapPropertiesContainer>::field_data_static<0>
{
  using member_type = LobbyMapProperties; // LobbyMapProperties
  static constexpr auto GetName() { return "m_MapProperties"; }
  static constexpr auto GetType() { return "LobbyMapProperties"; }
  static constexpr unsigned GetFieldNameHash() { return 0x841C9243; }
  static constexpr unsigned GetTypeNameHash() { return 0xF8086B4F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &LobbyMapPropertiesContainer::m_MapProperties; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LobbyMapPropertiesContainer *>(obj); return &ptr->m_MapProperties; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LobbyMapPropertiesContainer *>(obj); return &ptr->m_MapProperties; }
};

template <typename Self>
struct StormReflTypeInfo<LobbyMapPropertiesContainer>::field_data<0, Self> : public StormReflTypeInfo<LobbyMapPropertiesContainer>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, LobbyMapProperties> & Get() { return self.m_MapProperties; }
  std::add_const_t<std::remove_reference_t<LobbyMapProperties>> & Get() const { return self.m_MapProperties; }
  void SetDefault() { self.m_MapProperties = StormReflTypeInfo<LobbyMapPropertiesContainer>::GetDefault().m_MapProperties; }
};

template <>
struct StormReflTypeInfo<LobbyMapInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "LobbyMapInfo"; }
  static constexpr auto GetNameHash() { return 0xCC51C0C8; }
  static constexpr bool HasDefault() { return true; }
  static LobbyMapInfo & GetDefault() { static LobbyMapInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapInfo *>(ptr);
    if(typeid(LobbyMapInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapInfo *>(ptr);
    if(typeid(LobbyMapInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<LobbyMapInfo>::field_data_static<0>
{
  using member_type = LobbyMapPropertiesContainer; // LobbyMapPropertiesContainer
  static constexpr auto GetName() { return "m_PropertiesInfo"; }
  static constexpr auto GetType() { return "LobbyMapPropertiesContainer"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2CFDF744; }
  static constexpr unsigned GetTypeNameHash() { return 0x03D7CB90; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &LobbyMapInfo::m_PropertiesInfo; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<LobbyMapInfo *>(obj); return &ptr->m_PropertiesInfo; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const LobbyMapInfo *>(obj); return &ptr->m_PropertiesInfo; }
};

template <typename Self>
struct StormReflTypeInfo<LobbyMapInfo>::field_data<0, Self> : public StormReflTypeInfo<LobbyMapInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, LobbyMapPropertiesContainer> & Get() { return self.m_PropertiesInfo; }
  std::add_const_t<std::remove_reference_t<LobbyMapPropertiesContainer>> & Get() const { return self.m_PropertiesInfo; }
  void SetDefault() { self.m_PropertiesInfo = StormReflTypeInfo<LobbyMapInfo>::GetDefault().m_PropertiesInfo; }
};

template <>
struct StormReflTypeInfo<LobbyMapHeaderElem>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "LobbyMapHeaderElem"; }
  static constexpr auto GetNameHash() { return 0x36984F48; }
  static constexpr bool HasDefault() { return true; }
  static LobbyMapHeaderElem & GetDefault() { static LobbyMapHeaderElem def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapHeaderElem *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapHeaderElem *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<LobbyMapHeaderElem *>(ptr);
    if(typeid(LobbyMapHeaderElem).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const LobbyMapHeaderElem *>(ptr);
    if(typeid(LobbyMapHeaderElem).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct LobbyLevelList
  {
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct LobbyLevelList::type_info<0>
  {
    using type = ::LobbyMapProperties;
  };

  template <>
  struct LobbyLevelList::type_info<1>
  {
    using type = ::LobbyMapPropertiesContainer;
  };

  template <>
  struct LobbyLevelList::type_info<2>
  {
    using type = ::LobbyMapInfo;
  };

  template <>
  struct LobbyLevelList::type_info<3>
  {
    using type = ::LobbyMapHeaderElem;
  };

}

