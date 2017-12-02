#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayerStateBase.refl.h"


template <>
struct StormReflTypeInfo<PlayerStateBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerStateBase"; }
  static constexpr auto GetNameHash() { return 0x887CB291; }
  static PlayerStateBase & GetDefault() { static PlayerStateBase def; return def; }
};

namespace StormReflFileInfo
{
  struct PlayerStateBase
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayerStateBase::type_info<0>
  {
    using type = ::PlayerStateBase;
  };

}

