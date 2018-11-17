#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayAnimationComponent.refl.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"


template <>
struct StormReflEnumInfo<PlayAnimationComponentLoopMode>
{
  static constexpr int elems_n = 2;
  static constexpr auto GetName() { return "PlayAnimationComponentLoopMode"; }
  static constexpr auto GetNameHash() { return 0xC2AAC5B7; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<PlayAnimationComponentLoopMode>::elems<0>
{
  static constexpr auto GetName() { return "kPlayLooping"; }
  static constexpr auto GetNameHash() { return 0x0C8D8810; }
  static constexpr auto GetValue() { return PlayAnimationComponentLoopMode::kPlayLooping; }
};

template <>
struct StormReflEnumInfo<PlayAnimationComponentLoopMode>::elems<1>
{
  static constexpr auto GetName() { return "kPlayOnceAndDestroy"; }
  static constexpr auto GetNameHash() { return 0x8C33E396; }
  static constexpr auto GetValue() { return PlayAnimationComponentLoopMode::kPlayOnceAndDestroy; }
};

template <>
struct StormReflTypeInfo<PlayAnimationComponentInitData>
{
  using MyBase = ComponentInitData;
  static constexpr int fields_n = 2 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "PlayAnimationComponentInitData"; }
  static constexpr auto GetNameHash() { return 0x35DD3172; }
  static PlayAnimationComponentInitData & GetDefault() { static PlayAnimationComponentInitData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<PlayAnimationComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const PlayAnimationComponentInitData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x6DB2F865 == type_name_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<PlayAnimationComponentInitData *>(ptr);
    if(typeid(PlayAnimationComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<ComponentInitData *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const PlayAnimationComponentInitData *>(ptr);
    if(typeid(PlayAnimationComponentInitData).hash_code() == type_id_hash) return c;
    if(typeid(ComponentInitData).hash_code() == type_id_hash) return static_cast<const ComponentInitData *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<PlayAnimationComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Animation"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5172A5C7; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayAnimationComponentInitData::m_Animation; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayAnimationComponentInitData *>(obj); return &ptr->m_Animation; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayAnimationComponentInitData *>(obj); return &ptr->m_Animation; }
};

template <typename Self>
struct StormReflTypeInfo<PlayAnimationComponentInitData>::field_data<0 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<PlayAnimationComponentInitData>::field_data_static<0 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Animation; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Animation; }
  void SetDefault() { self.m_Animation = StormReflTypeInfo<PlayAnimationComponentInitData>::GetDefault().m_Animation; }
};

template <>
struct StormReflTypeInfo<PlayAnimationComponentInitData>::field_data_static<1 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  using member_type = REnum<PlayAnimationComponentLoopMode>; // REnum<PlayAnimationComponentLoopMode>
  static constexpr auto GetName() { return "m_LoopMode"; }
  static constexpr auto GetType() { return "REnum<PlayAnimationComponentLoopMode>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7F78E876; }
  static constexpr unsigned GetTypeNameHash() { return 0xC0607559; }
  static constexpr auto GetFieldIndex() { return 1 + StormReflTypeInfo<ComponentInitData>::fields_n; }
  static constexpr auto GetMemberPtr() { return &PlayAnimationComponentInitData::m_LoopMode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<PlayAnimationComponentInitData *>(obj); return &ptr->m_LoopMode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const PlayAnimationComponentInitData *>(obj); return &ptr->m_LoopMode; }
};

template <typename Self>
struct StormReflTypeInfo<PlayAnimationComponentInitData>::field_data<1 + StormReflTypeInfo<ComponentInitData>::fields_n, Self> : public StormReflTypeInfo<PlayAnimationComponentInitData>::field_data_static<1 + StormReflTypeInfo<ComponentInitData>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, REnum<PlayAnimationComponentLoopMode>> & Get() { return self.m_LoopMode; }
  std::add_const_t<std::remove_reference_t<REnum<PlayAnimationComponentLoopMode>>> & Get() const { return self.m_LoopMode; }
  void SetDefault() { self.m_LoopMode = StormReflTypeInfo<PlayAnimationComponentInitData>::GetDefault().m_LoopMode; }
};

namespace StormReflFileInfo
{
  struct PlayAnimationComponent
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayAnimationComponent::type_info<0>
  {
    using type = ::PlayAnimationComponentInitData;
  };

}

