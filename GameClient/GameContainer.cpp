
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeLoadingGlobal.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameCamera.h"

#include "Engine/Text/TextManager.h"

NullOptPtr<ServerObjectManager> GetServerObjectManager(NotNullPtr<GameContainer> game)
{
  auto instance_data = game->GetInstanceData();
  return instance_data ? &instance_data->GetFullState().m_ServerObjectManager : nullptr;
}

GameContainer::GameContainer(const Window & window, std::unique_ptr<GameContainerInitSettings> && init_settings) :
  m_EngineState(this),
  m_LevelList(),
  m_Window(window),
  m_InitSettings(std::move(init_settings)),
  m_ClientInstanceData(nullptr),
  m_ClientSystems(nullptr)
{
  auto resolution = m_Window.GetSize();
  m_RenderState.InitRenderState(resolution.x, resolution.y);
  m_RenderState.EnableBlendMode();

  m_RenderUtil.SetClearColor(Color(100, 149, 237, 255));
  m_RenderUtil.LoadShaders();

  SetInitialMode();
}

GameContainer::~GameContainer()
{

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

GameSharedGlobalResources & GameContainer::GetSharedGlobalResources()
{
  return m_SharedGlobalResources;
}

GameClientGlobalResources & GameContainer::GetClientGlobalResources()
{
  return m_ClientGlobalResources;
}

NullOptPtr<GameClientInstanceData> GameContainer::GetInstanceData()
{
  return m_ClientInstanceData;
}

void GameContainer::SetInstanceData(NullOptPtr<GameClientInstanceData> instance_data)
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

RenderState & GameContainer::GetRenderState()
{
  return m_RenderState;
}

RenderUtil & GameContainer::GetRenderUtil()
{
  return m_RenderUtil;
}

void GameContainer::StartNetworkClient()
{
  m_Client = std::make_unique<GameNetworkClient>(*this, m_NetInitSettings);
}

void GameContainer::StopNetworkClient()
{
  m_Client.reset();
}

GameNetworkClient & GameContainer::GetClient()
{
  ASSERT(m_Client, "Attempting to get client when network client has not been started");
  return *m_Client.get();
}

GameNetworkClientInitSettings & GameContainer::GetNetworkInitSettings()
{
  return m_NetInitSettings;
}

bool GameContainer::AllGlobalResourcesLoaded()
{
  return m_LevelList.IsLevelListLoaded() && m_ClientGlobalResources.IsLoaded() && m_SharedGlobalResources.IsLoaded();
}

void GameContainer::Update()
{
  m_RenderState.SetScreenSize(m_Window.GetSize());
  m_RenderState.SetRenderSize(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));

  if (m_Mode)
  {
    m_Mode->Step();
  }
}

void GameContainer::Render()
{
  if (m_Mode)
  {
    m_Mode->Render();
  }
  else
  {
    m_RenderUtil.Clear();
    g_TextManager.SetTextPos(Vector2(20, 20));
    g_TextManager.RenderText("No mode set", -1, m_RenderState);
  }

  m_Window.Swap();
}
