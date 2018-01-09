#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
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
#include "Engine/Profiler/Profiler.h"
#include "Engine/Audio/MusicManager.h"


GameModeOnlineGameplay::GameModeOnlineGameplay(GameContainer & game) :
  GameMode(game)
{

}

GameModeOnlineGameplay::~GameModeOnlineGameplay()
{
  m_ClientSystems.reset();
}

void GameModeOnlineGameplay::Initialize()
{
  auto & container = GetContainer();
  container.SetInstanceData(container.GetClient().GetClientInstanceData());
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  container.SetClientSystems(m_ClientSystems.get());
  container.SetInstanceData(container.GetClient().GetClientInstanceData());
  container.GetClient().FinalizeLevelLoad();
}

void GameModeOnlineGameplay::OnAssetsLoaded()
{
  m_FrameClock.Start();

  g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);
}

void GameModeOnlineGameplay::Update()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  PROFILE_SCOPE("Server update");

  auto & container = GetContainer();
  auto & client = container.GetClient();

  auto instance_data = client.GetClientInstanceData();
  auto & game_data = client.GetClientInstanceData()->GetGlobalInstanceData();
  auto & local_data = client.GetClientInstanceData()->GetClientLocalData(0);

  if (client.GetConnectionState() != ClientConnectionState::kConnected)
  {
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    return;
  }

  if (game_data.m_WiningTeam)
  {
    auto instance = container.GetClient().ConvertToOffline();
    container.StopNetworkClient();
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, std::move(instance), std::move(m_ClientSystems), EndGamePlayAgainMode::kOnlineGameplay);
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
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
  }
}

void GameModeOnlineGameplay::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
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

  //RenderProfilerData(render_state);

  m_FPSClock.Update();
  std::string fps_data = std::to_string(m_FPSClock.GetFrameCount());
  g_TextManager.SetTextPos(Vector2(40, 40) - render_state.GetRenderSize() / 2);
  g_TextManager.SetPrimaryColor();
  g_TextManager.SetShadowColor();
  g_TextManager.SetTextMode(TextRenderMode::kOutlined);
  g_TextManager.ClearTextBounds();
  g_TextManager.RenderText(fps_data.data(), -1, 1, render_state);

}

