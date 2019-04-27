

#include "HurricaneDDS/DDSResponderCall.h"

#include "Game.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"
#include "GameList.refl.meta.h"
#include "ServerManager.refl.meta.h"
#include "GameServerConnection.refl.meta.h"
#include "Matchmaker.refl.meta.h"
#include "LobbyLevelList.refl.h"

#include "LobbyShared/LobbyGameFuncs.h"



Game::Game(DDSNodeInterface node_interface) :
  m_Interface(node_interface),
  m_InitTime(node_interface.GetNetworkTime())
{

}

void Game::InitPrivateGame(const GameInitSettings & settings, std::string password)
{
  DDSLog::LogInfo("Initializing private game");
  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    return;
  }

  Init(settings);

  m_Interface.CallShared(&GameList::AssignJoinCode, m_Interface.GetLocalKey());
  
  m_GameInfo.m_Password = password;
  m_GameInfo.m_Type = LobbyGameType::kPrivate;
}

void Game::InitCasualGame(const GameInitSettings & settings, const GeneratedGame & game, int zone, const std::vector<int> & team_sizes)
{
  DDSLog::LogInfo("Initializing casual game");
  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    return;
  }

  m_TeamSizeOverrides = team_sizes;

  Init(settings);
  m_GameInfo.m_Type = LobbyGameType::kCasual;
  m_MatchmakerGameInfo = game;
  m_ZoneIndex = zone;
}

void Game::InitCompetitiveGame(const GameInitSettings & settings, const GeneratedGame & game, int zone, const std::vector<int> & team_sizes)
{
  DDSLog::LogInfo("Initializing competitive game");
  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    return;
  }

  m_TeamSizeOverrides = team_sizes;

  Init(settings);
  m_GameInfo.m_Type = LobbyGameType::kCompetitive;

  m_MatchmakerGameInfo = game;
  m_ZoneIndex = zone;
}

void Game::Init(const GameInitSettings & settings)
{
  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    return;
  }


  auto & level_info = g_LobbyLevelList.GetLevelInfo(settings.m_StageIndex);
  auto & level_name = g_LobbyLevelList.GetLevelName(settings.m_StageIndex);

  m_GameInfo.m_Settings = settings;
  m_GameInfo.m_State = LobbyGameState::kWaiting;
  m_GameCreateTime = m_Interface.GetNetworkTime();

  UpdateTeamSizes();

  auto max_players = GetMaxPlayers(level_info, m_GameInfo.m_Settings.Value());

  m_Interface.CallShared(&GameList::AddGame, m_Interface.GetLocalKey(), 0, max_players,
                         level_name, m_GameInfo.m_JoinCode, !m_GameInfo.m_Password.emtpy(), false);

  for(auto & action : m_PendingActions)
  {
    if(action.m_Join)
    {
      auto responder = DDSResponder{m_Interface, action.m_ResponderData};
      RequestAddUser(responder, action.m_JoinInfo);
    }
    else
    {
      RequestRemoveUser(action.m_JoinInfo.m_UserKey);
    }
  }

  m_PendingActions.clear();
}

void Game::Update()
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    static const int kNoInitDestroyTime = 5;
    if(m_Interface.GetNetworkTime() - m_InitTime >= kNoInitDestroyTime)
    {
      Cleanup();
    }

    return;
  }

  if(m_GameInfo.m_Type == LobbyGameType::kCompetitive)
  {
    if(m_GameInfo.m_State == LobbyGameState::kCountdown && !AllGeneratedUsersConnected())
    {
      m_GameInfo.m_State = LobbyGameState::kWaiting;
    }

    static const int kCompetitiveWaitTime = 15;
    if(m_GameInfo.m_State == LobbyGameState::kWaiting)
    {
      if(m_Interface.GetNetworkTime() - m_GameCreateTime > kCompetitiveWaitTime)
      {
        AbandonGame();
        Cleanup();
        return;
      }

      if(AllGeneratedUsersConnected())
      {
        BeginCountdown();
      }
    }
  }

  if(m_GameInfo.m_Type == LobbyGameType::kCasual)
  {
    if(m_GameInfo.m_State == LobbyGameState::kWaiting)
    {
      static const int kCasualGameAutoStartTime = 90;

      m_GameInfo.m_Countdown = kCasualGameAutoStartTime - (m_Interface.GetNetworkTime() - m_GameCreateTime);
      if(m_GameInfo.m_Countdown <= 10)
      {
        BeginCountdown();
      }
      else
      {
        auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);

        if(IsGameFullEnoughToStart(GetTeamCounts(), GetMaxTeamCounts(), level_info, m_GameInfo.m_Settings.Value()))
        {
          bool all_ready = true;

#ifdef NET_USE_READY
          all_ready = AllPlayersReady();
#endif

          if(all_ready)
          {
            BeginCountdown();
          }
        }
      }
    }
  }

  if(m_GameInfo.m_Type == LobbyGameType::kPrivate)
  {
#ifdef NET_USE_READY_PRIVATE_GAME
    if(m_GameInfo.m_State == LobbyGameState::kWaiting && AllPlayersReady())
    {
      BeginCountdown();
    }
#endif
  }

  if(m_GameInfo.m_State == LobbyGameState::kCountdown)
  {
    m_GameInfo.m_Countdown = m_GameInfo.m_Countdown - 1;
    if(m_GameInfo.m_Countdown <= 0)
    {
      StartGame();
    }
  }
  else if(m_GameInfo.m_State == LobbyGameState::kAssigningServer)
  {
    if(m_AssignedServer != 0)
    {
      m_GameInfo.m_State = LobbyGameState::kStarted;

      GameServerCreateGame msg;
      msg.m_GameId = m_Interface.GetLocalKey();
      msg.m_Settings = m_GameInfo.m_Settings.Value();
      msg.m_TeamInfo = m_GameInfo.m_TeamSizes.Value();

      m_Interface.Call(&GameServerConnection::CreateGame, m_AssignedServer, msg);

      for (auto & user : m_UserPrivateInfo)
      {
        LaunchGameForUser(user.first, user.second);
      }
    }
  }
  else if(m_GameInfo.m_State == LobbyGameState::kPostGame)
  {
    static const int kPostGameDuration = 45;
    if(m_Interface.GetNetworkTime() - m_GameEndTime > kPostGameDuration)
    {
      if(m_GameInfo.m_Type == LobbyGameType::kCompetitive)
      {
        Cleanup();
      }
      else
      {
        Reset();
      }
    }
  }
}

void Game::Cleanup()
{
  for(auto & action : m_PendingActions)
  {
    if(action.m_Join)
    {
      auto responder = DDSResponder{m_Interface, action.m_ResponderData};
      DDSResponderCall(responder, m_Interface.GetLocalKey(), action.m_JoinInfo.m_EndpointId, m_GameRandomId, false);
    }
  }

  for(auto user : m_GameInfo.m_Users)
  {
    m_Interface.Call(&User::NotifyLeftGame, user.second.m_UserKey, m_Interface.GetLocalKey(), m_GameRandomId, false);
  }

  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    m_Interface.CallShared(&GameList::RemoveGame, m_Interface.GetLocalKey());
  }

  if(m_GameInfo.m_Type == LobbyGameType::kCompetitive)
  {
    for(int team = 0; team < kMaxTeams; ++team)
    {
      for(auto & user : m_MatchmakerGameInfo.m_Users[team])
      {
        m_Interface.Call(&User::NotifyReconnectGameEnded, user.m_UserId, m_Interface.GetLocalKey(), m_GameRandomId);
      }
    }
  }

  if(m_AssignedServer != 0)
  {
    GameServerDestroyGame msg;
    msg.m_GameId = m_Interface.GetLocalKey();
    m_Interface.Call(&GameServerConnection::DestroyGame, m_AssignedServer, msg);

    m_Interface.CallShared(&ServerManager::HandleGameEnded, m_AssignedServer);
  }

  m_Interface.DestroySelf();
}

void Game::Reset()
{
  DDSLog::LogInfo("Resetting game");
  if(m_AssignedServer != 0)
  {
    GameServerDestroyGame msg;
    msg.m_GameId = m_Interface.GetLocalKey();
    m_Interface.Call(&GameServerConnection::DestroyGame, m_AssignedServer, msg);

    m_Interface.CallShared(&ServerManager::HandleGameEnded, m_AssignedServer);

    m_AssignedServer = 0;
    m_ServerIp = "";
    m_ServerPort = 0;
  }

  for(auto & user_info : m_UserPrivateInfo)
  {
    user_info.second.m_Token = 0;
    user_info.second.m_TokenAssigned = 0;
  }

  for(auto user : m_GameInfo.m_Users)
  {
#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
    user.second.m_Ready = false;
#endif
  }

  m_GameInfo.m_Countdown = 0;
  m_GameInfo.m_State = LobbyGameState::kWaiting;

  m_GameCreateTime = 0;
  m_GameEndTime = 0;
}

void Game::RequestAddUser(DDSResponder & responder, const GameUserJoinInfo & join_info)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    DDSLog::LogInfo("Queueing game add user");
    GameModifyAction action;
    action.m_Join = true;
    action.m_JoinInfo = join_info;
    action.m_ResponderData = responder.m_Data;
    m_PendingActions.emplace_back(std::move(action));
    return;
  }

  DDSLog::LogInfo("Adding user to game");

  bool success = AddUser(join_info);
  DDSResponderCall(responder, m_Interface.GetLocalKey(), join_info.m_EndpointId, m_GameRandomId, success);

  if(success && m_GameInfo.m_State == LobbyGameState::kStarted)
  {
    auto private_info = m_UserPrivateInfo.find(join_info.m_UserKey);
    LaunchGameForUser(join_info.m_UserKey, private_info->second);
  }
}

void Game::RequestRemoveUser(DDSKey user_key)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    DDSLog::LogInfo("Queueing game remove user");
    GameModifyAction action;
    action.m_Join = false;
    action.m_JoinInfo.m_UserKey = user_key;
    m_PendingActions.emplace_back(std::move(action));
    return;
  }

  DDSLog::LogInfo("Removing user from game");
  RemoveUser(user_key);
}

void Game::SetJoinCode(uint32_t join_code)
{
  DDSLog::LogInfo("Game got join code");
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  m_GameInfo.m_JoinCode = join_code;
}

void Game::AssignGameServer(DDSKey server_id, const std::string & server_ip, int port)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    m_Interface.CallShared(&ServerManager::HandleGameEnded, server_id);
    Cleanup();
    return;
  }

  DDSLog::LogInfo("Game got server assigned");

  m_AssignedServer = server_id;
  m_ServerIp = server_ip;
  m_ServerPort = port;
}

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
void Game::ChangeReady(DDSKey user_key, bool ready)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    return;
  }

  auto itr = m_GameInfo.m_Users.begin();
  while (itr != m_GameInfo.m_Users.end())
  {
    if (itr->second.m_UserKey == user_key)
    {
      break;
    }
    ++itr;
  }

  if (itr == m_GameInfo.m_Users.end())
  {
    return;
  }

  itr->second.m_Ready = ready;
}


bool Game::AllPlayersReady() const
{
  for(auto itr : m_GameInfo.m_Users)
  {
    if(itr.second.m_Ready == false)
    {
      return false;
    }
  }

  return true;
}

#endif

void Game::RequestSwitchEndpoint(DDSKey user_key, DDSKey endpoint_id)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing || m_AssignedServer == 0)
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "The game you were in has ended");
    Cleanup();
    return;
  }

  auto itr = m_UserPrivateInfo.find(user_key);
  if(itr == m_UserPrivateInfo.end())
  {
    m_Interface.Call(&UserConnection::SendRuntimeError, endpoint_id, "You were removed from the game");
    return;
  }

  m_Interface.Call(&GameServerConnection::RemoveUserFromGame, m_AssignedServer, m_Interface.GetLocalKey(), user_key);
  itr->second.m_EndpointId = endpoint_id;

  LaunchGameForUser(user_key, itr->second);
}

void Game::RequestStartGame(DDSKey user_key)
{
  if(m_GameInfo.m_State == LobbyGameState::kWaiting && m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_GameLeader == user_key)
  {
    BeginCountdown();
  }
}

void Game::RequestTeamSwitch(DDSKey requesting_user, DDSKey target_user, int team)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  if(m_GameInfo.m_Type != LobbyGameType::kPrivate)
  {
    return;
  }

  bool requesting_user_found = false;
  bool requesting_user_is_leader = false;

  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_UserKey == requesting_user)
    {
      requesting_user_found = true;

      if(user.second.m_UserKey == m_GameInfo.m_GameLeader)
      {
        requesting_user_is_leader = true;
      }
      break;
    }
  }

  if(!requesting_user_found)
  {
    return;
  }

  if(requesting_user_is_leader == false && requesting_user != target_user)
  {
    return;
  }

  auto & map_props = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto num_teams = GetMaxTeams(map_props, m_GameInfo.m_Settings.Value());

  if(team < 0 || team >= num_teams)
  {
    return;
  }

  auto max_team_size = GetMaxTeamSize(team, map_props, m_GameInfo.m_Settings.Value());

  int team_size = 0;

  int target_user_index = -1;
  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_UserKey == target_user)
    {
      target_user_index = user.first;
      if(user.second.m_Team == team)
      {
        return;
      }
    }

    if (user.second.m_Team == team)
    {
      team_size++;
    }
  }

  if(team_size + 1 > max_team_size || target_user_index == -1)
  {
    return;
  }

  m_GameInfo.m_Users[target_user_index].m_Team = team;
}

void Game::RequestKickUser(DDSKey requesting_user, DDSKey target_user)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  if(m_GameInfo.m_Type != LobbyGameType::kPrivate)
  {
    return;
  }

  bool requesting_user_is_leader = false;
  bool target_user_found = false;

  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_UserKey == requesting_user)
    {
      if(user.second.m_UserKey == m_GameInfo.m_GameLeader)
      {
        requesting_user_is_leader = true;
      }
    }

    if(user.second.m_UserKey == target_user)
    {
      target_user_found = true;
    }
  }

  if(!requesting_user_is_leader || !target_user_found)
  {
    return;
  }

  RemoveUser(target_user);
}


void Game::SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    return;
  }

  std::string player_name;
  bool is_leader = (user_key == m_GameInfo.m_GameLeader);
  for(auto itr : m_GameInfo.m_Users)
  {
    if(itr.second.m_UserKey == user_key)
    {
      player_name = itr.second.m_Name;
      break;
    }
  }

  if(player_name.empty())
  {
    return;
  }

  for(auto itr : m_GameInfo.m_Users)
  {
    m_Interface.Call(&User::HandleGameChat, itr.second.m_UserKey, m_Interface.GetLocalKey(), m_GameRandomId,
            itr.second.m_Name, itr.second.m_Icon, itr.second.m_Title, message);
  }
}

void Game::ChangeSettings(DDSKey user_key, const GameInitSettings & settings)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  if(m_GameInfo.m_State == LobbyGameState::kWaiting && m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_GameLeader == user_key)
  {
    m_GameInfo.m_Settings = settings;
    UpdateTeamSizes();
    ValidateTeams();
  }
}


#ifdef NET_USE_LOADOUT
void Game::ChangeLoadout(DDSKey user_key, const GamePlayerLoadout & loadout)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_UserKey == user_key)
    {
      user.second.m_Loadout = loadout;
      break;
    }
  }
}
#endif

void Game::RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key)
{
  DDSLog::LogInfo("Redeeming token");
  if(m_GameInfo.m_State == LobbyGameState::kInitializing || server_key != m_AssignedServer)
  {
    GameServerAuthenticateUserFailure msg;
    msg.m_ResponseId = response_id;

    m_Interface.Call(&GameServerConnection::NotifyTokenRedeemedFailure, server_key, m_Interface.GetLocalKey(), msg);
    return;
  }

  auto itr = m_UserPrivateInfo.find(user_key);
  if(itr != m_UserPrivateInfo.end())
  {
    for (auto user : m_GameInfo.m_Users)
    {
      if (user.second.m_UserKey == user_key)
      {
        if(itr->second.m_Token == token)
        {
          itr->second.m_Token = 0;
          itr->second.m_TokenAssigned = 0;

          GameServerAuthenticateUserSuccess msg;
          msg.m_ResponseId = response_id;
          msg.m_GameId = m_Interface.GetLocalKey();
          msg.m_UserId = user.second.m_UserKey;
          msg.m_Name = user.second.m_Name;
          msg.m_Team = user.second.m_Team;
          msg.m_AdminLevel = user.second.m_AdminLevel;
          msg.m_Icon = user.second.m_Icon;
          msg.m_Title = user.second.m_Title;
          msg.m_Celebration = user.second.m_Celebration;

#ifdef NET_USE_LOADOUT
          msg.m_Loadout = user.second.m_Loadout.Value();
#endif

#ifdef ENABLE_SQUADS
          msg.m_Squad = user.second.m_SquadTag;
#endif

          m_Interface.Call(&GameServerConnection::NotifyTokenRedeemedSuccess, server_key, m_Interface.GetLocalKey(), msg);
          return;
        }
      }
    }
  }

  GameServerAuthenticateUserFailure msg;
  msg.m_ResponseId = response_id;

  m_Interface.Call(&GameServerConnection::NotifyTokenRedeemedFailure, server_key, m_Interface.GetLocalKey(), msg);
}

void Game::HandleMemberUpdate(DDSKey user_key, std::string data)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  DDSLog::LogInfo("Got member data update");

  auto itr = m_GameInfo.m_Users.begin();
  while (itr != m_GameInfo.m_Users.end())
  {
    if (itr->second.m_UserKey == user_key)
    {
      break;
    }
    ++itr;
  }

  if (itr == m_GameInfo.m_Users.end())
  {
    return;
  }

  StormDataApplyChangePacket(itr->second, data.c_str());
}

void Game::HandleUserDisconnected(DDSKey user_key)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  DDSLog::LogInfo("User disconnected");

  for (auto user : m_GameInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      m_GameInfo.m_Users.RemoveAt(user.first);
      m_UserPrivateInfo.erase(user_key);

      bool allow_reconnect = m_GameInfo.m_Type == LobbyGameType::kCompetitive;
      m_Interface.Call(&User::NotifyLeftGame, user_key, m_Interface.GetLocalKey(), m_GameRandomId, allow_reconnect);
    }
  }
}

void Game::HandleGameComplete()
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  DDSLog::LogInfo("Game complete");

  m_GameInfo.m_State = LobbyGameState::kPostGame;
  m_GameEndTime = m_Interface.GetNetworkTime();
}


void Game::HandleServerDisconnected()
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    Cleanup();
    return;
  }

  DDSLog::LogInfo("Server disconnected");
}

void Game::AdminDestroyGame()
{
  DDSLog::LogInfo("Admin destroyed game");
  Cleanup();
}

void Game::MatchmakerDestroyGame()
{
  DDSLog::LogInfo("Matchmaker destroyed game");
  Cleanup();
}

bool Game::AddUser(const GameUserJoinInfo & join_info)
{
  if(join_info.m_IntendedType != m_GameInfo.m_Type)
  {
    return false;
  }

  if(m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_Password != join_info.m_Password)
  {
    return false;
  }

  DDSKey sub_id = m_Interface.CreateSubscription(DDSSubscriptionTarget<User>{},
                                                 join_info.m_UserKey, ".m_UserInfo", &Game::HandleMemberUpdate, true, join_info.m_UserKey);

  GameMember member;
  member.m_Name = join_info.m_Name;
  member.m_UserKey = join_info.m_UserKey;
  member.m_AdminLevel = join_info.m_AdminLevel;
  member.m_Icon = join_info.m_Icon;
  member.m_Title = join_info.m_Title;
  member.m_Celebration = join_info.m_Celebration;

#ifdef ENABLE_SQUADS
  member.m_SquadTag = join_info.m_SquadTag;
#endif

  int assigned_team = -1;
  if(FindUserInGeneratedGame(join_info.m_UserKey, m_GameInfo.m_Type == LobbyGameType::kCasual, assigned_team))
  {
    member.m_Team = assigned_team;
  }
  else if(join_info.m_AssignedTeam != -1)
  {
    member.m_Team = join_info.m_AssignedTeam;
  }
  else if(join_info.m_Observer)
  {
    member.m_Team = -1;
  }
  else
  {
    auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);

    auto team_counts = GetTeamCounts();
    member.m_Team = GetRandomTeam(team_counts, DDSGetRandomNumber(), level_info, m_GameInfo.m_Settings.Value());
  }

  auto player_index = m_GameInfo.m_Users.HighestIndex();
  m_GameInfo.m_Users.EmplaceBack(std::move(member));

  GameUserPrivateInfo private_info;
  private_info.m_EndpointId = join_info.m_EndpointId;
  private_info.m_SubscriptionId = sub_id;
  private_info.m_UserZoneInfo = join_info.m_ZoneInfo;
  private_info.m_MatchmakerRandomId = join_info.m_MatchmakerRandomId;

  m_UserPrivateInfo.emplace(std::make_pair(join_info.m_UserKey, private_info));
  return true;
}

void Game::RemoveUser(DDSKey user_key)
{
  auto itr = m_UserPrivateInfo.find(user_key);
  if(itr != m_UserPrivateInfo.end())
  {
    m_Interface.DestroySubscription<User>(user_key, itr->second.m_SubscriptionId);
    m_UserPrivateInfo.erase(itr);
  }

  bool found_user = false;
  int user_team = 0;
  for (auto user : m_GameInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      found_user = true;
      user_team = user.second.m_Team;
      m_GameInfo.m_Users.RemoveAt(user.first);
      break;
    }
  }

  if(found_user == false)
  {
    found_user = FindUserInGeneratedGame(user_key, m_GameInfo.m_Type == LobbyGameType::kCasual, user_team);
  }

  if(found_user && m_GameInfo.m_Type == LobbyGameType::kCasual)
  {
    m_Interface.CallShared(&Matchmaker::NotifyPlayerLeftCasualGame, m_Interface.GetLocalKey(), user_team, m_ZoneIndex);
  }

  if(m_AssignedServer != 0)
  {
    m_Interface.Call(&GameServerConnection::RemoveUserFromGame, m_AssignedServer, m_Interface.GetLocalKey(), user_key);
  }

  if(m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_Users.HighestIndex() == -1)
  {
    Cleanup();
  }
}

void Game::BeginCountdown()
{
  DDSLog::LogInfo("Starting countdown");
  assert(m_AssignedServer == 0);

  static const int kStartGameCountdown = 10;
  m_GameInfo.m_Countdown = kStartGameCountdown;
  m_GameInfo.m_State = LobbyGameState::kCountdown;

  if(m_ZoneIndex == -1)
  {
    m_ZoneIndex = FindBestZoneForPlayers();
  }

  m_Interface.CallShared(&ServerManager::AssignGameServer, m_Interface.GetLocalKey(), m_ZoneIndex);
}


void Game::StartGame()
{
  DDSLog::LogInfo("Starting game");
  m_GameInfo.m_Countdown = 0;
  m_GameInfo.m_State = LobbyGameState::kAssigningServer;
}

void Game::AbandonGame()
{
  DDSLog::LogInfo("Abandoning game");
  for(auto & user : m_UserPrivateInfo)
  {
    m_Interface.Call(&User::RejoinMatchmaking, user.first, user.second.m_EndpointId, user.second.m_MatchmakerRandomId);
  }
}

void Game::RandomizeTeams()
{
  DDSLog::LogInfo("Randomizing teams");
  auto & map_props = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto num_teams = GetMaxTeams(map_props, m_GameInfo.m_Settings.Value());

  std::vector<int> team_counts;
  team_counts.resize(num_teams);

  std::vector<int> max_team_sizes;
  for(int team = 0; team < num_teams; ++team)
  {
    max_team_sizes.push_back(GetMaxTeamSize(team, map_props, m_GameInfo.m_Settings.Value()));
  }

  std::vector<std::size_t> player_indices;
  for(auto user : m_GameInfo.m_Users)
  {
    player_indices.emplace_back(user.first);
  }

  std::shuffle(player_indices.begin(), player_indices.end(), DDSRandomGenerator{});
  for(auto & index : player_indices)
  {
    auto team = GetRandomTeam(team_counts, DDSGetRandomNumber(), map_props, m_GameInfo.m_Settings.Value());
    if(team <= num_teams && team_counts[team] + 1 < max_team_sizes[team])
    {
      m_GameInfo.m_Users[index].m_Team = team;
      team_counts[team]++;
    }
    else
    {
      m_GameInfo.m_Users[index].m_Team = -1;
    }
  }
}

void Game::UpdateGameList()
{
  int player_count = 0;
  for(auto itr : m_GameInfo.m_Users)
  {
    if(itr.second.m_Team != -1)
    {
      player_count++;
    }
  }

  auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto & level_name = g_LobbyLevelList.GetLevelName(m_GameInfo.m_Settings->m_StageIndex);
  int max_players = GetMaxPlayers(level_info, m_GameInfo.m_Settings.Value());

  m_Interface.CallShared(&GameList::UpdateGame, m_Interface.GetLocalKey(), player_count, max_players, level_name, false);
}

int Game::FindBestZoneForPlayers()
{
  static const int kMinPing = 70;
  static const int kMaxPing = 200;

  int zone_totals[kNumProjectZones] = {};
  for(auto & elem : m_UserPrivateInfo)
  {
    auto & info = elem.second;
    for(int index = 0; index < kNumProjectZones; ++index)
    {
      if(info.m_UserZoneInfo.m_Latencies[index] < kMinPing)
      {
        zone_totals[index] += kMinPing;
      }
      else if(info.m_UserZoneInfo.m_Latencies[index] >= kMaxPing)
      {
        zone_totals[index] += kMaxPing;
      }
      else
      {
        zone_totals[index] += info.m_UserZoneInfo.m_Latencies[index];
      }
    }
  }

  int best_zone = 0;
  int best_latency = zone_totals[0];
  for(int index = 1; index < kNumProjectZones; ++index)
  {
    if(zone_totals[index] < best_latency)
    {
      best_zone = index;
      best_latency = zone_totals[index];
    }
  }

  return best_zone;
}

std::vector<int> Game::GetTeamCounts()
{
  std::vector<int> team_counts;
  team_counts.resize(kMaxTeams);
  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_Team >= 0 && user.second.m_Team < kMaxTeams)
    {
      team_counts[user.second.m_Team]++;
    }
  }

  return team_counts;
}

std::vector<int> Game::GetMaxTeamCounts()
{
  std::vector<int> team_counts;
  team_counts.resize(kMaxTeams);
  for(int team = 0; team < kMaxTeams; ++team)
  {
    team_counts[team] = m_GameInfo.m_TeamSizes->m_MaxTeamSizes[team];
  }

  return team_counts;
}

void Game::ValidateTeams()
{
  std::vector<int> team_counts;
  team_counts.resize(kMaxTeams);

  for(auto player : m_GameInfo.m_Users)
  {
    int team = player.second.m_Team;
    if(team_counts[team] >= m_GameInfo.m_TeamSizes->m_MaxTeamSizes[team])
    {
      player.second.m_Team = -1;
    }
    else
    {
      team_counts[team]++;
    }
  }
}

void Game::UpdateTeamSizes()
{
  auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto max_teams = GetMaxTeams(level_info, m_GameInfo.m_Settings.Value());

  GameInfoTeamSizes team_sizes;
  if(!m_TeamSizeOverrides.empty())
  {
    for(int index = 0; index < kMaxTeams; ++index)
    {
      if(index < m_TeamSizeOverrides.size())
      {
        team_sizes.m_MaxTeamSizes[index] = m_TeamSizeOverrides[index];
      }
    }
  }
  else
  {
    for(int index = 0; index < kMaxTeams; ++index)
    {
      team_sizes.m_MaxTeamSizes[index] = GetMaxTeamSize(index, level_info, m_GameInfo.m_Settings.Value());
    }
  }

  m_GameInfo.m_TeamSizes = team_sizes;
}

bool Game::FindUserInGeneratedGame(DDSKey user_id, bool remove_if_found, int & out_team)
{
  for(int team = 0; team < kMaxTeams; ++team)
  {
    auto & user_list = m_MatchmakerGameInfo.m_Users[team];
    for(auto itr = user_list.begin(), end = user_list.end(); itr != end; ++itr)
    {
      if(itr->m_UserId == user_id)
      {
        out_team = team;
        if(remove_if_found)
        {
          user_list.erase(itr);
        }

        return true;
      }
    }
  }

  return false;
}

bool Game::AllGeneratedUsersConnected()
{
  for(int team = 0; team < kMaxTeams; ++team)
  {
    auto & user_list = m_MatchmakerGameInfo.m_Users[team];
    for(auto & user : user_list)
    {
      bool found = false;
      for(auto test_user : m_GameInfo.m_Users)
      {
        if(test_user.second.m_UserKey == user.m_UserId)
        {
          found = true;
        }
      }

      if(found == false)
      {
        return false;
      }
    }
  }

  return true;
}

void Game::LaunchGameForUser(DDSKey user_id, GameUserPrivateInfo & info)
{
  info.m_Token = DDSGetRandomNumber64();
  info.m_TokenAssigned = m_Interface.GetNetworkTime();

  m_Interface.Call(&User::NotifyLaunchGame, user_id, m_Interface.GetLocalKey(),
          m_GameRandomId, m_ServerIp, m_ServerPort, info.m_Token);
}