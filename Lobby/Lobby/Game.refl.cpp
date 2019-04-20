
#include "Lobby/Game.refl.meta.h"
#include "Lobby/User.refl.meta.h"
#include "Lobby/GameList.refl.meta.h"
#include "Lobby/ServerManager.refl.meta.h"
#include "Lobby/GameServerConnection.refl.meta.h"
#include "Lobby/LobbyLevelList.refl.h"

#include "LobbyShared/LobbyGameFuncs.h"

#include "HurricaneDDS/DDSResponderCall.h"

static const int kCasualGameAutoStartTime = 90;

Game::Game(DDSNodeInterface node_interface)
  : m_Interface(node_interface)
{

}

void Game::InitPrivateGame(const GameInitSettings & settings, std::string password)
{
  Init(settings);

  m_Interface.CallShared(&GameList::AssignJoinCode, m_Interface.GetLocalKey());
  
  m_GameInfo.m_Password = password;
  m_GameInfo.m_Type = LobbyGameType::kPrivate;
}

void Game::InitCasualGame(const GameInitSettings & settings, int zone)
{
  Init(settings);
  m_GameInfo.m_Type = LobbyGameType::kCasual;
  m_ZoneIndex = zone;
}

void Game::InitCompetitiveGame(const GameInitSettings & settings, const GeneratedGame & game, int zone)
{
  Init(settings);
  m_GameInfo.m_Type = LobbyGameType::kCompetitive;

  m_CompetitiveGameInfo = game;
  m_ZoneIndex = zone;
}

void Game::Init(const GameInitSettings & settings)
{
  if(m_GameInfo.m_State != LobbyGameState::kInitializing)
  {
    return;
  }

  m_GameInfo.m_Settings = settings;
  m_GameInfo.m_State = LobbyGameState::kWaiting;
  m_GameCreateTime = m_Interface.GetNetworkTime();

  auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto & level_name = g_LobbyLevelList.GetLevelName(m_GameInfo.m_Settings->m_StageIndex);

  auto max_players = GetMaxPlayers(level_info, m_GameInfo.m_Settings.Value());

  m_Interface.CallShared(&GameList::AddGame, m_Interface.GetLocalKey(), 0, max_players,
                         level_name, m_GameInfo.m_JoinCode, !m_GameInfo.m_Password.emtpy(), false);

  for(auto & join_info : m_PendingJoins)
  {
    auto responder = DDSResponder{m_Interface, join_info.second};
    AddUser(responder, join_info.first);
  }

  m_PendingJoins.clear();
}

void Game::Destroy()
{
  for(auto user : m_GameInfo.m_Users)
  {
    m_Interface.Call(&User::NotifyLeftGame, user.second.m_UserKey, m_Interface.GetLocalKey(), m_GameRandomId);
  }

  Cleanup();
}

void Game::Cleanup()
{
  m_Interface.CallShared(&GameList::RemoveGame, m_Interface.GetLocalKey());
  m_Interface.DestroySelf();
}

void Game::Update()
{
  if(m_GameInfo.m_State == LobbyGameState::kCountdown)
  {
    m_GameInfo.m_Countdown = m_GameInfo.m_Countdown - 1;
    if(m_GameInfo.m_Countdown <= 0)
    {
      StartGame();
    }
  }
  else if(m_GameInfo.m_State == LobbyGameState::kWaiting && m_GameInfo.m_Type == LobbyGameType::kCasual)
  {
    m_GameInfo.m_Countdown = kCasualGameAutoStartTime - (m_Interface.GetNetworkTime() - m_GameCreateTime);
    if(m_GameInfo.m_Countdown <= 0)
    {
      StartGame();
    }
  }
}

void Game::SetJoinCode(uint32_t join_code)
{
  m_GameInfo.m_JoinCode = join_code;
}

void Game::AddUser(DDSResponder & responder, const GameUserJoinInfo & join_info)
{
  if(m_GameInfo.m_State == LobbyGameState::kInitializing)
  {
    m_PendingJoins.emplace_back(std::make_pair(join_info, responder.m_Data));
    return;
  }

  if(join_info.m_IntendedType != m_GameInfo.m_Type)
  {
    DDSResponderCall(responder, m_Interface.GetLocalKey(), join_info.m_EndpointId, m_GameRandomId, false);
    return;
  }

  if(m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_Password != join_info.m_Password)
  {
    DDSResponderCall(responder, m_Interface.GetLocalKey(), join_info.m_EndpointId, m_GameRandomId, false);
    return;
  }

  DDSKey sub_id = m_Interface.CreateSubscription(DDSSubscriptionTarget<User>{},
          join_info.m_UserKey, ".m_UserInfo", &Game::HandleMemberUpdate, true, join_info.m_UserKey);

  GameMember member;
  member.m_UserKey = join_info.m_UserKey;
  member.m_Name = join_info.m_Name;

  if(join_info.m_Observer)
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
  m_UserZoneInfo.emplace(std::make_pair(player_index, join_info.m_ZoneInfo));

  m_MemberSubscriptionIds.emplace(std::make_pair(join_info.m_UserKey, sub_id));
  DDSResponderCall(responder, m_Interface.GetLocalKey(), join_info.m_EndpointId, m_GameRandomId, true);
}

void Game::RemoveUser(DDSKey user_key)
{
  auto itr = m_MemberSubscriptionIds.find(user_key);
  if (itr == m_MemberSubscriptionIds.end())
  {
    return;
  }

  m_Interface.DestroySubscription<User>(user_key, itr->second);
  m_MemberSubscriptionIds.erase(itr);

  for (auto user : m_GameInfo.m_Users)
  {
    if (user.second.m_UserKey == user_key)
    {
      m_GameInfo.m_Users.RemoveAt(user.first);
      m_UserZoneInfo.erase(user.first);
      break;
    }
  }

  if(m_GameInfo.m_Users.Empty())
  {
    Cleanup();
  }
}

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
void Game::ChangeReady(DDSKey user_key, bool ready)
{
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

  itr->second.m_Ready = true;
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

void Game::BeginCountdown()
{
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
  m_GameInfo.m_Countdown = 0;
  m_GameInfo.m_State = LobbyGameState::kStarted;
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

void Game::RandomizeTeams()
{
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

void Game::SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message)
{
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
            itr.second.m_Name, itr.second.m_Title, message);
  }
}

void Game::UpdateSettings(DDSKey user_key, GameInitSettings settings)
{
  if(m_GameInfo.m_State == LobbyGameState::kWaiting && m_GameInfo.m_Type == LobbyGameType::kPrivate && m_GameInfo.m_GameLeader == user_key)
  {
    m_GameInfo.m_Settings = settings;
    ValidateTeams();
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

void Game::RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key)
{
  auto itr = m_Tokens.find(token);
  if(itr == m_Tokens.end())
  {
    m_Interface.Call(&GameServerConnection::NotifyTokenRedeemed, server_key, user_key, m_Interface.GetLocalKey(), response_id, false);
  }
  else
  {
    bool is_valid = itr->second.m_UserKey == user_key;
    m_Interface.Call(&GameServerConnection::NotifyTokenRedeemed, server_key, user_key, m_Interface.GetLocalKey(), response_id, is_valid);
    m_Tokens.erase(itr);
  }
}

void Game::ExpireToken(DDSKey token)
{
  auto itr = m_Tokens.find(token);
  if(itr == m_Tokens.end())
  {
    return;
  }

  m_Tokens.erase(itr);
}

void Game::HandleMemberUpdate(DDSKey user_key, std::string data)
{
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

void Game::HandleGameComplete()
{
  Destroy();
}

int Game::FindBestZoneForPlayers()
{
  static const int kMinPing = 70;
  static const int kMaxPing = 200;

  int zone_totals[kNumProjectZones] = {};
  for(auto & elem : m_UserZoneInfo)
  {
    auto & info = elem.second;
    for(int index = 0; index < kNumProjectZones; ++index)
    {
      if(info.m_Latencies[index] < kMinPing)
      {
        zone_totals[index] += kMinPing;
      }
      else if(info.m_Latencies[index] >= kMaxPing)
      {
        zone_totals[index] += kMaxPing;
      }
      else
      {
        zone_totals[index] += info.m_Latencies[index];
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

  auto & map_props = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto num_teams = GetMaxTeams(map_props, m_GameInfo.m_Settings.Value());

  team_counts.resize(num_teams);
  for(auto user : m_GameInfo.m_Users)
  {
    if(user.second.m_Team >= 0 && user.second.m_Team < num_teams)
    {
      team_counts[user.second.m_Team]++;
    }
  }

  return team_counts;
}

void Game::ValidateTeams()
{
  auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto max_teams = GetMaxTeams(level_info, m_GameInfo.m_Settings.Value());

  std::vector<int> max_team_sizes;
  for(int team = 0; team < max_teams; ++team)
  {
    max_team_sizes.emplace_back(GetMaxTeamSize(team, level_info, m_GameInfo.m_Settings.Value()));
  }

  std::vector<int> team_counts;
  team_counts.resize(max_teams);

  for(auto player : m_GameInfo.m_Users)
  {
    int team = player.second.m_Team;
    if(team >= max_teams || team_counts[team] >= max_team_sizes[team])
    {
      player.second.m_Team = -1;
    }
    else
    {
      team_counts[team]++;
    }
  }
}