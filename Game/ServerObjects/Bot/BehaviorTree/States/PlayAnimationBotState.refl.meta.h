#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "PlayAnimationBotState.refl.h"
#include "Game/GameFullState.refl.meta.h"
#include "Game/ServerObjects/Bot/BotServerObject.refl.meta.h"


template <>
struct StormReflTypeInfo<PlayAnimationBotState>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayAnimationBotState"; }
  static constexpr auto GetNameHash() { return 0x0A06114B; }
};

namespace StormReflFileInfo
{
  struct PlayAnimationBotState
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct PlayAnimationBotState::type_info<0>
  {
    using type = ::PlayAnimationBotState;
  };

}

