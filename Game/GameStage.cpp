
#include "GameStage.h"

GameStage::GameStage(const Map & map) :
  m_DynamicObjectCount(127)
{

}

GameFullState GameStage::CreateDefaultGameState() const
{
  return GameFullState{ ServerObjectManager(m_StaticObjects, m_DynamicObjectCount) };
}
