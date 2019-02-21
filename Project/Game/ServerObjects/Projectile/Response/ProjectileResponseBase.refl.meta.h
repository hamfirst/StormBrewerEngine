#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "ProjectileResponseBase.refl.h"


template <>
struct StormReflTypeInfo<ProjectileResponseBaseConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ProjectileResponseBaseConfig"; }
  static constexpr auto GetNameHash() { return 0x6E067AD3; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileResponseBaseConfig & GetDefault() { static ProjectileResponseBaseConfig def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseBaseConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseBaseConfig *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseBaseConfig *>(ptr);
    if(typeid(ProjectileResponseBaseConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseBaseConfig *>(ptr);
    if(typeid(ProjectileResponseBaseConfig).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<ProjectileResponseBase>
{
  using MyBase = ServerObjectComponentBase<ProjectileResponseBaseConfig>;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "ProjectileResponseBase"; }
  static constexpr auto GetNameHash() { return 0xB8C052D5; }
  static constexpr bool HasDefault() { return true; }
  static ProjectileResponseBase & GetDefault() { static ProjectileResponseBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0F21A3D8 == type_name_hash) return static_cast<ServerObjectComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0F21A3D8 == type_name_hash) return static_cast<const ServerObjectComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ProjectileResponseBase *>(ptr);
    if(typeid(ProjectileResponseBase).hash_code() == type_id_hash) return c;
    if(typeid(ServerObjectComponentBase<ProjectileResponseBaseConfig>).hash_code() == type_id_hash) return static_cast<ServerObjectComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ProjectileResponseBase *>(ptr);
    if(typeid(ProjectileResponseBase).hash_code() == type_id_hash) return c;
    if(typeid(ServerObjectComponentBase<ProjectileResponseBaseConfig>).hash_code() == type_id_hash) return static_cast<const ServerObjectComponentBase<ProjectileResponseBaseConfig> *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct ProjectileResponseBase
  {
    static const int types_n = 2;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct ProjectileResponseBase::type_info<0>
  {
    using type = ::ProjectileResponseBaseConfig;
  };

  template <>
  struct ProjectileResponseBase::type_info<1>
  {
    using type = ::ProjectileResponseBase;
  };

}

