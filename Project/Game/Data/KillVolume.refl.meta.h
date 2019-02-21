#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "KillVolume.refl.h"
#include "Runtime/Volume/VolumeDef.refl.meta.h"


template <>
struct StormReflTypeInfo<KillVolume>
{
  using MyBase = VolumeDataBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "KillVolume"; }
  static constexpr auto GetNameHash() { return 0xB1B659F0; }
  static constexpr bool HasDefault() { return true; }
  static KillVolume & GetDefault() { static KillVolume def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<KillVolume *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x420476BB == type_name_hash) return static_cast<VolumeDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const KillVolume *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x420476BB == type_name_hash) return static_cast<const VolumeDataBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<KillVolume *>(ptr);
    if(typeid(KillVolume).hash_code() == type_id_hash) return c;
    if(typeid(VolumeDataBase).hash_code() == type_id_hash) return static_cast<VolumeDataBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const KillVolume *>(ptr);
    if(typeid(KillVolume).hash_code() == type_id_hash) return c;
    if(typeid(VolumeDataBase).hash_code() == type_id_hash) return static_cast<const VolumeDataBase *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct KillVolume
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct KillVolume::type_info<0>
  {
    using type = ::KillVolume;
  };

}

