#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "GameConfig.refl.h"


template <>
struct StormReflTypeInfo<GameConfig>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "GameConfig"; }
  static constexpr auto GetNameHash() { return 0x2470BC89; }
  static GameConfig & GetDefault() { static GameConfig def; return def; }
};

namespace StormReflFileInfo
{
  struct GameConfig
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct GameConfig::type_info<0>
  {
    using type = ::GameConfig;
  };

}

