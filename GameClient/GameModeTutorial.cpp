
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeTutorial.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeSinglePlayerBots.h"

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

GameModeTutorial::GameModeTutorial(GameContainer & game, const GameInitSettings game_settings) :
  GameMode(game),
  m_Paused(false)
{
  auto & container = GetContainer();
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(container, 0, true, nullptr, nullptr);
  m_InstanceContainer->Load(game_settings);
}

GameModeTutorial::~GameModeTutorial()
{
  m_TutorialPopup.Clear();
  m_Fader.Clear();
  m_ClientSystems.reset();
}

void GameModeTutorial::Initialize()
{

}

void GameModeTutorial::OnAssetsLoaded()
{
  m_InstanceData = std::make_unique<GameClientInstanceData>(m_InstanceContainer->GetClientInstanceData(*this));
  m_ClientSystems = std::make_unique<GameClientSystems>(GetContainer());

  auto & container = GetContainer();
  container.SetInstanceData(m_InstanceData.get());
  container.SetClientSystems(m_ClientSystems.get());

  auto game_logic = m_InstanceContainer->GetLogicContainer(true);

#ifdef NET_USE_RANDOM
  game_logic.GetInstanceData().m_Random = NetRandom(1);
#endif

  m_InstanceContainer->GetGameController().FillWithBots(game_logic, 0);
  m_InstanceContainer->GetInstanceData().m_Players[0].m_AIPlayerInfo.Clear();

  m_InstanceContainer->GetGameController().StartGame(game_logic);

  m_InstanceContainer->GetInstanceData().m_Score[2] = 4;

  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetEntitySync().ActivateEntities();

  m_Fader = m_ClientSystems->GetUIManager().GetUIManager().AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 255));
  fader_data.SetBounds(Box::FromPoints(Vector2(0, 0), Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight)));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_FrameClock.Start();

  g_MusicManager.FadeTo(GetContainer().GetClientGlobalResources().GameplayLoop, 0.5f, 0.2f, 2.0f);
  g_MusicManager.PlayClip(GetContainer().GetClientGlobalResources().GameplayStart, 0.2f, true);

  m_ClientSystems->GetUIManager().DisablePopup();

  m_Sequencer.Push(1.0f, [this](float v )
  {
    m_Fader->GetData().m_ColorA = 1.0f - v;
  });

  m_Sequencer.Push(4.0, [this](float v) 
  {
    if (v == 1.0f)
    {

      Box box;
      box.m_Start = { 100, 100 };
      box.m_End = box.m_Start + Vector2{ 200, 130 };

      m_TutorialPopup.Emplace(m_ClientSystems->GetUIManager().GetUIManager(), "tutorial", nullptr, box, 
        "Tutorial message!", &GetContainer().GetClientGlobalResources().UISoundEffects);
      m_TutorialPopup->SetOnOkayCallback([this] { Resume(); m_TutorialPopup->Hide(); });

      Pause();
    }
  });

  m_Sequencer.Push(1.0f, [this](float v)
  {    
    m_Fader->GetData().m_ColorA = v;

    if (v == 1.0f)
    {
      Resume();
      m_Paused = true;

      auto & container = GetContainer();
      container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, true);
    }
  });
}

void GameModeTutorial::Update()
{
  if (AssetLoadingComplete() == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & instance_data = *m_InstanceData.get();
  auto & game_data = instance_data.GetGameState();

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();
  auto visual_effects = engine_state.GetVisualEffectManager();
  auto map_system = engine_state.GetMapSystem();

  if (m_FrameClock.ShouldSkipFrameUpdate() == false)
  {
    m_FrameClock.BeginFrame();
    m_Sequencer.Update(1.0f / 60.0f);

    if (m_Paused == false)
    {
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

  {
    PROFILE_SCOPE("VFX update");
    visual_effects->Update();
  }

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  {
    PROFILE_SCOPE("UI update");
    ui_manager.Update();
  }

  {
    PROFILE_SCOPE("Input update");
    input_manager.Update();
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
  auto & render_util = container.GetRenderUtil();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

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
}

bool GameModeTutorial::IsLoaded()
{
  if (m_InstanceContainer->IsLoaded() == false)
  {
    return false;
  }

  return GameMode::IsLoaded();
}

void GameModeTutorial::SendClientEvent(std::size_t class_id, const void * event_ptr)
{
  auto game = m_InstanceContainer->GetLogicContainer(true);
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
