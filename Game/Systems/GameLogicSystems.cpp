
#include "Game/GameCommon.h"
#include "Game/Systems/GameLogicSystems.h"

GameLogicSystems::GameLogicSystems(const StaticCollisionDatabase & static_collision) :
  m_CollisionDatabase(static_collision)
{

}

CollisionDatabase & GameLogicSystems::GetCollisionDatabase()
{
  return m_CollisionDatabase;
}
