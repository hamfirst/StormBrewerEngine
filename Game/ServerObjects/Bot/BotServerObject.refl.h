#pragma once

#include "Game/GameCommon.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameStage.h"
#include "Game/Systems/GameLogicSystems.h"
#include "Game/ServerObjects/CharacterFacing.refl.h"

#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectRegistrationMacros.h"

#include "StormBehavior/StormBehaviorTree.h"

struct BotServerObjectInitData : public ServerObjectInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED(BotServerObjectInitData);
};

class BotServerObject : public ServerObject
{
public:
  DECLARE_SERVER_OBJECT;

  BotServerObject() = default;
  BotServerObject(const BotServerObject & rhs) = default;
  BotServerObject(BotServerObject && rhs) = default;

  BotServerObject & operator = (const BotServerObject & rhs) = default;
  BotServerObject & operator = (BotServerObject && rhs) = default;

  void Init(const BotServerObjectInitData & init_data);
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);

  MoverResult MoveCheckCollisionDatabase(GameLogicContainer & game_container);
  void MoveCheckIntersectionDatabase(GameLogicContainer & game_container, GameNetVal player_radius, GameNetVal move_threshold);

  bool FrameAdvance(uint32_t anim_name_hash, bool loop = true, int frames = 1);
  
  virtual void InitPosition(const Vector2 & pos) override;
  virtual Vector2 GetPosition(GameLogicContainer & game_container) const override;

  virtual SpriteResource * GetSprite();
  virtual StormBehaviorTree<BotServerObject, GameLogicContainer> * GetBehaviorTree();
  void RetransitionBT();

public:

  GameNetVec2 m_Position = {};
  GameNetVec2 m_Velocity = {};

#ifdef PLATFORMER_MOVEMENT
  bool m_OnGround;
#endif

  NetRangedNumber<int, -1, 30> m_AnimIndex = -1;
  NetRangedNumber<int, 0, 31> m_AnimFrame = 0;
  NetRangedNumber<int, 0, 63> m_AnimDelay = 0;
  NetEnum<CharacterFacing> m_Facing = CharacterFacing::kRight;

private:
  bool m_Retransition = false;
};
