
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeEndGame.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentUpdateBucketList.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/EngineState.h"


GameModeSinglePlayerBots::GameModeSinglePlayerBots(GameContainer & game, const std::string & player_name, const GameInitSettings game_settings) :
  GameMode(game),
  m_PlayerName(player_name)
{
  auto & container = GetContainer();
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(container);
  m_InstanceContainer->Load(game_settings);
}

GameModeSinglePlayerBots::~GameModeSinglePlayerBots()
{
  m_ClientSystems.Clear();
}

void GameModeSinglePlayerBots::Initialize()
{

}

void GameModeSinglePlayerBots::OnAssetsLoaded()
{
  m_InstanceData.Emplace(m_InstanceContainer->GetInstanceData(*this));

  m_ClientSystems.Emplace(GetContainer());

  auto & container = GetContainer();
  container.SetInstanceData(m_InstanceData.GetPtr());
  container.SetClientSystems(&m_ClientSystems.Value());

  auto game_logic = m_InstanceContainer->GetLogicContainer(true);
  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetGameController().ConstructPlayer(0, game_logic, m_PlayerName, 0);
  m_InstanceContainer->GetGameController().PlayerReady(0, game_logic);
  m_InstanceContainer->GetGameController().FillWithBots(game_logic, GetRandomNumber());
  m_InstanceContainer->GetGameController().StartGame(game_logic);

}

void GameModeSinglePlayerBots::Update()
{
  auto & container = GetContainer();
  auto & instance_data = m_InstanceData.Value();

  if (instance_data.GetGameState().m_WiningTeam != -1)
  {
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, std::move(m_InstanceContainer));
    return;
  }

  m_InstanceContainer->Update();

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();

  ComponentUpdateBucketList update_list;
  comp_system->CreateUpdateBucketList(update_list);

  for (int index = 0, end = update_list.GetNumBuckets(); index < end; ++index)
  {
    update_list.CallFirst(index);
    entity_system->FinalizeEvents();

    update_list.CallMiddle(index);
    entity_system->FinalizeEvents();

    update_list.CallLast(index);
    entity_system->FinalizeEvents();
  }

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  ui_manager.Update();
  input_manager.Update();
}

void GameModeSinglePlayerBots::Render()
{
  if (IsLoaded() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  render_state.SetRenderSize(camera.GetGameResolution());

  render_util.SetClearColor(Color(100, 149, 237, 255));
  render_util.Clear();

  auto & engine_state = container.GetEngineState();
  auto entity_system = engine_state.GetEntitySystem();
  auto map_system = engine_state.GetMapSystem();

  auto screen_resolution = container.GetWindow().GetSize();

  camera.SetScreenResolution(screen_resolution);
  camera.Update();

  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetPosition(), camera.GetGameResolution());

  camera.Draw(container, &engine_state, render_state, render_util);

  input_manager.Render();
  ui_manager.Render();
}

bool GameModeSinglePlayerBots::IsLoaded()
{
  if(m_InstanceContainer->IsLoaded() == false)
  {
    return false;
  }

  return GameMode::IsLoaded();
}

void GameModeSinglePlayerBots::SendClientEvent(std::size_t class_id, const void * event_ptr)
{
  auto game = m_InstanceContainer->GetLogicContainer(true);
  m_InstanceContainer->GetGameController().HandleClientEvent(0, game, class_id, event_ptr);
}
