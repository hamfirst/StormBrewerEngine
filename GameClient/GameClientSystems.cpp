#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientSystems.h"


GameClientSystems::GameClientSystems(GameContainer & container) :
  m_InputManager(container),
  m_UIManager(container),
  m_Camera(container)
{

}

GameClientSystems::~GameClientSystems()
{

}

GameClientInputManager & GameClientSystems::GetInputManager()
{
  return m_InputManager;
}

GameClientUIManager & GameClientSystems::GetUIManager()
{
  return m_UIManager;
}

GameCamera & GameClientSystems::GetCamera()
{
  return m_Camera;
}