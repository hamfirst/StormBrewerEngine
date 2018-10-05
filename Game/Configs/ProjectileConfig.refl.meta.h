#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileConfig.refl.h"


template <>
struct StormReflTypeInfo<ProjectileConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ProjectileConfig"; }
  static constexpr auto GetNameHash() { return 0x2E56CBC8; }
  static ProjectileConfig & GetDefault() { static ProjectileConfig def; return def; }
};

template <>
struct StormReflTypeInfo<ProjectileConfig>::field_data_static<0>
{
  using member_type = RUInt; // RNumber<unsigned int>
  static constexpr auto GetName() { return "m_MaxDistance"; }
  static constexpr auto GetType() { return "RNumber<unsigned int>"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE000440A; }
  static constexpr unsigned GetTypeNameHash() { return 0x7B4FB98C; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &ProjectileConfig::m_MaxDistance; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileConfig>::field_data<0, Self> : public StormReflTypeInfo<ProjectileConfig>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RUInt> & Get() { return self.m_MaxDistance; }
  std::add_const_t<std::remove_reference_t<RUInt>> & Get() const { return self.m_MaxDistance; }
  void SetDefault() { self.m_MaxDistance = StormReflTypeInfo<ProjectileConfig>::GetDefault().m_MaxDistance; }
};

namespace StormReflFileInfo
{
  struct ProjectileConfig
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileConfig::type_info<0>
  {
    using type = ::ProjectileConfig;
  };

}

