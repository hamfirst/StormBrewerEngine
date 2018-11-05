#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementFullTexture.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementFullTextureInitData"; }
  static constexpr auto GetNameHash() { return 0x79CAB921; }
  static UIElementFullTextureInitData & GetDefault() { static UIElementFullTextureInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementFullTextureInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementFullTextureInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementFullTextureInitData *>(ptr);
    if(typeid(UIElementFullTextureInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementFullTextureInitData *>(ptr);
    if(typeid(UIElementFullTextureInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_TextureFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x300D4BA3; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureInitData::m_TextureFile; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIElementFullTextureInitData *>(obj); return &ptr->m_TextureFile; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIElementFullTextureInitData *>(obj); return &ptr->m_TextureFile; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureInitData>::field_data<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n, Self> : public StormReflTypeInfo<UIElementFullTextureInitData>::field_data_static<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_TextureFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_TextureFile; }
  void SetDefault() { self.m_TextureFile = StormReflTypeInfo<UIElementFullTextureInitData>::GetDefault().m_TextureFile; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<UIElementFullTextureInitData>::annotations<0 + StormReflTypeInfo<UIElementInitDataBase>::fields_n>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: image"; }
  static constexpr uint32_t GetAnnotationHash() { return 0xD4E8122A; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>
{
  using MyBase = UIElementDataFrameCenter;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementFullTextureData"; }
  static constexpr auto GetNameHash() { return 0x1DC7E1C5; }
  static UIElementFullTextureData & GetDefault() { static UIElementFullTextureData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementFullTextureData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementFullTextureData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x4076AA02 == type_name_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementFullTextureData *>(ptr);
    if(typeid(UIElementFullTextureData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementFullTextureData *>(ptr);
    if(typeid(UIElementFullTextureData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataFrameCenter).hash_code() == type_id_hash) return static_cast<const UIElementDataFrameCenter *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleX"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x10B4609F; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ScaleX; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIElementFullTextureData *>(obj); return &ptr->m_ScaleX; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIElementFullTextureData *>(obj); return &ptr->m_ScaleX; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<0 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleX; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleX; }
  void SetDefault() { self.m_ScaleX = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ScaleX; }
};

template <>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_ScaleY"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x67B35009; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n; }
  static constexpr auto GetMemberPtr() { return &UIElementFullTextureData::m_ScaleY; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<UIElementFullTextureData *>(obj); return &ptr->m_ScaleY; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const UIElementFullTextureData *>(obj); return &ptr->m_ScaleY; }
};

template <typename Self>
struct StormReflTypeInfo<UIElementFullTextureData>::field_data<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n, Self> : public StormReflTypeInfo<UIElementFullTextureData>::field_data_static<1 + StormReflTypeInfo<UIElementDataFrameCenter>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_ScaleY; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_ScaleY; }
  void SetDefault() { self.m_ScaleY = StormReflTypeInfo<UIElementFullTextureData>::GetDefault().m_ScaleY; }
};

namespace StormReflFileInfo
{
  struct UIElementFullTexture
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementFullTexture::type_info<0>
  {
    using type = ::UIElementFullTextureInitData;
  };

  template <>
  struct UIElementFullTexture::type_info<1>
  {
    using type = ::UIElementFullTextureData;
  };

}

