#pragma once

#include "GameClient/GameCamera.h"
#include "GameClient/GameClientInputManager.h"
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameNetworkClient.h"

class GameContainer;

class GameClientSystems
{
public:
  GameClientSystems(GameContainer & container);
  ~GameClientSystems();

  GameClientInputManager & GetInputManager();
  GameClientUIManager & GetUIManager();

  GameCamera & GetCamera();

private:

  GameClientInputManager m_InputManager;
  GameClientUIManager m_UIManager;

  GameCamera m_Camera;
};
