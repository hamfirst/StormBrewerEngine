
#include "GameClient/GameClientInstanceContainer.h"
#include "GameClient/GameContainer.h"


GameClientInstanceContainer::GameClientInstanceContainer(GameContainer & game_container) :
  m_GameContainer(game_container),
  m_ClientController(game_container),
  m_LevelLoader(game_container),
  m_EntitySync(game_container),
  m_Loaded(false)
{

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
  int send_timer = 0;
  auto logic_container = GetLogicContainer(m_GameContainer.GetSharedGlobalResources(), false, send_timer);

  GetGameController().Update(logic_container);
  GetEntitySync().Sync(GetSim().m_ServerObjectManager);
}

GameClientInstanceData GameClientInstanceContainer::GetInstanceData(GameClientEventSender & event_sender)
{
  return GameClientInstanceData(m_Sim.Value(), m_ClientData, *m_Stage.get(), m_SharedResources.Value(), m_ClientResources.Value(), event_sender);
}

GameLogicContainer GameClientInstanceContainer::GetLogicContainer(GameSharedGlobalResources & shared_resources, bool authority, int & send_timer)
{
  return GameLogicContainer(
    GetGameController(),
    GetSim().m_GlobalData,
    GetSim().m_ServerObjectManager,
    GetClientController(),
    GetClientController(),
    shared_resources,
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

ClientLocalData & GameClientInstanceContainer::GetClientData()
{
  return m_ClientData;
}

ClientAuthData & GameClientInstanceContainer::GetClientAuthData()
{
  return m_ClientAuthData;
}

GameFullState & GameClientInstanceContainer::GetSim()
{
  return m_Sim.Value();
}

GameFullState & GameClientInstanceContainer::GetDefaultSim()
{
  return m_DefaultSim.Value();
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
