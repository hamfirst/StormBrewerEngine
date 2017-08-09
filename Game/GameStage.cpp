
#include "Game/GameStage.h"

#include "Foundation/BasicTypes/BasicTypeHash.h"
#include "Foundation/Pathfinding/Pathfinding.h"

GameStage::GameStage(const Map & map) :
  m_DynamicObjectCount(127)
{

}

GameStage::~GameStage()
{

}

GameFullState GameStage::CreateDefaultGameState() const
{
  return GameFullState{ ServerObjectManager(m_StaticObjects, m_DynamicObjectCount, kMaxPlayers) };
}
