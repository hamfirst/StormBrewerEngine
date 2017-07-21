#pragma once

#include "Engine/UI/UIManager.h"
#include "Engine/UI/Prototype/UIPrototypeButton.h"

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
private:

  GameContainer & m_GameContainer;

  UIManager m_UIManager;
  UIElementPtr<UIElementText> m_Turn;
  UIElementPtr<UIElementGradient> m_EndTurn;
  UIElementPtr<UIElementText> m_EndTurnCaption;
  UIElementPtr<UIElementText> m_EndTurnTimer;
  UIElementPtr<UIElementText> m_PlayerHealth;
  UIElementPtr<UIElementText> m_OpponentHealth;
};

