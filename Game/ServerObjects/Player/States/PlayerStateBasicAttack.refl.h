
#pragma once

#include "StormNet/NetReflectionStruct.h"
#include "StormNet/NetReflectionTypeDatabase.h"

#include "Game/ServerObjects/Player/States/PlayerStateBase.refl.h"

#include "Game/GameplayEvents/DamageType.refl.h"

struct PlayerStateBasicAttackSettings
{
  NET_REFL;

  bool m_ApplyMovement = false;
  bool m_RetainMovement = false;

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
  bool m_ApplyGravity = false;
  bool m_InterruptIfNoGround = false;
#endif

};

struct PlayerStateBasicAttackDamageSettings
{
  NET_REFL;

  NetRangedNumber<int, 1, 64> m_DamageAmount;
  NetEnum<DamageType> m_DamageType;
};

struct DealDamageAnimationEvent;

class PlayerStateBasicAttack : public PlayerStateBase, public PlayerStateEventHandler<PlayerStateBasicAttack>
{
public:
  DECLARE_PLAYER_STATE;
  
  void Setup(PlayerServerObject & player, uint32_t animation_hash, const PlayerStateBasicAttackSettings & settings = {},
    const Optional<PlayerStateBasicAttackDamageSettings> & damage_settings = {}, bool inherit_movement = false);

  virtual void Move(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Transition(PlayerServerObject & player, GameLogicContainer & game_container) override;
  virtual void Animate(PlayerServerObject & player, GameLogicContainer & game_container) override;

  virtual void PostUpdate(PlayerServerObject & player, GameLogicContainer & game_container) override;

  bool STORM_REFL_FUNC HandleDealDamageEvent(const DealDamageAnimationEvent & ev, const EventMetaData & meta);

public:

  uint32_t m_AnimationHash;
  PlayerStateBasicAttackSettings m_Settings;
  NetOptional<PlayerStateBasicAttackDamageSettings> m_DamageSettings;

private:
  GameNetVec2 m_AnimationVelocity;
};
