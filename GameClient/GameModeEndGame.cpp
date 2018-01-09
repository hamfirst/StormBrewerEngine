#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeEndGame.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameContainer.h"

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

GameModeEndGame::GameModeEndGame(GameContainer & game, std::unique_ptr<GameClientInstanceContainer> && instance_container,
                                                       std::unique_ptr<GameClientSystems> && client_systems, EndGamePlayAgainMode mode) :
  GameMode(game),
  m_InstanceContainer(std::move(instance_container)),
  m_ClientSystems(std::move(client_systems)),
  m_Mode(mode),
  m_UIManager(game.GetWindow())
{

}

GameModeEndGame::~GameModeEndGame()
{

}

void GameModeEndGame::Initialize()
{
  m_Victory = false;

  auto & game_state = m_InstanceContainer->GetGlobalInstanceData();

  auto num_local_players = m_InstanceContainer->GetNumLocalData();
  for (std::size_t client_index = 0; client_index < num_local_players; ++client_index)
  {
    auto & local_data = m_InstanceContainer->GetClientLocalData(client_index);
    auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

    if (game_state.m_WiningTeam && game_state.m_WiningTeam.Value() == local_player.m_Team)
    {
      m_Victory = true;
    }
  }
}

void GameModeEndGame::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  m_Fader = m_UIManager.AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 0));
  fader_data.SetBounds(Box::FromPoints(-half_res, half_res));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_PlayAgain.Emplace(m_UIManager, "playagain", nullptr, Box::FromFrameCenterAndSize(Vector2(0, 0), Vector2(150, 50)), 
    "Play Again", &container.GetClientGlobalResources().UISoundEffects);
  m_PlayAgain->SetOnClickCallback([this] { PlayAgain(); });

  m_Quit.Emplace(m_UIManager, "playagain", nullptr, Box::FromFrameCenterAndSize(Vector2(0, -50), Vector2(150, 25)),
    "Quit To Main Menu", &container.GetClientGlobalResources().UISoundEffects);
  m_Quit->SetOnClickCallback([this] { Quit(); });

  m_Result = m_UIManager.AllocateText("result");
  auto & result_data = m_Result->GetData();
  result_data.m_Centered = 1.0f;
  result_data.m_FontId = -1.0f;
  result_data.m_PositionX = 0;
  result_data.m_PositionY = 80;
  result_data.m_Text = m_Victory ? "Victory" : "Defeat";
  result_data.m_TextMode = 2.0f;

  g_MusicManager.FadeOut(0.1f);
  if (m_Victory)
  {
    g_MusicManager.PlayClip(container.GetClientGlobalResources().VictoryMusic, 0.5f, true);
  }
  else
  {
    g_MusicManager.PlayClip(container.GetClientGlobalResources().DefeatMusic, 0.5f, true);
  }

  m_Sequencer.Push(0.5f, [this](float val) { });
  m_Sequencer.Push(0.5f, [this](float val) {
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { m_Fader->SetInactive(); });

  m_FrameClock.Start();
}

void GameModeEndGame::Update()
{

  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);

  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();

  auto & engine_state = container.GetEngineState();
  auto comp_system = engine_state.GetComponentSystem();
  auto entity_system = engine_state.GetEntitySystem();
  auto visual_effects = engine_state.GetVisualEffectManager();
  auto map_system = engine_state.GetMapSystem();

  if (m_FrameClock.ShouldSkipFrameUpdate() == false && m_Fader->GetData().m_ColorA != 1.0f)
  {
    m_FrameClock.BeginFrame();
    container.GetWindow().Update();

    input_manager.Update();

    if (m_Sequencer.IsComplete() == false)
    {
      entity_system->BeginFrame();
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
  }

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

void GameModeEndGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  auto & ui_manager = container.GetClientSystems()->GetUIManager();
  auto & input_manager = container.GetClientSystems()->GetInputManager();
  auto & camera = container.GetClientSystems()->GetCamera();

  render_state.SetRenderSize(camera.GetGameResolution());

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

  m_UIManager.Render(render_state, render_util);
}

void GameModeEndGame::PlayAgain()
{
  m_Fader->SetActive();

  auto & container = GetContainer();

  switch (m_Mode)
  {
  case EndGamePlayAgainMode::kOnlineGameplay:
    container.StartNetworkClient();
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
    g_MusicManager.CutTo(GetContainer().GetClientGlobalResources().MainMenuMusic, 0.5f);
    break;
  case EndGamePlayAgainMode::kOfflineMultiplayer:
    container.SwitchMode(GameModeDef<GameModeOfflineStaging>{});
    break;
  case EndGamePlayAgainMode::kOfflineSingleplayer:
    container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, false);
    break;
  }
}

void GameModeEndGame::Quit()
{
  m_Fader->SetActive();

  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}