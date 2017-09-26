
#include "GameClient/GameClientInstanceContainer.h"
#include "GameClient/GameContainer.h"

int s_BogusSendTimer = 0;

GameClientInstanceContainer::GameClientInstanceContainer(GameContainer & game_container, int num_local_clients, bool authority,
                                                         NullOptPtr<GameEventReconciler> reconciler, NullOptPtr<int> reconcile_frame) :
  m_GameContainer(game_container),
  m_ClientController(game_container),
  m_LevelLoader(game_container),
  m_EntitySync(game_container),
  m_ServerEventResponder(&m_ClientController, reconciler, reconcile_frame),
  m_Loaded(false),
  m_NumLocalClients(num_local_clients),
  m_Authority(authority)
{
  m_ClientData.resize(num_local_clients);
  m_ClientAuthData.resize(num_local_clients);
}

GameClientInstanceContainer::~GameClientInstanceContainer()
{

}

void GameClientInstanceContainer::Load(const GameInitSettings & init_settings, uint64_t load_token)
{
  m_ClientController.PreloadLevel();
  m_InitSettings = init_settings;

  m_LevelLoader.LoadLevel(init_settings, load_token, [this, load_token](uint64_t, const Map & map) 
  {
    m_Loaded = true;
    m_Stage = std::make_unique<GameStage>(map);

    m_Sim.Emplace(m_Stage->CreateDefaultGameState());
    m_DefaultSim.Emplace(m_Stage->CreateDefaultGameState());
  });

  m_SharedResources.Emplace(init_settings);
  m_ClientResources.Emplace(init_settings);
}

bool GameClientInstanceContainer::IsLoaded()
{
  if (m_Loaded)
  {
    return m_SharedResources->IsLoaded() && m_ClientResources->IsLoaded();
  }

  return false;
}

void GameClientInstanceContainer::Update()
{
  auto logic_container = GetLogicContainer(m_Authority);

  GetGameController().Update(logic_container);
  GetEntitySync().Sync(GetState().m_ServerObjectManager);
}

GameClientInstanceData GameClientInstanceContainer::GetClientInstanceData(GameClientEventSender & event_sender)
{
  return GameClientInstanceData(
    m_GameContainer, 
    m_GameController, 
    m_ClientController, 
    m_Sim.Value(), 
    m_ClientData.data(), m_NumLocalClients,
    *m_Stage.get(), 
    m_SharedResources.Value(), 
    m_ClientResources.Value(), 
    event_sender,
    m_ServerEventResponder);
}

GameLogicContainer GameClientInstanceContainer::GetLogicContainer(bool authority, int & send_timer)
{
  return GameLogicContainer(
    GetGameController(),
    GetState().m_InstanceData,
    GetState().m_ServerObjectManager,
    m_ServerEventResponder,
    GetClientController(),
    m_GameContainer.GetSharedGlobalResources(),
    GetSharedResources(),
    GetStage(),
    authority, send_timer);
}

GameController & GameClientInstanceContainer::GetGameController()
{
  return m_GameController;
}

GameClientController & GameClientInstanceContainer::GetClientController()
{
  return m_ClientController;
}

GameClientLevelLoader & GameClientInstanceContainer::GetLevelLoader()
{
  return m_LevelLoader;
}

GameClientEntitySync & GameClientInstanceContainer::GetEntitySync()
{
  return m_EntitySync;
}

GameInitSettings & GameClientInstanceContainer::GetInitSettings()
{
  return m_InitSettings;
}

ClientLocalData & GameClientInstanceContainer::GetClientLocalData(std::size_t client_index)
{
  return m_ClientData[client_index];
}

ClientAuthData & GameClientInstanceContainer::GetClientAuthData(std::size_t client_index)
{
  return m_ClientAuthData[client_index];
}

GameFullState & GameClientInstanceContainer::GetState()
{
  return m_Sim.Value();
}

GameFullState & GameClientInstanceContainer::GetDefaultState()
{
  return m_DefaultSim.Value();
}

GameInstanceData & GameClientInstanceContainer::GetInstanceData()
{
  return m_Sim.Value().m_InstanceData;
}

GameSharedInstanceResources & GameClientInstanceContainer::GetSharedResources()
{
  return m_SharedResources.Value();
}

GameClientInstanceResources & GameClientInstanceContainer::GetClientResources()
{
  return m_ClientResources.Value();
}

GameStage & GameClientInstanceContainer::GetStage()
{
  return *m_Stage.get();
}
