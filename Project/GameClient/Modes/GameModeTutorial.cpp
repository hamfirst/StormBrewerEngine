#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeTutorial.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"

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

#include <ctime>

GameModeTutorial::GameModeTutorial(GameContainer & game) :
  GameMode(game),
  m_Paused(false)
{
  auto & container = GetContainer();
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(container, *this, 0, true);
  m_InstanceContainer->Load(GameInitSettings{});
}

GameModeTutorial::~GameModeTutorial()
{
  m_ClientSystems.reset();
}

void GameModeTutorial::Initialize()
{

}

void GameModeTutorial::OnAssetsLoaded()
{
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  auto & container = GetContainer();
  container.SetInstanceData(m_InstanceContainer.get());
  container.SetClientSystems(m_ClientSystems.get());

  auto game_logic = m_InstanceContainer->GetLogicContainer();

  auto & render_state = container.GetRenderState();
  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

#ifdef NET_USE_RANDOM
  game_logic.GetInstanceData().m_Random = NetRandom(1);
#endif

  game_logic.SetAllowModifyLowFrequencyData(true);
  m_InstanceContainer->GetGameController().FillWithBots(game_logic, 0);
  m_InstanceContainer->GetGlobalInstanceData().m_AIPlayerInfo.RemoveAt(0);

  m_InstanceContainer->GetGameController().StartGame(game_logic);
#ifdef NET_USE_SCORE
  m_InstanceContainer->GetGlobalInstanceData().m_Score[2] = 4;
#endif

  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetEntitySync().ActivateEntities();

  m_FrameClock.Start();

  //g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  //g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);

  m_ClientSystems->GetUIManager().DisablePopup();
}

void GameModeTutorial::Update()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & instance_data = *m_InstanceContainer.get();
  auto & game_data = instance_data.GetGlobalInstanceData();

  container.GetWindow().Update();

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
    m_Sequencer.Update(1.0f / 60.0f);

    if (m_Paused == false)
    {
      input_manager.Update();

      PROFILE_SCOPE("Server update");

      entity_system->BeginFrame();
      m_InstanceContainer->Update();

      map_system->UpdateAllMaps(container);

      {
        PROFILE_SCOPE("Component update");
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
    }
  }

  m_FrameClock.RemoveExtra();

  auto & camera = container.GetClientSystems()->GetCamera();
  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetPosition(), camera.GetGameResolution());

  {
    PROFILE_SCOPE("VFX update");
    visual_effects->Update(viewport_bounds);
  }

  {
    PROFILE_SCOPE("UI update");
    ui_manager.Update();
  }
}

void GameModeTutorial::Render()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  render_state.SetScreenSize(container.GetWindow().GetSize());
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

  {
    PROFILE_SCOPE("Camera Draw");
    camera.Draw(container, &engine_state, render_state);
  }

  {
    PROFILE_SCOPE("Input Draw");
    input_manager.Render();
  }

  {
    PROFILE_SCOPE("UI Draw");
    ui_manager.Render();
  }

  if (ui_manager.WantsToQuit())
  {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
  }
}

bool GameModeTutorial::IsLoaded()
{
  if (m_InstanceContainer->IsLoaded() == false)
  {
    return false;
  }

  return GameMode::IsLoaded();
}

void GameModeTutorial::SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index)
{
  auto game = m_InstanceContainer->GetLogicContainer();
  m_InstanceContainer->GetGameController().HandleClientEvent(0, game, class_id, event_ptr);
}

void GameModeTutorial::Pause()
{
  m_Paused = true;
  m_Sequencer.Pause();

  auto & container = GetContainer();
  container.GetEngineState().GetVisualEffectManager()->Pause();
}

void GameModeTutorial::Resume()
{
  m_Paused = false;
  m_Sequencer.Unpause();

  auto & container = GetContainer();
  container.GetEngineState().GetVisualEffectManager()->Unpause();
}
