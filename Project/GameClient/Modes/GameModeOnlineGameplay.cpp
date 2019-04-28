#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeOnlineGameplay.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/Modes/GameModeEndGame.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Entity/EntitySystem.h"
#include "Engine/Component/ComponentSystem.h"
#include "Engine/Component/ComponentUpdateBucketList.h"
#include "Engine/Map/MapSystem.h"
#include "Engine/VisualEffect/VisualEffectManager.h"
#include "Engine/DrawList/DrawList.h"
#include "Engine/EngineState.h"
#include "Engine/Profiler/Profiler.h"
#include "Engine/Audio/MusicManager.h"


GameModeOnlineGameplay::GameModeOnlineGameplay(GameContainer & game) :
  GameMode(game)
{

}

GameModeOnlineGameplay::~GameModeOnlineGameplay()
{
  auto & container = GetContainer();
  container.ResetAllGameplaySystems();

  container.SetInstanceData(nullptr);
  container.SetClientSystems(nullptr);
  m_ClientSystems.reset();
}

void GameModeOnlineGameplay::Initialize()
{
  auto & container = GetContainer();
  container.SetInstanceData(container.GetGameClient().GetClientInstanceData());
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  container.SetClientSystems(m_ClientSystems.get());
  container.SetInstanceData(container.GetGameClient().GetClientInstanceData());
  container.GetGameClient().FinalizeLevelLoad();
}

void GameModeOnlineGameplay::OnAssetsLoaded()
{
  m_FrameClock.Start();

  //g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  //g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);
}

void GameModeOnlineGameplay::Update()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  PROFILE_SCOPE("Server update");

  auto & container = GetContainer();
  auto & client = container.GetGameClient();

  auto instance_data = client.GetClientInstanceData();
  auto & game_data = client.GetClientInstanceData()->GetGlobalInstanceData();
  auto & local_data = client.GetClientInstanceData()->GetClientLocalData(0);

  if (client.GetConnectionState() != ClientConnectionState::kConnected)
  {
    container.SwitchMode<GameModeConnectingGame>();
    return;
  }

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();
  auto visual_effects = engine_state.GetVisualEffectManager();
  auto map_system = engine_state.GetMapSystem();

  if (game_data.m_WiningTeam)
  {
    auto instance = container.GetGameClient().ConvertToOffline();
    container.StopNetworkClient();
    container.SwitchMode<GameModeEndGame>(std::move(instance), std::move(m_ClientSystems), EndGamePlayAgainMode::kOnlineGameplay);
    return;
  }

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  for (int index = 0; index < 3 && m_FrameClock.ShouldSkipFrameUpdate() == false; ++index)
  {
    m_FrameClock.BeginFrame();

    if (client.SkipUpdate())
    {
      continue;
    }

    container.GetWindow().Update();
    entity_system->BeginFrame();

    input_manager.Update();
    client.Update();

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
    container.StopNetworkClient();
    container.SwitchMode<GameModeMainMenu>();
    container.ResetAllGameplaySystems();
  }
}

void GameModeOnlineGameplay::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  {
    PROFILE_SCOPE("Render");
    if (AssetLoadingComplete() == false)
    {
      return;
    }

    render_state.SetRenderSize(camera.GetGameResolution());
    render_state.SetFramePct((float)m_FrameClock.GetFramePercent());

    render_state.SetDefaultClearColor();
    render_state.Clear();

    auto & engine_state = container.GetEngineState();
    auto entity_system = engine_state.GetEntitySystem();
    auto map_system = engine_state.GetMapSystem();

    auto screen_resolution = container.GetWindow().GetSize();

    camera.SetScreenResolution(screen_resolution);
    camera.Update();

    auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetPosition(), camera.GetGameResolution());

    camera.Draw(container, &engine_state, render_state);

    input_manager.Render();
    ui_manager.Render();
  }
}

