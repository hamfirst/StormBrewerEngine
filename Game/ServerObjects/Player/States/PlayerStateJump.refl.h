
#pragma once

#include "ProjectSettings/ProjectPerspective.h"

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
#define PLAYER_ENABLE_JUMP
#endif

#ifdef PLAYER_ENABLE_JUMP

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

class PlayerStateJump : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateJump>
{
public:
  DECLARE_PLAYER_STATE;

  void AllowGraceJump();
  bool CanGraceJump() const;

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;

public:

  NetRangedNumber<int, 0, 5> m_JumpGraceFrames;
};

#endif