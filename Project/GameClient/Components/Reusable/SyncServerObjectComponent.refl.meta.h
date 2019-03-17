#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SyncServerObjectComponent.refl.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<SyncServerObjectComponentInitData>
{
  using MyBase = ComponentInitData;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "SyncServerObjectComponentInitData"; }
  static constexpr auto GetNameHash() { return 0xFBE918AF; }
  static constexpr bool HasDefault() { return true; }
  static SyncServerObjectComponentInitData & GetDefault() { static SyncServerObjectComponentInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<SyncServerObjectComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const SyncServerObjectComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<SyncServerObjectComponentInitData *>(ptr);
    if(typeid(SyncServerObjectComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const SyncServerObjectComponentInitData *>(ptr);
    if(typeid(SyncServerObjectComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<SyncServerObjectComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SyncSprite"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD4010554; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &SyncServerObjectComponentInitData::m_SyncSprite; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<SyncServerObjectComponentInitData *>(obj); return &ptr->m_SyncSprite; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const SyncServerObjectComponentInitData *>(obj); return &ptr->m_SyncSprite; }
};

template <typename Self>
struct StormReflTypeInfo<SyncServerObjectComponentInitData>::field_data<0 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<SyncServerObjectComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SyncSprite; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SyncSprite; }
  void SetDefault() { self.m_SyncSprite = StormReflTypeInfo<SyncServerObjectComponentInitData>::GetDefault().m_SyncSprite; }
};

namespace StormReflFileInfo
{
  struct SyncServerObjectComponent
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SyncServerObjectComponent::type_info<0>
  {
    using type = ::SyncServerObjectComponentInitData;
  };

}

