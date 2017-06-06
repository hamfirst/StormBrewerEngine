#pragma once

#include "Foundation/Common.h"

#include "Engine/Window/Window.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

#include "Game/GameState.h"
#include "GameClient/GameMode.h"

class GameMode;

class GameContainer
{
public:
  GameContainer(const Window & window);
  ~GameContainer();

  void Update();
  void Render();

  GameState & GetGameState();
  Window & GetWindow();

  RenderState & GetRenderState();
  RenderUtil & GetRenderUtil();

private:
  GameState m_GameState;

  Window m_Window;
  std::unique_ptr<GameMode> m_Mode;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;
};


