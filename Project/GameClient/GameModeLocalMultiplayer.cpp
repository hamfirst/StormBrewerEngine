#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeLocalMultiplayer.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeEndGame.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentUpdateBucketList.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/EngineState.h"
#include "Engine/Audio/MusicManager.h"

#include <ctime>


GameModeLocalMultiplayer::GameModeLocalMultiplayer(GameContainer & game, const std::vector<bool> & attached_players, const GameInitSettings game_settings) :
  GameMode(game),
  m_AttachedPlayers(attached_players)
{
  int num_local_players = 0;
  for (auto attached : m_AttachedPlayers)
  {
    if (attached)
    {
      num_local_players++;
    }
  }

  auto & container = GetContainer();
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(container, *this, num_local_players, true);
  m_InstanceContainer->Load(game_settings);
}

GameModeLocalMultiplayer::~GameModeLocalMultiplayer()
{
  m_ClientSystems.reset();
}

void GameModeLocalMultiplayer::Initialize()
{

}

void GameModeLocalMultiplayer::OnAssetsLoaded()
{
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  auto & container = GetContainer();
  container.SetInstanceData(m_InstanceContainer.get());
  container.SetClientSystems(m_ClientSystems.get());

  auto game_logic = m_InstanceContainer->GetLogicContainer();
  game_logic.SetAllowModifyLowFrequencyData(true);
  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetEntitySync().ActivateEntities();

#ifdef NET_USE_RANDOM
  game_logic.GetInstanceData().m_Random = NetRandom((uint32_t)time(nullptr));
#endif

  int local_player_index = 0;
  for (int index = 0; index < kMaxPlayers; ++index)
  {
    if (m_AttachedPlayers[index])
    {
      m_InstanceContainer->GetGameController().ConstructPlayer(index, game_logic, "Player" + std::to_string(index + 1), index);
      auto & local_data = m_InstanceContainer->GetClientLocalData(local_player_index);
      local_data.m_PlayerIndex = index;

      m_ClientSystems->GetInputManager().BindGamepad(local_player_index, index);

      local_player_index++;
    }
  }

  m_InstanceContainer->GetGameController().FillWithBots(game_logic, GetRandomNumber());
  m_InstanceContainer->GetGameController().StartGame(game_logic);

  m_FrameClock.Start();

  //g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  //g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);
}

void GameModeLocalMultiplayer::Update()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & instance_data = *m_InstanceContainer.get();
  auto & game_data = instance_data.GetGlobalInstanceData();

  if (game_data.m_WiningTeam)
  {
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, std::move(m_InstanceContainer), std::move(m_ClientSystems), EndGamePlayAgainMode::kOfflineMultiplayer);
    return;
  }

  int num_local_players_alive = 0;
  for (auto player_index = 0; player_index < kMaxPlayers; player_index++)
  {
    if (m_AttachedPlayers[player_index])
    {
      num_local_players_alive++;
    }
  }

  if (num_local_players_alive == 0)
  {
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, std::move(m_InstanceContainer), std::move(m_ClientSystems), EndGamePlayAgainMode::kOfflineMultiplayer);
    return;
  }

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();
  auto visual_effects = engine_state.GetVisualEffectManager();
  auto map_system = engine_state.GetMapSystem();

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  for (int index = 0; index < 3 && m_FrameClock.ShouldSkipFrameUpdate() == false; ++index)
  {
    m_FrameClock.BeginFrame();
    container.GetWindow().Update();

    entity_system->BeginFrame();
    input_manager.Update();
    m_InstanceContainer->Update();

    map_system->UpdateAllMaps(container);

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
  }

  m_FrameClock.RemoveExtra();

  auto & camera = container.GetClientSystems()->GetCamera();
  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetPosition(), camera.GetGameResolution());

  visual_effects->Update(viewport_bounds);
  ui_manager.Update();

  if (ui_manager.WantsToQuit())
  {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
  }
}

void GameModeLocalMultiplayer::Render()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  render_state.SetScreenSize(container.GetWindow().GetSize());
  render_state.SetRenderSize(camera.GetGameResolution());
  render_state.SetFramePct((float)m_FrameClock.GetFramePercent());

  render_util.SetClearColor(kDefaultClearColor);
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

bool GameModeLocalMultiplayer::IsLoaded()
{
  if (m_InstanceContainer->IsLoaded() == false)
  {
    return false;
  }

  return GameMode::IsLoaded();
}

void GameModeLocalMultiplayer::SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index)
{
  auto game = m_InstanceContainer->GetLogicContainer();
  m_InstanceContainer->GetGameController().HandleClientEvent(0, game, class_id, event_ptr);
}
