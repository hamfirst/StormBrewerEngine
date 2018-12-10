#pragma once

#include "Engine/UI/UIManager.h"

#include "Game/GameNetworkSettings.h"

#include "Foundation/Sequencer/Sequencer.h"

class GameContainer;
class GameClientEventSender;
class GameCamera;

class RenderState;
class RenderUtil;

class GameClientUIManager
{
public:
  GameClientUIManager(GameContainer & container);
  ~GameClientUIManager();

  void Update();
  void Render();

  void ShowTutorial();
  bool IsPopupOpen();
  void DisablePopup();

  bool IsBlocking();
  bool WantsToQuit();

  UIManager & GetUIManager();

protected:

  void TogglePopup();

  void Quit();

private:

  GameContainer & m_GameContainer;

  UIManager m_UIManager;

  bool m_WantsToQuit;
  bool m_DisabledPopup;
};

