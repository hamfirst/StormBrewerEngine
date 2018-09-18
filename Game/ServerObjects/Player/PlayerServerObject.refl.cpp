

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.meta.h"

#include "Game/ServerObjects/Player/States/PlayerStateIdle.refl.h"
#include "Game/ServerObjects/Player/States/PlayerStateJump.refl.h"

#include "Game/Configs/PlayerConfig.refl.meta.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Animation/AnimationState.h"

GLOBAL_ASSET(SpritePtr, "./Sprites/Player.sprite", g_PlayerSprite);
GLOBAL_ASSET_ARRAY(ConfigPtr<PlayerConfig>, g_PlayerConfig, "./Configs/PlayerConfig.playerconfig");

void PlayerServerObject::Init(const PlayerServerObjectInitData & init_data)
{
  m_State.SetType<PlayerStateIdle>();
}

void PlayerServerObject::UpdateFirst(GameLogicContainer & game_container)
{
  m_ProcessedAttacks.clear();
}

void PlayerServerObject::UpdateMiddle(GameLogicContainer & game_container)
{
  m_State->PreUpdate(*this, game_container);
  m_State->Move(*this, game_container);

  m_Retransition = true;
  m_State->Transition(*this, game_container);
  m_Retransition = false;

  m_State->Animate(*this, game_container);
  m_State->PostUpdate(*this, game_container);

  auto box = g_PlayerSprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox")).Offset(m_Position);
  game_container.GetSystems().GetCVCPushSystem().SetCharacterCVCPosition(box, this);
}

void PlayerServerObject::UpdateLast(GameLogicContainer & game_container)
{
  auto box = g_PlayerSprite->GetSingleBox(COMPILE_TIME_CRC32_STR("MoveBox"));
  box = box.Offset(m_Position);

  for (auto & kill_vol : game_container.GetStage().GetKillVolumes())
  {
    if (BoxIntersect(box, kill_vol))
    {
      DamageEvent ev;
      ev.m_Amount = 255;
      ev.m_Direction = m_Facing;
      ev.m_Source = -1;
      ev.m_AttackId = -1;
      ev.m_DamageType = DamageType::kFall;

      SendEvent(ev, EventMetaData(game_container));
      return;
    }
  }

  auto frame_id = g_PlayerSprite->GetAnimationFrameId(m_AnimIndex, m_AnimFrame);

  auto hurt_boxes = g_PlayerSprite->GetMultiBox(COMPILE_TIME_CRC32_STR("ReceiveDamage"), frame_id);
  for (auto & box : hurt_boxes)
  {
    PushReceiveDamageBox(box, game_container);
  }
}

void PlayerServerObject::ResetState(GameLogicContainer & game_container)
{
  TransitionToState<PlayerStateIdle>(game_container);

  if (GetSlotIndex() == 0)
  {
    m_Facing = CharacterFacing::kRight;
  }
  else
  {
    m_Facing = CharacterFacing::kLeft;
  }

  m_Health = 255;
}

MoverResult PlayerServerObject::MoveCheckCollisionDatabase(GameLogicContainer & game_container, const GameNetVec2 & extra_movement)
{
#ifdef MOVER_ONE_WAY_COLLISION
  auto result = GameServerObjectBase::MoveCheckCollisionDatabase(game_container, m_Velocity + extra_movement, m_FallThrough);
#else
  auto result = GameServerObjectBase::MoveCheckCollisionDatabase(game_container, m_Velocity + extra_movement);
#endif

  if (result.m_HitRight)
  {
    m_Velocity.x = 0;
  }
  else if (result.m_HitLeft)
  {
    m_Velocity.x = 0;
  }

  if (result.m_HitTop)
  {
    m_Velocity.y = 0;
  }
  else if (result.m_HitBottom)
  {
    m_Velocity.y = 0;
  }

#ifdef PLATFORMER_MOVEMENT

  m_OnGround = result.m_HitBottom;
  m_OnOneWayCollision = result.m_HitBottom && result.m_HitBottom->m_Mask == COLLISION_LAYER_ONE_WAY;

  m_FallThrough = false;

#endif

  return result;
}

#if defined(PLATFORMER_MOVEMENT)
void PlayerServerObject::Jump(GameLogicContainer & game_container)
{
#if defined(PLAYER_ENABLE_JUMP)
  if (m_OnGround)
  {
    if (m_OnOneWayCollision && m_Input.m_YInput < GameNetVal(GetConfig()->m_FallthroughThreshold).Invert())
    {
      m_FallThrough = true;
    }
    else
    {
      game_container.GetEventSender().BroadcastServerAuthEvent(PlaceholderServerAuthEvent{});

      m_Velocity.y += GetConfig()->m_JumpSpeed;
      m_OnGround = false;

      TransitionToState<PlayerStateJump>(game_container);
    }
  }
  else if (m_State.Is<PlayerStateJump>())
  {
    auto jump_state = m_State.Get<PlayerStateJump>();

    if (jump_state->CanGraceJump())
    {
      m_Velocity.y += GetConfig()->m_JumpSpeed;
      TransitionToState<PlayerStateJump>(game_container);
    }
  }

#endif
}
#endif

bool PlayerServerObject::HandlePlaceholderEvent(PlaceholderEvent & ev, const EventMetaData & meta)
{
  return true;
}

bool PlayerServerObject::HandleDamageEvent(DamageEvent & ev, const EventMetaData & meta)
{
  auto & game = *meta.m_GameLogicContainer;

#ifdef NET_USE_ROUND_TIMER
  if (game.GetInstanceData().m_RoundState != RoundState::kRound)
  {
    return false;
  }
#endif

  if (m_Invulnerable)
  {
    return false;
  }

  if (ev.m_Source == GetSlotIndex())
  {
    return false;
  }

  if (vfind(m_ProcessedAttacks, ev.m_AttackId))
  {
    return false;
  }

  m_ProcessedAttacks.push_back(ev.m_AttackId);

  if (ev.m_Amount >= m_Health)
  {
#ifdef NET_USE_ROUND_TIMER
    auto other_player = game.GetObjectManager().GetReservedSlotObjectAs<PlayerServerObject>(GetSlotIndex() == 0 ? 1 : 0);
    game.GetInstanceData().m_RoundState = RoundState::kPostRound;
    game.GetInstanceData().m_RoundTimer = kMaxCountdown;
#endif
    m_Health = 0;
  }
  else
  {
    m_Health -= ev.m_Amount;
  }

  return true;
}

bool PlayerServerObject::HandleDealDamageEvent(DealDamageAnimationEvent & ev, const EventMetaData & meta)
{
  auto & game_container = *meta.m_GameLogicContainer;

  for (auto b = meta.m_ActiveAreaStart; b != meta.m_ActiveAreaEnd; ++b)
  {
    DamageEvent dmg;
    dmg.m_Amount = ev.m_Amount;
    dmg.m_DamageType = ev.m_DamageType;
    dmg.m_AttackId = m_AttackId;
    dmg.m_Source = GetSlotIndex();
    dmg.m_Direction = m_Facing.ToEnum();

    PushDealDamageBox(*b, dmg, game_container);
  }

  return true;
}

Optional<AnimationState> PlayerServerObject::GetAnimationState() const
{
  AnimationState state;
  state.m_AnimIndex = m_AnimIndex;
  state.m_AnimFrame = m_AnimFrame;
  state.m_AnimDelay = m_AnimDelay;
  return state;
}

void PlayerServerObject::SetAnimationState(const AnimationState & anim_state)
{
  m_AnimIndex = anim_state.m_AnimIndex;
  m_AnimFrame = anim_state.m_AnimFrame;
  m_AnimDelay = anim_state.m_AnimDelay;
}

Optional<int> PlayerServerObject::GetAssociatedPlayer() const
{
  return GetSlotIndex();
}

SpritePtr PlayerServerObject::GetSprite() const
{
  return g_PlayerSprite;
}

Optional<CharacterFacing> PlayerServerObject::GetFacing() const
{
  return m_Facing.ToEnum();
}

czstr PlayerServerObject::GetDefaultEntityBinding() const
{
  return "./Entities/Player.entity";
}

const ConfigPtr<PlayerConfig> & PlayerServerObject::GetConfig() const
{
  return m_Config.Value();
}
