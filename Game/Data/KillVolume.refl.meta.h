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
  static KillVolume & GetDefault() { static KillVolume def; return def; }
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

