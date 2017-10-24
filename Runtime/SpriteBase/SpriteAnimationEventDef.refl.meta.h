#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "SpriteAnimationEventDef.refl.h"


template <>
struct StormReflTypeInfo<SpriteAnimationEventBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "SpriteAnimationEventBase"; }
  static constexpr auto GetNameHash() { return 0xDBC3BCBA; }
  static SpriteAnimationEventBase & GetDefault() { static SpriteAnimationEventBase def; return def; }
};

namespace StormReflFileInfo
{
  struct SpriteAnimationEventDef
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct SpriteAnimationEventDef::type_info<0>
  {
    using type = ::SpriteAnimationEventBase;
  };

}

