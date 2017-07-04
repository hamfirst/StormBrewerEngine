#pragma once

#include "Foundation/Common.h"

#include "Engine/Window/Window.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/EngineState.h"

#include "Game/GameStageManager.h"

#include "GameClient/GameMode.h"
#include "GameClient/GameGlobalResources.h"

class GameMode;
class GameNetworkClient;

template <typename GameMode>
struct GameModeDef {};

class GameContainer
{
public:
  GameContainer(const Window & window);
  ~GameContainer();

  void SetInitialMode();

  EngineState & GetEngineState();
  Window & GetWindow();

  GameLevelList & GetLevelList();

  RenderState & GetRenderState();
  RenderUtil & GetRenderUtil();

  void StartNetworkClient(const char * remote_ip, int remote_port);
  void StopNetworkClient();
  GameNetworkClient & GetClient();

  bool AllGlobalResourcesLoaded();

  void Update();
  void Render();

  template <typename Mode, typename ... Args>
  void SwitchMode(const GameModeDef<Mode> & def, Args && ... args)
  {
    m_Mode = std::make_unique<Mode>(std::forward<Args>(args)...);
    m_Mode->Initialize(*this);
  }

private:
  EngineState m_EngineState;

  Window m_Window;
  std::unique_ptr<GameMode> m_Mode;
  std::unique_ptr<GameNetworkClient> m_Client;

  GameGlobalResources m_GlobalResources;
  GameLevelList m_LevelList;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;
};


