#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "AttachVfxComponent.refl.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>
{
  using MyBase = ComponentInitData;
  static constexpr int fields_n = 4 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "AttachVfxComponentInitData"; }
  static constexpr auto GetNameHash() { return 0x96E294A9; }
  static AttachVfxComponentInitData & GetDefault() { static AttachVfxComponentInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<AttachVfxComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const AttachVfxComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<AttachVfxComponentInitData *>(ptr);
    if(typeid(AttachVfxComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const AttachVfxComponentInitData *>(ptr);
    if(typeid(AttachVfxComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_VfxFile"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9DC04EC1; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &AttachVfxComponentInitData::m_VfxFile; }
};

template <typename Self>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data<0 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_VfxFile; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_VfxFile; }
  void SetDefault() { self.m_VfxFile = StormReflTypeInfo<AttachVfxComponentInitData>::GetDefault().m_VfxFile; }
};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::annotations<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::annotations<0 + StormReflTypeInfo<ComponentInitData>::fields_n>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: vfx"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x645DC1BC; }
};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<1 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RBool; // RBool
  static constexpr auto GetName() { return "m_SpawnFinalParticle"; }
  static constexpr auto GetType() { return "RBool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x38489A40; }
  static constexpr unsigned GetTypeNameHash() { return 0x50062D06; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &AttachVfxComponentInitData::m_SpawnFinalParticle; }
};

template <typename Self>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data<1 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<1 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RBool> & Get() { return self.m_SpawnFinalParticle; }
  std::add_const_t<std::remove_reference_t<RBool>> & Get() const { return self.m_SpawnFinalParticle; }
  void SetDefault() { self.m_SpawnFinalParticle = StormReflTypeInfo<AttachVfxComponentInitData>::GetDefault().m_SpawnFinalParticle; }
};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<2 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_AttachAnchor"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA2E31E28; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 2 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &AttachVfxComponentInitData::m_AttachAnchor; }
};

template <typename Self>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data<2 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<2 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_AttachAnchor; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_AttachAnchor; }
  void SetDefault() { self.m_AttachAnchor = StormReflTypeInfo<AttachVfxComponentInitData>::GetDefault().m_AttachAnchor; }
};

template <>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<3 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_LayerOffset"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAABA9AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 3 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &AttachVfxComponentInitData::m_LayerOffset; }
};

template <typename Self>
struct StormReflTypeInfo<AttachVfxComponentInitData>::field_data<3 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<AttachVfxComponentInitData>::field_data_static<3 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_LayerOffset; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_LayerOffset; }
  void SetDefault() { self.m_LayerOffset = StormReflTypeInfo<AttachVfxComponentInitData>::GetDefault().m_LayerOffset; }
};

namespace StormReflFileInfo
{
  struct AttachVfxComponent
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct AttachVfxComponent::type_info<0>
  {
    using type = ::AttachVfxComponentInitData;
  };

}

