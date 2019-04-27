#pragma once

#include "Foundation/Common.h"
#include "Foundation/Time/StopWatch.h"

#include "Engine/Window/Window.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/UI/UIManager.h"
#include "Engine/EngineState.h"

#include "Runtime/UI/UIResource.h"

#include "GameShared/GameStageManager.h"

#include "GameClient/Modes/GameMode.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientSave.h"
#include "GameClient/GameClientLatencyChecker.h"

#include "LobbyClientConnection/LobbyClientConnection.h"

class GameMode;
class GameNetworkClient;
class GameClientInstanceContainer;

struct GameContainerInitSettings
{
  bool m_AutoConnect = false;
  bool m_AutoBotGame = false;

  LobbyLoginMode m_LoginMode = LobbyLoginMode::kGuest;
  std::string m_LoadBalancerHostName = "127.0.0.1";
  std::string m_Token;
  std::string m_UserName;
};

class GameContainer
{
public:
  GameContainer(Window & window, std::unique_ptr<GameContainerInitSettings> && init_settings = std::make_unique<GameContainerInitSettings>());
  GameContainer(const GameContainer & rhs) = delete;
  GameContainer(GameContainer && rhs) = delete;
  GameContainer & operator =(const GameContainer & rhs) = delete;
  GameContainer & operator =(GameContainer && rhs) = delete;

  ~GameContainer();

  void SetInitialMode();

  EngineState & GetEngineState();
  Window & GetWindow();

  NullOptPtr<GameContainerInitSettings> GetInitSettings();
  void ReleaseInitSettings();

  GameLevelList & GetLevelList();
  GameClientSave & GetSave();

  NullOptPtr<GameClientInstanceContainer> GetInstanceData();
  void SetInstanceData(NullOptPtr<GameClientInstanceContainer> instance_data);

  NullOptPtr<GameClientSystems> GetClientSystems();
  void SetClientSystems(NullOptPtr<GameClientSystems> client_systems);

  RenderState & GetRenderState();

  void StartLobbyClient();
  void StopLobbyClient();
  bool HasLobbyClient();
  LobbyClientConnection & GetLobbyClient();

  void StartLatencyChecker();
  void StopLatencyChecker();
  bool HasLatencyChecker();
  GameClientLatencyChecker & GetLatencyChecker();
  
  void StartNetworkClient(const GameNetworkClientInitSettings & settings);
  void StopNetworkClient();
  bool HasClient() const;
  GameNetworkClient & GetGameClient();

  bool AllGlobalResourcesLoaded();

  void Update();
  void Render();
  void InputEvent();

  template <typename Mode, typename ... Args>
  void SwitchMode(Args && ... args)
  {
    if(m_Mode.get())
    {
      m_Mode->Deinit();
    }

    if (m_Updating)
    {
      m_NextMode = std::make_unique<Mode>(*this, std::forward<Args>(args)...);
      m_NextMode->Initialize();
    }
    else
    {
      m_Mode = std::make_unique<Mode>(*this, std::forward<Args>(args)...);
      m_Mode->Initialize();
    }
  }

  void UpdateUIManager();
  void RenderUIManager();
  void ClearUIManager();
  NotNullPtr<UIManager> GetUIManager();


private:
  EngineState m_EngineState;
  StopWatch m_FrameClock;
  float m_DeltaTime = 0;

  Window m_Window;
  std::unique_ptr<GameMode> m_Mode;
  std::unique_ptr<GameMode> m_NextMode;
  std::unique_ptr<GameNetworkClient> m_Client;
  std::unique_ptr<GameClientLatencyChecker> m_LatencyChecker;
  std::unique_ptr<LobbyClientConnection> m_LobbyConnection;
  std::unique_ptr<GameContainerInitSettings> m_InitSettings;

  NullOptPtr<GameClientInstanceContainer> m_ClientInstanceData;
  NullOptPtr<GameClientSystems> m_ClientSystems;

  GameLevelList m_LevelList;
  GameClientSave m_Save;

  RenderState m_RenderState;

  bool m_Updating = false;
};


