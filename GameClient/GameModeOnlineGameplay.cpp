
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
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


GameModeOnlineGameplay::GameModeOnlineGameplay(GameContainer & game) :
  GameMode(game)
{

}

GameModeOnlineGameplay::~GameModeOnlineGameplay()
{
  m_ClientSystems.Clear();
}

void GameModeOnlineGameplay::Initialize()
{
  auto & container = GetContainer();
  container.SetInstanceData(container.GetClient().GetClientInstanceData());
  m_ClientSystems.Emplace(container);

  container.SetClientSystems(&m_ClientSystems.Value());
  container.GetClient().FinalizeMapLoad();
}

void GameModeOnlineGameplay::OnAssetsLoaded()
{

}

void GameModeOnlineGameplay::Update()
{
  auto & container = GetContainer();
  auto & client = container.GetClient();
  auto instance_data = client.GetClientInstanceData();
  if (client.GetConnectionState() != ClientConnectionState::kConnected)
  {
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }

  if (instance_data->GetGameState().m_Started == false)
  {
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }

  if (instance_data->GetGameState().m_WiningTeam != -1)
  {
    auto instance_container = container.GetClient().ConvertToOffline();
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, std::move(instance_container));
    return;
  }

  client.Update();

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

void GameModeOnlineGameplay::Render()
{
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

