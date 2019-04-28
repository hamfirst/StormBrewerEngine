#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"
#include "GameClient/Modes/GameModeLoadingGlobal.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameCamera.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Asset/ClientAssetLoader.h"

#include "Runtime/Asset/Asset.h"


NullOptPtr<ServerObjectManager> GetServerObjectManager(NotNullPtr<GameContainer> game)
{
  auto instance_data = game->GetInstanceData();
  return instance_data ? &instance_data->GetFullState().m_ServerObjectManager : nullptr;
}

NullOptPtr<ServerObjectManager> GetServerObjectManager(NotNullPtr<GameContainer> game, int history_index)
{
  auto instance_data = game->GetInstanceData();
  return instance_data ? &instance_data->GetHistoryState(history_index).m_ServerObjectManager : nullptr;
}

GameContainer::GameContainer(Window & window, std::unique_ptr<GameContainerInitSettings> && init_settings) :
  m_EngineState(this, window),
  m_LevelList(),
  m_Window(window),
  m_InitSettings(std::move(init_settings)),
  m_ClientInstanceData(nullptr),
  m_ClientSystems(nullptr),
  m_Updating(false)
{
  auto resolution = m_Window.GetSize();

  m_RenderState.InitRenderState(resolution.x, resolution.y);
  m_RenderState.SetRenderSize(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));
  m_RenderState.EnableBlendMode();

  m_RenderState.SetDefaultClearColor();

  g_GlobalAssetList.BeginAssetLoad(&g_EngineClientAssetLoader);
  m_EngineState.GetUIManager()->LoadScripts(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));

  m_FrameClock.Start();

  m_LatencyChecker = std::make_unique<GameClientLatencyChecker>();
  m_LatencyChecker->Start();

  SetInitialMode();
}

GameContainer::~GameContainer()
{
  g_GlobalAssetList.UnloadAllAssets();
}

void GameContainer::SetInitialMode()
{
  m_Mode = std::make_unique<GameModeLoadingGlobal>(*this);
  m_Mode->Initialize();
}

EngineState & GameContainer::GetEngineState()
{
  return m_EngineState;
}

Window & GameContainer::GetWindow()
{
  return m_Window;
}

NullOptPtr<GameContainerInitSettings> GameContainer::GetInitSettings()
{
  return m_InitSettings.get();
}

void GameContainer::ReleaseInitSettings()
{
  m_InitSettings.reset();
}

GameLevelList & GameContainer::GetLevelList()
{
  return m_LevelList;
}

GameClientSave & GameContainer::GetSave()
{
  return m_Save;
}

NullOptPtr<GameClientInstanceContainer> GameContainer::GetInstanceData()
{
  return m_ClientInstanceData;
}

void GameContainer::SetInstanceData(NullOptPtr<GameClientInstanceContainer> instance_data)
{
  m_ClientInstanceData = instance_data;
}

NullOptPtr<GameClientSystems> GameContainer::GetClientSystems()
{
  return m_ClientSystems;
}

void GameContainer::SetClientSystems(NullOptPtr<GameClientSystems> client_systems)
{
  m_ClientSystems = client_systems;
}

void GameContainer::ResetAllGameplaySystems()
{
  m_EngineState.DestroyAllGameplayObjects();
}

RenderState & GameContainer::GetRenderState()
{
  return m_RenderState;
}

void GameContainer::StartLobbyClient()
{
  LobbyClientConnectionSettings settings;
  settings.m_LoadBalancerHostName = m_InitSettings->m_LoadBalancerHostName;
  settings.m_LoginMode = m_InitSettings->m_LoginMode;
  settings.m_Token = m_InitSettings->m_Token;
  settings.m_GuestUserName = m_InitSettings->m_UserName;

  m_LobbyConnection = std::make_unique<LobbyClientConnection>(settings);
}

void GameContainer::StopLobbyClient()
{
  m_LobbyConnection.reset();
}

bool GameContainer::HasLobbyClient()
{
  return m_LobbyConnection.get();
}

LobbyClientConnection & GameContainer::GetLobbyClient()
{
  return *m_LobbyConnection.get();
}

void GameContainer::StartLatencyChecker()
{
  m_LatencyChecker = std::make_unique<GameClientLatencyChecker>();
}

void GameContainer::StopLatencyChecker()
{
  m_LatencyChecker.reset();
}

bool GameContainer::HasLatencyChecker()
{
  return m_LatencyChecker.get();
}

GameClientLatencyChecker & GameContainer::GetLatencyChecker()
{
  return *m_LatencyChecker.get();
}

void GameContainer::StartNetworkClient(const GameNetworkClientInitSettings & settings)
{
  m_Client = std::make_unique<GameNetworkClient>(*this, settings);
}

void GameContainer::StopNetworkClient()
{
  m_Client.reset();
}

bool GameContainer::HasClient() const
{
  return m_Client.get() != nullptr;
}

GameNetworkClient & GameContainer::GetGameClient()
{
  ASSERT(m_Client, "Attempting to get client when network client has not been started");
  return *m_Client.get();
}

bool GameContainer::AllGlobalResourcesLoaded()
{
  return m_LevelList.IsLevelListLoaded() && m_EngineState.GetUIManager()->FinishedLoading();
}

void GameContainer::Update()
{
  m_DeltaTime = static_cast<float>(m_FrameClock.GetTimeSinceLastCheck());

  m_Updating = true;
  m_RenderState.SetScreenSize(m_Window.GetSize());

  m_Save.Update();

  if (m_Mode)
  {
    m_Mode->Step();
  }
  else
  {
    GetWindow().Update();
  }

  auto comp_system = m_EngineState.GetComponentSystem();
  comp_system->FinalizeComponentDestroys();

  if (m_NextMode)
  {
    m_Mode = std::move(m_NextMode);
  }

  m_Updating = false;


}

void GameContainer::Render()
{
  m_Window.MakeCurrent();

  m_RenderState.MakeCurrent();
  m_RenderState.BeginFrame(m_Window);

  if (m_Mode)
  {
    m_Mode->Render();
  }
  else
  {
    m_RenderState.Clear();
    g_TextManager.SetTextPos(Vector2(20, 20));
    g_TextManager.RenderText("No mode set", -1, 1, m_RenderState);
  }

  m_RenderState.FinalizeFrame(m_Window);

  m_Window.Swap();
}

void GameContainer::InputEvent()
{
  m_Updating = true;

  if (m_Mode)
  {
    m_Mode->InputEvent();
  }

  if (m_NextMode)
  {
    m_Mode = std::move(m_NextMode);
  }

  m_Updating = false;
}

void GameContainer::UpdateUIManager()
{
  auto & render_state = GetRenderState();

  auto input_state = GetWindow().GetInputState();
  GetEngineState().GetUIManager()->Update(m_DeltaTime, *input_state, render_state);
}

void GameContainer::RenderUIManager()
{
  auto & render_state = GetRenderState();
  GetEngineState().GetUIManager()->Render(render_state);
}

void GameContainer::ClearUIManager()
{
  GetEngineState().GetUIManager()->ClearUI();
}

NotNullPtr<UIManager> GameContainer::GetUIManager()
{
  return GetEngineState().GetUIManager();
}
