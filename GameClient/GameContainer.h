#pragma once

#include "Foundation/Common.h"

#include "Engine/Window/Window.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/EngineState.h"

#include "Game/GameStageManager.h"

#include "GameClient/GameMode.h"

class GameMode;

class GameContainer
{
public:
  GameContainer(const Window & window);
  ~GameContainer();

  EngineState & GetEngineState();
  Window & GetWindow();

  GameLevelList & GetLevelList();

  RenderState & GetRenderState();
  RenderUtil & GetRenderUtil();

  void Update();
  void Render();

private:
  EngineState m_EngineState;

  Window m_Window;
  std::unique_ptr<GameMode> m_Mode;

  GameLevelList m_LevelList;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;
};


