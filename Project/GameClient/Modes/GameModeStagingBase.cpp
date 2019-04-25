
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeNameSelect.h"
#include "GameClient/Modes/GameModeStagingBase.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"
#include "GameClient/Modes/GameModeTutorial.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/GameContainer.h"
#include "GameClient/Components/PlayerComponent.refl.h"

#include "Game/GameNetworkData.refl.h"
#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "Engine/Engine.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/Staging.ui", g_StagingUI);

GameModeStagingBase::GameModeStagingBase(GameContainer & game) :
  GameMode(game)
{

}

void GameModeStagingBase::OnAssetsLoaded()
{
  m_Settings = GetAppliedOptions();

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

  game_interface.AddVariable("game_name", GetGameName());
  game_interface.AddVariable("game_code", GetGameCode());

#ifdef NET_ALLOW_OBSERVERS
  game_interface.AddVariable("allow_observers", true);
#else
  game_interface.AddVariable("allow_observers", false);
#endif

  game_interface.AddVariable("allow_chat", AllowChat());
  game_interface.AddVariable("allow_reader", AllowReady());
  game_interface.AddVariable("allow_playerlist", AllowPlayerList());
  game_interface.AddVariable("allow_loadout", AllowLoadout());
  game_interface.AddVariable("allow_gametimer", AllowGameTimer());
  game_interface.AddVariable("allow_mapsettings", AllowMapChange());

  BIND_SCRIPT_INTERFACE(game_interface, this, GetGameName);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetGameCode);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetGameTimer);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetTeamCount);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerCount);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerMaxCount);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerId);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetTeamName);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetTeamColor);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetTeamColorDark);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerName);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerState);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerReady);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetPlayerActions);
  BIND_SCRIPT_INTERFACE(game_interface, this, Ready);
  BIND_SCRIPT_INTERFACE(game_interface, this, SendChat);
  BIND_SCRIPT_INTERFACE(game_interface, this, DefaultAction);
  BIND_SCRIPT_INTERFACE(game_interface, this, GetCurrentOptions);
  BIND_SCRIPT_INTERFACE(game_interface, this, LoadMap);
  BIND_SCRIPT_INTERFACE(game_interface, this, SetMapOptions);
  BIND_SCRIPT_INTERFACE(game_interface, this, CommitMapChanges);
  BIND_SCRIPT_INTERFACE(game_interface, this, CancelMapChanges);

  container.GetUIManager()->PushUIDef(g_StagingUI);
}

void GameModeStagingBase::Update()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeStagingBase::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

int GameModeStagingBase::GetPlayerId(int team, int player_index)
{
  return team * kMaxPlayers + player_index;
}

std::string GameModeStagingBase::GetTeamName(int team, int player_index)
{
  switch(team)
  {
    case -1:
      return "Observers";
    case 0:
      return "Red";
    case 1:
      return "Blue";
    case 2:
      return "Green";
    case 3:
      return "Black";
    default:
      ASSERT(false, "Invalid team");
      return "Unknown";
  }
}

std::tuple<float, float, float> GameModeStagingBase::GetTeamColor(int team)
{
  auto color = PlayerComponent::GetTeamColor(team);
  return std::make_tuple(color.r, color.g, color.b);
}

std::tuple<float, float, float> GameModeStagingBase::GetTeamColorDark(int team)
{
  auto color = PlayerComponent::GetTeamDarkColor(team);
  return std::make_tuple(color.r, color.g, color.b);
}

std::string GameModeStagingBase::GetPlayerName(int player_id)
{
  return "Player";
}

int GameModeStagingBase::GetPlayerState(int player_id)
{
  return 0;
}

bool GameModeStagingBase::GetPlayerReady(int player_id)
{
  return false;
}

std::unordered_map<std::string, std::string> GameModeStagingBase::GetPlayerActions(int player_id)
{
  std::unordered_map<std::string, std::string> actions;
  actions.emplace(std::make_pair("Default Action", "DefaultAction"));
  return actions;
}

std::tuple<int, int, int, int> GameModeStagingBase::GetCurrentOptions()
{
#ifdef NET_USE_PLAYER_LIMIT
  auto player_count = m_Settings.m_PlayerCount;
#else
  auto player_count = 0;
#endif

#ifdef NET_USE_SCORE_LIMIT
  auto score_limit = m_Settings.m_ScoreLimit;
#else
  auto score_limit = 0;
#endif

#ifdef NET_USE_TIME_LIMIT
  auto time_limit = m_Settings.m_TimeLimit;
#else
  auto time_limit = 0;
#endif

  return std::make_tuple(m_Settings.m_StageIndex, player_count, score_limit, time_limit);
}

void GameModeStagingBase::LoadMap(int map_index)
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

#ifdef NET_USE_TIME_LIMIT
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

void GameModeStagingBase::SetMapOptions(int player_count, int score_limit, int time_limit)
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

void GameModeStagingBase::CommitMapChanges()
{
  ChangeMapOptions(m_Settings);
}

void GameModeStagingBase::CancelMapChanges()
{
  m_Settings = GetAppliedOptions();
}

void GameModeStagingBase::Quit()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}

