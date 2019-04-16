
#include "Lobby/Game.refl.meta.h"
#include "Lobby/User.refl.meta.h"
#include "Lobby/GameList.refl.meta.h"
#include "Lobby/GameServerConnection.refl.meta.h"
#include "Lobby/LobbyLevelList.refl.h"

#include "LobbyShared/LobbyGameFuncs.h"

#include "HurricaneDDS/DDSResponderCall.h"

static const int kCasualGameAutoStartTime = 90;

Game::Game(DDSNodeInterface node_interface)
  : m_Interface(node_interface)
{

}


void Game::Init(GameInitSettings settings)
{
  m_GameInfo.m_Settings = settings;
  m_GameCreateTime = m_Interface.GetNetworkTime();

  auto & level_info = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings->m_StageIndex);
  auto & level_name = g_LobbyLevelList.GetLevelName(m_GameInfo.m_Settings->m_StageIndex);

  auto max_players = GetMaxPlayers(level_info, m_GameInfo.m_Settings.Value());

  m_Interface.CallShared(&GameList::AddGame, m_Interface.GetLocalKey(), 0, max_players,
                         level_name, m_GameInfo.m_JoinCode, !m_GameInfo.m_Password.emtpy(), false);
}

void Game::Cleanup()
{
  m_Interface.CallShared(&GameList::RemoveGame, m_Interface.GetLocalKey());
  m_Interface.DestroySelf();
}

void Game::Update()
{
  if(m_GameInfo.m_State == GameState::kCountdown)
  {
    m_GameInfo.m_Countdown = m_GameInfo.m_Countdown - 1;
    if(m_GameInfo.m_Countdown <= 0)
    {
      StartGame();
    }
  }
  else if(m_GameInfo.m_State == GameState::kWaiting && m_GameInfo.m_Type == GameType::kCasual)
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

void Game::AddUser(DDSResponder & responder, DDSKey user_key)
{
  DDSKey sub_id =
          m_Interface.CreateSubscription(DDSSubscriptionTarget<User>{}, user_key, ".m_UserInfo", &Game::HandleMemberUpdate, true, user_key);

  m_MemberSubscriptionIds.emplace(std::make_pair(user_key, sub_id));
  DDSResponderCall(responder, ChannelJoinResult::kSuccess);
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


void Game::StartGame()
{
  m_GameInfo.m_Countdown = 0;
  m_GameInfo.m_State = GameState::kStarted;
}

void Game::RequestStartGame(DDSKey user_key)
{
  if(m_GameInfo.m_State == GameState::kWaiting && m_GameInfo.m_Type == GameType::kPrivate && m_GameInfo.m_GameLeader == user_key)
  {
    StartGame();
  }
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
    auto team = GetRandomTeam(team_counts, DDSGetRandomNumber());
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

void Game::SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title)
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


}

void Game::UpdateSettings(DDSKey user_key, GameInitSettings settings)
{
  if(m_GameInfo.m_State == GameState::kWaiting && m_GameInfo.m_Type == GameType::kPrivate && m_GameInfo.m_GameLeader == user_key)
  {
    m_GameInfo.m_Settings = settings;
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

  StormDataApplyChangePacket(itr->second, data.data());
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