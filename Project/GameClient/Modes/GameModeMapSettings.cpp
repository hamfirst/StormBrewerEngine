#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"
#include "GameClient/Modes/GameModeOfflineStaging.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/Asset/Asset.h"
#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/MapSettings.ui", g_MapSettingsSelectUI);

GameModeMapSettings::GameModeMapSettings(GameContainer &game, GameModeMapSettingsNextScreen next_screen) :
    GameModeOnlineBase(game),
    m_NextScreen(next_screen),
    m_ScriptInterface(nullptr)
{

}

void GameModeMapSettings::Initialize()
{

}

void GameModeMapSettings::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModeMapSettings::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();
  m_ScriptInterface = &game_interface;

  auto & level_list = container.GetLevelList();

  ui->Call("ResetMapOptions");
  for(auto & level_info : level_list.GetLevelListAsset()->GetData()->m_Levels)
  {
    ui->Call("PushMapOption", { ScriptValue(level_info.m_Name) });
  }

#ifdef NET_USE_PLAYER_LIMIT
  game_interface.AddVariable("player_count_enabled", true);
#else
  game_interface.AddVariable("player_count_enabled", false);
#endif

#ifdef NET_USE_SCORE_LIMIT
  game_interface.AddVariable("score_limit_enabled", true);
#else
  game_interface.AddVariable("score_limit_enabled", false);
#endif

#ifdef NET_USE_TIME_LIMIT
  game_interface.AddVariable("time_limit_enabled", true);
#else
  game_interface.AddVariable("time_limit_enabled", false);
#endif

  BIND_SCRIPT_INTERFACE(game_interface, this, Submit);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  BIND_SCRIPT_INTERFACE(game_interface, this, LoadMap);
  BIND_SCRIPT_INTERFACE(game_interface, this, SetMapOptions);

  LoadMap(0);
  m_MapImageBinding.Emplace(container.GetUIManager()->CreateTextureBinding("map_image",
          Delegate<NotNullPtr<const Texture>>([this]() -> NullOptPtr<const Texture>
                  {
                    auto asset = m_MapImage.Resolve();
                    if(asset && asset->IsLoaded())
                    {
                      return &asset->GetTexture();
                    }

                    return nullptr;
                  })));

  container.GetUIManager()->PushUIDef(g_MapSettingsSelectUI);
}

void GameModeMapSettings::Update()
{
  if(m_NextScreen == GameModeMapSettingsNextScreen::kPrivateGame)
  {
    if(HandleDisconnect())
    {
      return;
    }
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeMapSettings::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

void GameModeMapSettings::Back()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeMainMenu>();
}

void GameModeMapSettings::Submit()
{
  auto & container = GetContainer();

  switch(m_NextScreen)
  {
    case GameModeMapSettingsNextScreen::kOfflineStaging:
      container.SwitchMode<GameModeOfflineStaging>(m_Settings);
      break;
    case GameModeMapSettingsNextScreen::kPrivateGame:
      break;
  }
}

void GameModeMapSettings::LoadMap(int map_index)
{
  m_Settings.m_StageIndex = (uint8_t)map_index;

  auto & container = GetContainer();
  auto & level_list = container.GetLevelList();

  auto & level_info = level_list.GetLevelListAsset()->GetData()->m_Levels[map_index];

  m_MapImage = TextureAsset::Load(level_info.m_MapImage.c_str(), false);

  m_ScriptInterface->AddVariable("player_limit_increment", ScriptValue(kMaxTeams));
  m_ScriptInterface->AddVariable("map_description", ScriptValue(level_info.m_Description));

#ifdef NET_USE_PLAYER_LIMIT
  m_ScriptInterface->AddVariable("player_limit_increment", ScriptValue(kMaxTeams));
  m_ScriptInterface->AddVariable("player_limit_min", ScriptValue(kMaxTeams));
  m_ScriptInterface->AddVariable("player_limit_max", ScriptValue(level_info.m_MaxPlayers));
  m_ScriptInterface->AddVariable("player_limit_default", ScriptValue(level_info.m_MaxPlayersDefault));
#else
  m_ScriptInterface->AddVariable("player_limit_increment", 1);
  m_ScriptInterface->AddVariable("player_limit_min", 1);
  m_ScriptInterface->AddVariable("player_limit_max", 1);
  m_ScriptInterface->AddVariable("player_limit_default", 1);
#endif

#ifdef NET_USE_SCORE_LIMIT
  m_ScriptInterface->AddVariable("score_limit_increment", ScriptValue(1));
  m_ScriptInterface->AddVariable("score_limit_min", ScriptValue(1));
  m_ScriptInterface->AddVariable("score_limit_max", ScriptValue(level_info.m_MaxScore));
  m_ScriptInterface->AddVariable("score_limit_default", ScriptValue(level_info.m_MaxScoreDefault));
#else
  m_ScriptInterface->AddVariable("score_limit_increment", ScriptValue(1));
  m_ScriptInterface->AddVariable("score_limit_min", ScriptValue(1));
  m_ScriptInterface->AddVariable("score_limit_max", ScriptValue(1));
  m_ScriptInterface->AddVariable("score_limit_default", ScriptValue(1));
#endif

#ifdef NET_USE_SCORE_LIMIT
  m_ScriptInterface->AddVariable("time_limit_increment", ScriptValue(1));
  m_ScriptInterface->AddVariable("time_limit_min", ScriptValue(1));
  m_ScriptInterface->AddVariable("time_limit_max", ScriptValue(level_info.m_MaxTime));
  m_ScriptInterface->AddVariable("time_limit_default", ScriptValue(level_info.m_MaxPlayersDefault));
#else
  m_ScriptInterface->AddVariable("time_limit_increment", ScriptValue(1));
  m_ScriptInterface->AddVariable("time_limit_min", ScriptValue(1));
  m_ScriptInterface->AddVariable("time_limit_max", ScriptValue(1));
  m_ScriptInterface->AddVariable("time_limit_default", ScriptValue(1));
#endif
}

void GameModeMapSettings::SetMapOptions(int player_count, int score_limit, int time_limit)
{
#ifdef NET_USE_PLAYER_LIMIT
  m_Settings.m_PlayerCount = (uint8_t)player_count;
#endif

#ifdef NET_USE_SCORE_LIMIT
  m_Settings.m_ScoreLimit = (uint16_t)score_limit;
#endif

#ifdef NET_USE_SCORE_LIMIT
  m_Settings.m_TimeLimit = (uint16_t)time_limit;
#endif
}
