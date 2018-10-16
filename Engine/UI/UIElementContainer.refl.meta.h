#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "UIElementContainer.refl.h"
#include "Engine/UI/UICustomPropertyData.refl.meta.h"
#include "Runtime/UI/UIDef.refl.meta.h"


template <>
struct StormReflTypeInfo<UIElementContainerInitData>
{
  using MyBase = UIElementInitDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementContainerInitData"; }
  static constexpr auto GetNameHash() { return 0x86439F54; }
  static UIElementContainerInitData & GetDefault() { static UIElementContainerInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementContainerInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementContainerInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x17C45A05 == type_name_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementContainerInitData *>(ptr);
    if(typeid(UIElementContainerInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<UIElementInitDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementContainerInitData *>(ptr);
    if(typeid(UIElementContainerInitData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementInitDataBase).hash_code() == type_id_hash) return static_cast<const UIElementInitDataBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<UIElementContainerData>
{
  using MyBase = UIElementDataStartEnd;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "UIElementContainerData"; }
  static constexpr auto GetNameHash() { return 0x29015F17; }
  static UIElementContainerData & GetDefault() { static UIElementContainerData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<UIElementContainerData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x7B3842A1 == type_name_hash) return static_cast<UIElementDataStartEnd *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementContainerData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x7B3842A1 == type_name_hash) return static_cast<const UIElementDataStartEnd *>(c);
    if(0xC8F14E8A == type_name_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<UIElementContainerData *>(ptr);
    if(typeid(UIElementContainerData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataStartEnd).hash_code() == type_id_hash) return static_cast<UIElementDataStartEnd *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<UIElementDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const UIElementContainerData *>(ptr);
    if(typeid(UIElementContainerData).hash_code() == type_id_hash) return c;
    if(typeid(UIElementDataStartEnd).hash_code() == type_id_hash) return static_cast<const UIElementDataStartEnd *>(c);
    if(typeid(UIElementDataBase).hash_code() == type_id_hash) return static_cast<const UIElementDataBase *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct UIElementContainer
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct UIElementContainer::type_info<0>
  {
    using type = ::UIElementContainerInitData;
  };

  template <>
  struct UIElementContainer::type_info<1>
  {
    using type = ::UIElementContainerData;
  };

}

