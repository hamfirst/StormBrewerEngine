
#include "Game/GameCommon.h"

#include "GameShared/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Game/ServerObjects/Player/States/PlayerStateBasicAttack.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateBasicAttack.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"

#include "StormNet/NetReflectionTypeDatabase.h"

NET_REGISTER_TYPE(PlayerStateBasicAttack, PlayerStateBase);

void PlayerStateBasicAttack::Setup(PlayerServerObject & player, uint32_t animation_hash, const PlayerStateBasicAttackSettings & settings,
  const Optional<PlayerStateBasicAttackDamageSettings> & damage_settings, bool inherit_movement)
{
  m_AnimationHash = animation_hash;
  m_Settings = settings;

  player.m_AnimIndex = player.GetSprite()->GetAnimationIndex(m_AnimationHash);
  player.m_AnimFrame = 0;
  player.m_AnimDelay = 0;

  if (damage_settings)
  {
    m_DamageSettings = damage_settings.Value();
  }

  m_AnimationVelocity.SetZero();

  if (inherit_movement == false)
  {
    player.m_Velocity.x = 0;
    player.m_Velocity.y = 0;
  }
}

void PlayerStateBasicAttack::Move(PlayerServerObject & player, GameLogicContainer & game_container)
{
  player.m_Velocity.x = 0;

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
  if (m_Settings.m_ApplyGravity)
  {
    player.m_Velocity.y -= player.GetConfig()->m_Gravity;
  }
#endif

  auto sprite = player.GetSprite();

  m_AnimationVelocity.SetZero();
  if (m_Settings.m_ApplyMovement)
  {
    uint64_t cur_frame_id = sprite->GetAnimationFrameId(player.m_AnimIndex, player.m_AnimFrame);
    Vector2 cur_anchor_position = sprite->GetAnchor(COMPILE_TIME_CRC32_STR("Movement"), cur_frame_id);

    Vector2 prev_anchor_position = {};
    if (player.m_AnimFrame > 0)
    {
      uint64_t prev_frame_id = sprite->GetAnimationFrameId(player.m_AnimIndex, player.m_AnimFrame - 1);
      prev_anchor_position = sprite->GetAnchor(COMPILE_TIME_CRC32_STR("Movement"), prev_frame_id);
    }

    auto frame_duration = sprite->GetAnimationFrameDuration(player.m_AnimIndex, player.m_AnimFrame);
    if (frame_duration > 0)
    {
      auto animation_movement = GameNetVec2(GameNetVal(cur_anchor_position.x - prev_anchor_position.x), 
                                            GameNetVal(cur_anchor_position.y - prev_anchor_position.y));

      m_AnimationVelocity = animation_movement / GameNetVal(frame_duration);

      if (player.m_Facing == CharacterFacing::kLeft)
      {
        m_AnimationVelocity.x = -m_AnimationVelocity.x;
      }
    }
  }

  player.MoveCheckCollisionDatabase(game_container, m_AnimationVelocity);
}

void PlayerStateBasicAttack::Transition(PlayerServerObject & player, GameLogicContainer & game_container)
{
#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
  if (m_Settings.m_InterruptIfNoGround && player.m_OnGround == false)
  {
    player.TransitionToState<PlayerStateJump>(game_container);
    return;
  }
#endif
}

void PlayerStateBasicAttack::Animate(PlayerServerObject & player, GameLogicContainer & game_container)
{
  bool finished = player.FrameAdvance(m_AnimationHash, false);
  player.TriggerAnimationEvents(game_container, *this);

  if (finished)
  {
    if (m_Settings.m_RetainMovement)
    {
      player.m_Velocity += m_AnimationVelocity;
    }

#if PROJECT_PERSPECTIVE == PERSPECTIVE_SIDESCROLLER
    if (player.m_OnGround)
    {
      player.TransitionToState<PlayerStateIdle>(game_container);
    }
    else
    {
      player.TransitionToState<PlayerStateJump>(game_container);
    }
#else
    player.TransitionToState<PlayerStateIdle>(game_container);
#endif

    return;
  }
}

void PlayerStateBasicAttack::PostUpdate(PlayerServerObject & player, GameLogicContainer & game_container)
{
  if (m_DamageSettings)
  {
    DamageEvent dmg;
    dmg.m_Amount = m_DamageSettings->m_DamageAmount;
    dmg.m_DamageType = m_DamageSettings->m_DamageType;
    dmg.m_AttackId = player.m_AttackId;
    dmg.m_Source = player.GetSlotIndex();
    dmg.m_Direction = player.m_Facing;

    player.PushDealDamageEventBoxes(COMPILE_TIME_CRC32_STR("DealDamage"), dmg, game_container);
  }
}

bool PlayerStateBasicAttack::HandleDealDamageEvent(const DealDamageAnimationEvent & ev, const EventMetaData & meta)
{
  auto player = static_cast<PlayerServerObject *>(meta.m_SourceServerObject);
  return player->HandleDealDamageEvent(ev, meta);
}
