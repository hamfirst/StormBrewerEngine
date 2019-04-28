
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeOnlineGameplay.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/Modes/GameModeOnlineStaging.h"

#include "GameShared/GameLevelListAsset.refl.meta.h"

#include "LobbyShared/LobbyGameFuncs.h"


#include "Engine/UI/UIManager.h"

GameModeOnlineStaging::GameModeOnlineStaging(GameContainer & game) :
        GameModeStagingBase(game)
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    auto & lobby_client = container.GetLobbyClient();

    auto & game_info = lobby_client.GetGameInfo();
    if(game_info)
    {
      UpdateGameInfo();
    }

    lobby_client.SetGameDataUpdateCallback([&]
    {
      UpdateGameInfo();
    });

    lobby_client.SetGameChatCallback([&](const std::string_view & user, const std::string_view & name, int icon, int title)
    {
      auto & container = GetContainer();
      container.GetUIManager()->Call("AddChatMessage", { std::string(user), std::string(name) });
    });
  }
}

GameModeOnlineStaging::~GameModeOnlineStaging()
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    auto & lobby_client = container.GetLobbyClient();
    lobby_client.SetGameDataUpdateCallback({});
    lobby_client.SetGameChatCallback({});
  }
}

bool GameModeOnlineStaging::AllowLoadout()
{
#ifdef NET_USE_LOADOUT
  return true;
#else
  return false;
#endif
}

bool GameModeOnlineStaging::AllowReady()
{
#ifdef NET_USE_READY
  return true;
#elif defined(NET_USE_READY_PRIVATE_GAME)
  return m_GameInfo.m_Type == LobbyGameType::kPrivate;
#else
  return false;
#endif
}


bool GameModeOnlineStaging::AllowMapChange()
{
  return m_GameInfo.m_Type == LobbyGameType::kPrivate && m_IsGameLeader;
}

bool GameModeOnlineStaging::AllowGameTimer()
{
  return true;
}

std::string GameModeOnlineStaging::GetGameName()
{
  switch((LobbyGameType)m_GameInfo.m_Type)
  {
    case LobbyGameType::kCompetitive:
      return "Competitive Game";
    case LobbyGameType::kCasual:
      return "Casual Game";
    case LobbyGameType::kPrivate:
      return "Private Game";
  }

  return "";
}

std::string GameModeOnlineStaging::GetGameCode()
{
  if(m_GameInfo.m_JoinCode == 0U)
  {
    return "";
  }

  return "";
}

std::string GameModeOnlineStaging::GetGameTimer()
{
  if(m_GameInfo.m_State == LobbyGameState::kCountdown ||
    (m_GameInfo.m_Type == LobbyGameType::kCasual && m_GameInfo.m_State == LobbyGameState::kWaiting))
  {
    return std::to_string((int)m_GameInfo.m_Countdown);
  }

  return "";
}

int GameModeOnlineStaging::GetTeamCount()
{
  auto & map_props = GetContainer().GetLevelList().GetPreloadedMapProperties(m_GameInfo.m_Settings->m_StageIndex);
  return GetMaxTeams(map_props, m_GameInfo.m_Settings.Value());
}

int GameModeOnlineStaging::GetPlayerCount(int team_index)
{
#ifdef NET_FILL_WITH_BOTS
  return m_GameInfo.m_TeamSizes->m_MaxTeamSizes[team_index];
#else
  int team_count = 0;
  for(auto elem : m_GameInfo.m_Users)
  {
    if(elem.second.m_Team == team_index)
    {
      team_count++;
    }
  }

  return team_count;
#endif
}

int GameModeOnlineStaging::GetPlayerMaxCount(int team_index)
{
  return m_GameInfo.m_TeamSizes->m_MaxTeamSizes[team_index];
}

int GameModeOnlineStaging::GetPlayerId(int team, int player_index)
{
  return (team << 16) | player_index;
}

std::string GameModeOnlineStaging::GetPlayerName(int player_id)
{
  auto member = FindMember(player_id);
  return member ? member->m_Name.c_str() : "Bot";
}

int GameModeOnlineStaging::GetPlayerState(int player_id)
{
  auto member = FindMember(player_id);

  int state = 0;
  if(m_GameInfo.m_Type == LobbyGameType::kPrivate)
  {
    if(member && member->m_UserKey == m_GameInfo.m_GameLeader)
    {
      state = 1;
    }
  }

  return state;
}

bool GameModeOnlineStaging::GetPlayerReady(int player_id)
{
#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  auto member = FindMember(player_id);
  return member ? (bool)member->m_Ready : true;
#else
  return false;
#endif
}

std::unordered_map<std::string, std::string> GameModeOnlineStaging::GetPlayerActions(int player_id)
{
  return {};
}

void GameModeOnlineStaging::Ready(bool ready)
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    container.GetLobbyClient().SendGameReady(ready);
  }
}

void GameModeOnlineStaging::SendChat(const std::string & chat)
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    container.GetLobbyClient().SendGameChat(chat);
  }
}

bool GameModeOnlineStaging::TransitionToNextState()
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    auto & lobby_client = GetContainer().GetLobbyClient();
    auto & game_info = lobby_client.GetGameLaunchInfo();

    if(game_info)
    {
      if(container.HasClient() == false)
      {
        GameNetworkClientInitSettings settings;
        settings.m_RemoteHost = game_info->m_ServerIp.c_str();
        settings.m_RemotePort = game_info->m_ServerPort;
        settings.m_GameId = game_info->m_GameId;
        settings.m_UserId = game_info->m_UserId;
        settings.m_JoinKey = game_info->m_Token;

        container.StartNetworkClient(settings);
      }

      container.SwitchMode<GameModeConnectingGame>();
      return true;
    }
  }

  return false;
}

void GameModeOnlineStaging::Quit()
{
  auto & container = GetContainer();
  if(container.HasLobbyClient())
  {
    auto & lobby_client = GetContainer().GetLobbyClient();
    lobby_client.SendLeaveGame();

    GetContainer().StopNetworkClient();

#ifndef NET_FORCE_CASUAL_GAMES
    if(container.HasLobbyClient())
    {
      GetContainer().SwitchMode<GameModePlayOnline>();
      return;
    }
#endif

    GetContainer().StopLobbyClient();
    GetContainer().SwitchMode<GameModeMainMenu>();
  }
}

void GameModeOnlineStaging::UpdateGameInfo()
{
  auto & lobby_client = GetContainer().GetLobbyClient();
  auto & game_info = lobby_client.GetGameInfo().Value();
  m_GameInfo = game_info;

  auto & user_info = lobby_client.GetUserLocalData().Value();
  m_IsGameLeader = game_info.m_GameLeader == user_info.m_UserKey;
}

NullOptPtr<GameMember> GameModeOnlineStaging::FindMember(int player_id)
{
  auto team = player_id >> 16;
  auto player_index = player_id & 0xFFFF;

  for(auto elem : m_GameInfo.m_Users)
  {
    if(elem.second.m_Team == team)
    {
      if(player_index == 0)
      {
        return &elem.second;
      }

      player_index--;
    }
  }

  return nullptr;
}
