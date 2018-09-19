#pragma once

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"
#include "Engine/UI/Prototype/UIPrototypeConfirmPopup.h"
#include "Engine/UI/Prototype/UIPrototypeMuteButton.h"
#include "Engine/UI/Prototype/UIPrototypeFullscreenButton.h"

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

  UIClickablePtr CreateClickable(const Box & active_area);
  UIManager & GetUIManager();

protected:

  void TogglePopup();

  void Quit();

private:

  GameContainer & m_GameContainer;

  UIManager m_UIManager;
  UIElementHandle m_HudHandle;

  Optional<UIPrototypeConfirmPopup> m_QuitPopup;
  Optional<UIElementHandle> m_Tutorial;
  Optional<UIPrototypeButton> m_TutorialOkay;

  Optional<UIPrototypeMuteButton> m_MuteButton;
  Optional<UIPrototypeMuteButton> m_MusicButton;
  Optional<UIPrototypeFullscreenButton> m_FullscreenButton;

  bool m_WantsToQuit;
  bool m_DisabledPopup;
};

