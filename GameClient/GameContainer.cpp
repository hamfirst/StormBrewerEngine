#include "GameClient/GameClientCommon.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeLoadingGlobal.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameCamera.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/Asset/Asset.h"

GameSharedGlobalResources & GetSharedGlobalResourcesFromContainer(NotNullPtr<GameContainer> container)
{
  return container->GetSharedGlobalResources();
}

GameClientGlobalResources & GetClientGlobalResourcesFromContainer(NotNullPtr<GameContainer> container)
{
  return container->GetClientGlobalResources();
}

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

GameContainer::GameContainer(const Window & window, std::unique_ptr<GameContainerInitSettings> && init_settings) :
  m_EngineState(this),
  m_LevelList(),
  m_Window(window),
  m_InitSettings(std::move(init_settings)),
  m_ClientInstanceData(nullptr),
  m_ClientSystems(nullptr),
  m_Updating(false)
{
  auto resolution = m_Window.GetSize();
  m_RenderState.InitRenderState(resolution.x, resolution.y);
  m_RenderState.EnableBlendMode();

  m_RenderUtil.SetClearColor(Color(100, 149, 237, 255));
  m_RenderUtil.LoadShaders();

  m_SharedGlobalResources.Emplace();
  m_ClientGlobalResources.Emplace();

  g_GlobalAssetList.BeginAssetLoad();

  SetInitialMode();
}

GameContainer::~GameContainer()
{
  m_SharedGlobalResources.Clear();
  m_ClientGlobalResources.Clear();

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

GameSharedGlobalResources & GameContainer::GetSharedGlobalResources()
{
  return m_SharedGlobalResources.Value();
}

GameClientGlobalResources & GameContainer::GetClientGlobalResources()
{
  return m_ClientGlobalResources.Value();
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
  m_Client = std::make_unique<GameNetworkClient>(*this);
}

void GameContainer::StopNetworkClient()
{
  m_Client.reset();
}

bool GameContainer::HasClient() const
{
  return m_Client.get() != nullptr;
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
  return m_LevelList.IsLevelListLoaded() && m_ClientGlobalResources->IsLoaded() && m_SharedGlobalResources->IsLoaded();
}

void GameContainer::Update()
{
  m_Updating = true;
  m_RenderState.SetScreenSize(m_Window.GetSize());
  m_RenderState.SetRenderSize(Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight));

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
