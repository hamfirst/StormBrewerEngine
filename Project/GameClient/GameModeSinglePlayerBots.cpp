#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeSinglePlayerBots.h"
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



#include <ctime>


GameModeSinglePlayerBots::GameModeSinglePlayerBots(GameContainer & game, const GameInitSettings game_settings, bool show_tutorial) :
  GameMode(game)
{
  auto & container = GetContainer();
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(container, *this, 1, true);
  m_InstanceContainer->Load(game_settings);

  m_ShowTutorial = show_tutorial;
}

GameModeSinglePlayerBots::~GameModeSinglePlayerBots()
{
  m_ClientSystems.reset();
}

void GameModeSinglePlayerBots::Initialize()
{

}

void GameModeSinglePlayerBots::OnAssetsLoaded()
{
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  auto & container = GetContainer();
  container.SetInstanceData(m_InstanceContainer.get());
  container.SetClientSystems(m_ClientSystems.get());

  auto game_logic = m_InstanceContainer->GetLogicContainer();
  game_logic.SetAllowModifyLowFrequencyData(true);

  auto & render_state = container.GetRenderState();
  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

#ifdef NET_USE_RANDOM
  game_logic.GetInstanceData().m_Random = NetRandom((uint32_t)time(nullptr));
#endif

  m_InstanceContainer->GetGameController().ConstructPlayer(0, game_logic, "Player", 0);
  //m_InstanceContainer->GetGameController().FillWithBots(game_logic, GetRandomNumber());
  m_InstanceContainer->GetGameController().StartGame(game_logic);
  m_InstanceContainer->GetClientLocalData(0).m_PlayerIndex = 0;

  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetEntitySync().ActivateEntities();

  m_FrameClock.Start();


  if (m_ShowTutorial)
  {
    m_ClientSystems->GetUIManager().ShowTutorial();
  }
  else
  {
    //m_Sequencer.Push(0.5f, [this](float v) { m_Fader->GetData().m_ColorA = 1.0f - v; if (v == 1.0f) m_Fader->SetDisabled(); });
  }

  //g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  //g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);
}

void GameModeSinglePlayerBots::Update()
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
    container.SwitchMode(GameModeDef<GameModeEndGame>{}, 
      std::move(m_InstanceContainer), std::move(m_ClientSystems), EndGamePlayAgainMode::kOfflineSingleplayer);
    return;
  }

  if (m_ShowTutorial && m_ClientSystems->GetUIManager().IsPopupOpen() == false)
  {
    m_ShowTutorial = false;
    //m_Sequencer.Push(0.5f, [this](float v) { m_Fader->GetData().m_ColorA = 1.0f - v; if (v == 1.0f) m_Fader->SetDisabled(); });
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
    m_Sequencer.Update();

    container.GetWindow().Update();

    if (m_ClientSystems->GetUIManager().IsPopupOpen() == false)
    {
      PROFILE_SCOPE("Server update");

      entity_system->BeginFrame();

      input_manager.Update();
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

      m_InstanceContainer->SyncEntities();
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

void GameModeSinglePlayerBots::Render()
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

  auto camera_res = camera.GetGameResolution();

  render_state.SetScreenSize(container.GetWindow().GetSize());
  render_state.SetRenderSize(camera.GetGameResolution());
  render_state.SetFramePct((float)m_FrameClock.GetFramePercent());

  render_util.SetDefaultClearColor();
  render_util.Clear();

  auto & engine_state = container.GetEngineState();
  auto entity_system = engine_state.GetEntitySystem();
  auto map_system = engine_state.GetMapSystem();

  auto screen_resolution = container.GetWindow().GetSize();


  {
    PROFILE_SCOPE("Camera Update");
    camera.SetScreenResolution(screen_resolution);
    camera.Update();
  }

  auto viewport_bounds = Box::FromFrameCenterAndSize(camera.GetPosition(), camera.GetGameResolution());

  {
    PROFILE_SCOPE("Camera Draw");
    camera.Draw(container, &engine_state, render_state, render_util);
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

bool GameModeSinglePlayerBots::IsLoaded()
{
  if(m_InstanceContainer->IsLoaded() == false)
  {
    return false;
  }

  return GameMode::IsLoaded();
}

void GameModeSinglePlayerBots::SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index)
{
  auto game = m_InstanceContainer->GetLogicContainer();
  m_InstanceContainer->GetGameController().HandleClientEvent(0, game, class_id, event_ptr);
}

