#pragma once

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"

#include "Game/GameNetworkSettings.h"

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

  bool IsBlocking();

  UIClickablePtr CreateClickable(const Box & active_area);
private:

  GameContainer & m_GameContainer;

  UIManager m_UIManager;

#ifdef NET_USE_COUNTDOWN
  UIElementPtr<UIElementText> m_CountdownCaption;
  UIElementPtr<UIElementText> m_Countdown;
#endif

#ifdef NET_USE_ROUND_TIMER
  UIElementPtr<UIElementText> m_RoundTimerCaption;
  UIElementPtr<UIElementText> m_RoundTimer;
#endif
};

