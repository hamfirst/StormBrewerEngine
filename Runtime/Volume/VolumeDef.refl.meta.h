#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "VolumeDef.refl.h"


template <>
struct StormReflTypeInfo<VolumeDataBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "VolumeDataBase"; }
  static constexpr auto GetNameHash() { return 0x420476BB; }
  static VolumeDataBase & GetDefault() { static VolumeDataBase def; return def; }
};

namespace StormReflFileInfo
{
  struct VolumeDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct VolumeDef::type_info<0>
  {
    using type = ::VolumeDataBase;
  };

}

