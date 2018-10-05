#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "EntityDef.refl.h"
#include "Runtime/Component/ComponentInitData.refl.meta.h"


template <>
struct StormReflTypeInfo<EntityDef>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "EntityDef"; }
  static constexpr auto GetNameHash() { return 0x511C9D4F; }
  static EntityDef & GetDefault() { static EntityDef def; return def; }
};

template <>
struct StormReflTypeInfo<EntityDef>::field_data_static<0>
{
  using member_type = RString; // RString
  static constexpr auto GetName() { return "m_Sprite"; }
  static constexpr auto GetType() { return "RString"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7822D856; }
  static constexpr unsigned GetTypeNameHash() { return 0x01F631DC; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &EntityDef::m_Sprite; }
};

template <typename Self>
struct StormReflTypeInfo<EntityDef>::field_data<0, Self> : public StormReflTypeInfo<EntityDef>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RString> & Get() { return self.m_Sprite; }
  std::add_const_t<std::remove_reference_t<RString>> & Get() const { return self.m_Sprite; }
  void SetDefault() { self.m_Sprite = StormReflTypeInfo<EntityDef>::GetDefault().m_Sprite; }
};

template <>
struct StormReflTypeInfo<EntityDef>::annotations<0>
{
  static constexpr int annotations_n = 1;
  template <int A> struct annoation { };
};

template <>
struct StormReflTypeInfo<EntityDef>::annotations<0>::annoation<0>
{
  static constexpr const char * GetAnnotation() { return "file: sprite"; }
  static constexpr uint32_t GetAnnotationHash() { return 0x1563DF3B; }
};

template <>
struct StormReflTypeInfo<EntityDef>::field_data_static<1>
{
  using member_type = RMergeList<RPolymorphic<ComponentInitData> >; // RMergeList<RPolymorphicBase<ComponentInitData, TypeDatabase<ComponentInitData, void>, TypeDatabaseTypeInfo<ComponentInitData, void>, false> >
  static constexpr auto GetName() { return "m_Components"; }
  static constexpr auto GetType() { return "RMergeList<RPolymorphicBase<ComponentInitData, TypeDatabase<ComponentInitData, void>, TypeDatabaseTypeInfo<ComponentInitData, void>, false> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x64F11C30; }
  static constexpr unsigned GetTypeNameHash() { return 0x2CECCE09; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &EntityDef::m_Components; }
};

template <typename Self>
struct StormReflTypeInfo<EntityDef>::field_data<1, Self> : public StormReflTypeInfo<EntityDef>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RMergeList<RPolymorphic<ComponentInitData> >> & Get() { return self.m_Components; }
  std::add_const_t<std::remove_reference_t<RMergeList<RPolymorphic<ComponentInitData> >>> & Get() const { return self.m_Components; }
  void SetDefault() { self.m_Components = StormReflTypeInfo<EntityDef>::GetDefault().m_Components; }
};

namespace StormReflFileInfo
{
  struct EntityDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct EntityDef::type_info<0>
  {
    using type = ::EntityDef;
  };

}

