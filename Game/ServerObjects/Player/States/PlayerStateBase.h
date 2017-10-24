#pragma once

#include "Game/GameCommon.h"
#include "Game/GameServerTypes.h"
#include "Game/GameLogicContainer.h"

#include "StormRefl/StormReflMetaInfoBase.h"

class PlayerServerObject;

class PlayerStateBase
{
public:
  virtual void Update(PlayerServerObject & player, GameLogicContainer & game_container) {};
};

template <>
struct StormReflTypeInfo<PlayerStateBase>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "PlayerStateBase"; }
  static constexpr auto GetNameHash() { return 0x6F8BA414; }
};
