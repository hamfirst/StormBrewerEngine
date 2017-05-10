#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ComponentInitData.refl.h"


template <>
struct StormReflTypeInfo<ComponentInitData>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ComponentInitData"; }
  static constexpr auto GetNameHash() { return 0x6DB2F865; }
  static ComponentInitData & GetDefault() { static ComponentInitData def; return def; }
};

template <>
struct StormReflTypeInfo<ComponentInitData>::field_data_static<0>
{
  using member_type = RInt; // RNumber<int>
  static constexpr auto GetName() { return "m_Test"; }
  static constexpr auto GetType() { return "RNumber<int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6E2EB13; }
  static constexpr unsigned GetTypeNameHash() { return 0x75C9DA09; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ComponentInitData::m_Test; }
};

template <typename Self>
struct StormReflTypeInfo<ComponentInitData>::field_data<0, Self> : public StormReflTypeInfo<ComponentInitData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RInt> & Get() { return self.m_Test; }
  std::add_const_t<std::remove_reference_t<RInt>> & Get() const { return self.m_Test; }
  void SetDefault() { self.m_Test = StormReflTypeInfo<ComponentInitData>::GetDefault().m_Test; }
};

namespace StormReflFileInfo
{
  struct ComponentInitData
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ComponentInitData::type_info<0>
  {
    using type = ::ComponentInitData;
  };

}

