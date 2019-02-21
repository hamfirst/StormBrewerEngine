#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileMotionLinear.refl.h"
#include "Game/ServerObjects/Projectile/Motion/ProjectileMotionBase.refl.meta.h"


template <>
struct StormReflTypeInfo<ProjectileMotionLinearConfig>
{
  using MyBase = ProjectileMotionBaseConfig;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileMotionLinearConfig"; }
  static constexpr auto GetNameHash() { return 0xB3D23059; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileMotionLinearConfig & GetDefault() { static ProjectileMotionLinearConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionLinearConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xD15E6198 == type_name_hash) return static_cast<ProjectileMotionBaseConfig *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionLinearConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xD15E6198 == type_name_hash) return static_cast<const ProjectileMotionBaseConfig *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionLinearConfig *>(ptr);
    if(typeid(ProjectileMotionLinearConfig).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileMotionBaseConfig).hash_code() == type_id_hash) return static_cast<ProjectileMotionBaseConfig *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionLinearConfig *>(ptr);
    if(typeid(ProjectileMotionLinearConfig).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileMotionBaseConfig).hash_code() == type_id_hash) return static_cast<const ProjectileMotionBaseConfig *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileMotionLinearConfig>::field_data_static<0 + StormReflTypeInfo<ProjectileMotionBaseConfig>::fields_n>
{
  using member_type = RDeterministicFloat<GameNetVal>; // RDeterministicFloat<NetFixedPoint<long, 32, 16> >
  static constexpr auto GetName() { return "m_Speed"; }
  static constexpr auto GetType() { return "RDeterministicFloat<NetFixedPoint<long, 32, 16> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x82106E96; }
  static constexpr unsigned GetTypeNameHash() { return 0x9C9647A3; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ProjectileMotionBaseConfig>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileMotionLinearConfig::m_Speed; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileMotionLinearConfig *>(obj); return &ptr->m_Speed; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileMotionLinearConfig *>(obj); return &ptr->m_Speed; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileMotionLinearConfig>::field_data<0 + StormReflTypeInfo<ProjectileMotionBaseConfig>::fields_n, Self> : public StormReflTypeInfo<ProjectileMotionLinearConfig>::field_data_static<0 + StormReflTypeInfo<ProjectileMotionBaseConfig>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, RDeterministicFloat<GameNetVal>> & Get() { return self.m_Speed; }
  std::add_const_t<std::remove_reference_t<RDeterministicFloat<GameNetVal>>> & Get() const { return self.m_Speed; }
  void SetDefault() { self.m_Speed = StormReflTypeInfo<ProjectileMotionLinearConfig>::GetDefault().m_Speed; }
};

template <>
struct StormReflTypeInfo<ProjectileMotionLinear>
{
  using MyBase = ProjectileMotionBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileMotionLinear"; }
  static constexpr auto GetNameHash() { return 0xE04A82B8; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileMotionLinear & GetDefault() { static ProjectileMotionLinear def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionLinear *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA001F5DF == type_name_hash) return static_cast<ProjectileMotionBase *>(c);
    if(0x0F21A3D8 == type_name_hash) return static_cast<ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionLinear *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA001F5DF == type_name_hash) return static_cast<const ProjectileMotionBase *>(c);
    if(0x0F21A3D8 == type_name_hash) return static_cast<const ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionLinear *>(ptr);
    if(typeid(ProjectileMotionLinear).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileMotionBase).hash_code() == type_id_hash) return static_cast<ProjectileMotionBase *>(c);
    if(typeid(ServerObjectComponentBase<ProjectileMotionBaseConfig>).hash_code() == type_id_hash) return static_cast<ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionLinear *>(ptr);
    if(typeid(ProjectileMotionLinear).hash_code() == type_id_hash) return c;
    if(typeid(ProjectileMotionBase).hash_code() == type_id_hash) return static_cast<const ProjectileMotionBase *>(c);
    if(typeid(ServerObjectComponentBase<ProjectileMotionBaseConfig>).hash_code() == type_id_hash) return static_cast<const ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileMotionLinear>::field_data_static<0 + StormReflTypeInfo<ProjectileMotionBase>::fields_n>
{
  using member_type = GameNetVal; // NetFixedPoint<long, 32, 16>
  static constexpr auto GetName() { return "m_RangeRemaining"; }
  static constexpr auto GetType() { return "NetFixedPoint<long, 32, 16>"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51F0BDD2; }
  static constexpr unsigned GetTypeNameHash() { return 0x0D893FA0; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<ProjectileMotionBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &ProjectileMotionLinear::m_RangeRemaining; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<ProjectileMotionLinear *>(obj); return &ptr->m_RangeRemaining; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const ProjectileMotionLinear *>(obj); return &ptr->m_RangeRemaining; }
};

template <typename Self>
struct StormReflTypeInfo<ProjectileMotionLinear>::field_data<0 + StormReflTypeInfo<ProjectileMotionBase>::fields_n, Self> : public StormReflTypeInfo<ProjectileMotionLinear>::field_data_static<0 + StormReflTypeInfo<ProjectileMotionBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameNetVal> & Get() { return self.m_RangeRemaining; }
  std::add_const_t<std::remove_reference_t<GameNetVal>> & Get() const { return self.m_RangeRemaining; }
  void SetDefault() { self.m_RangeRemaining = StormReflTypeInfo<ProjectileMotionLinear>::GetDefault().m_RangeRemaining; }
};

namespace StormReflFileInfo
{
  struct ProjectileMotionLinear
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileMotionLinear::type_info<0>
  {
    using type = ::ProjectileMotionLinearConfig;
  };

  template <>
  struct ProjectileMotionLinear::type_info<1>
  {
    using type = ::ProjectileMotionLinear;
  };

}

