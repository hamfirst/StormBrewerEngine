#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileMotionBase.refl.h"


template <>
struct StormReflTypeInfo<ProjectileMotionBaseConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ProjectileMotionBaseConfig"; }
  static constexpr auto GetNameHash() { return 0xD15E6198; }
  static ProjectileMotionBaseConfig & GetDefault() { static ProjectileMotionBaseConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionBaseConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionBaseConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionBaseConfig *>(ptr);
    if(typeid(ProjectileMotionBaseConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionBaseConfig *>(ptr);
    if(typeid(ProjectileMotionBaseConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileMotionBase>
{
  using MyBase = ServerObjectComponentBase<ProjectileMotionBaseConfig>;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileMotionBase"; }
  static constexpr auto GetNameHash() { return 0xA001F5DF; }
  static ProjectileMotionBase & GetDefault() { static ProjectileMotionBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0F21A3D8 == type_name_hash) return static_cast<ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0F21A3D8 == type_name_hash) return static_cast<const ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileMotionBase *>(ptr);
    if(typeid(ProjectileMotionBase).hash_code() == type_id_hash) return c;
    if(typeid(ServerObjectComponentBase<ProjectileMotionBaseConfig>).hash_code() == type_id_hash) return static_cast<ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileMotionBase *>(ptr);
    if(typeid(ProjectileMotionBase).hash_code() == type_id_hash) return c;
    if(typeid(ServerObjectComponentBase<ProjectileMotionBaseConfig>).hash_code() == type_id_hash) return static_cast<const ServerObjectComponentBase<ProjectileMotionBaseConfig> *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct ProjectileMotionBase
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileMotionBase::type_info<0>
  {
    using type = ::ProjectileMotionBaseConfig;
  };

  template <>
  struct ProjectileMotionBase::type_info<1>
  {
    using type = ::ProjectileMotionBase;
  };

}

