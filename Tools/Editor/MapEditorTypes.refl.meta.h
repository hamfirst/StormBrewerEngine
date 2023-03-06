#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "MapEditorTypes.refl.h"
#include "Runtime/Anchor/AnchorDef.refl.meta.h"


template <>
struct StormReflTypeInfo<MapEditorAnchorInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "MapEditorAnchorInitData"; }
  static constexpr auto GetNameHash() { return 0x9DED0DA2; }
  static constexpr bool HasDefault() { return true; }
  static MapEditorAnchorInitData & GetDefault() { static MapEditorAnchorInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<MapEditorAnchorInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const MapEditorAnchorInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<MapEditorAnchorInitData *>(ptr);
    if(typeid(MapEditorAnchorInitData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const MapEditorAnchorInitData *>(ptr);
    if(typeid(MapEditorAnchorInitData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<MapEditorAnchorInitData>::field_data_static<0>
{
  using member_type = RPolymorphic<AnchorDataBase>; // RPolymorphicBase<AnchorDataBase, TypeDatabase<AnchorDataBase>, TypeDatabaseTypeInfo<AnchorDataBase> >
  static constexpr auto GetName() { return "m_InitData"; }
  static constexpr auto GetType() { return "RPolymorphicBase<AnchorDataBase, TypeDatabase<AnchorDataBase>, TypeDatabaseTypeInfo<AnchorDataBase> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x880F1CB3; }
  static constexpr unsigned GetTypeNameHash() { return 0x0A61DC07; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &MapEditorAnchorInitData::m_InitData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<MapEditorAnchorInitData *>(obj); return &ptr->m_InitData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const MapEditorAnchorInitData *>(obj); return &ptr->m_InitData; }
};

template <typename Self>
struct StormReflTypeInfo<MapEditorAnchorInitData>::field_data<0, Self> : public StormReflTypeInfo<MapEditorAnchorInitData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RPolymorphic<AnchorDataBase>> & Get() { return self.m_InitData; }
  std::add_const_t<std::remove_reference_t<RPolymorphic<AnchorDataBase>>> & Get() const { return self.m_InitData; }
  void SetDefault() { self.m_InitData = StormReflTypeInfo<MapEditorAnchorInitData>::GetDefault().m_InitData; }
};

template <>
struct StormReflTypeInfo<MapEditorAnchorInitData>::field_data_static<1>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Sprite"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7822D856; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &MapEditorAnchorInitData::m_Sprite; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<MapEditorAnchorInitData *>(obj); return &ptr->m_Sprite; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const MapEditorAnchorInitData *>(obj); return &ptr->m_Sprite; }
};

template <typename Self>
struct StormReflTypeInfo<MapEditorAnchorInitData>::field_data<1, Self> : public StormReflTypeInfo<MapEditorAnchorInitData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Sprite; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Sprite; }
  void SetDefault() { self.m_Sprite = StormReflTypeInfo<MapEditorAnchorInitData>::GetDefault().m_Sprite; }
};

template <>
struct StormReflTypeInfo<MapEditorAnchorInitData>::annotations<1>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<MapEditorAnchorInitData>::annotations<1>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: sprite"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x1563DF3B; }
};

namespace StormReflFileInfo
{
  struct MapEditorTypes
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct MapEditorTypes::type_info<0>
  {
    using type = ::MapEditorAnchorInitData;
  };

}

