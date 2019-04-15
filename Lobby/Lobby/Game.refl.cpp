
#include "Lobby/Game.refl.meta.h"
#include "Lobby/User.refl.meta.h"
#include "Lobby/GameList.refl.meta.h"
#include "Lobby/LobbyLevelList.refl.h"

#include <HurricaneDDS/DDSResponderCall.h>

Game::Game(DDSNodeInterface node_interface)
  : m_Interface(node_interface)
{

}


void Game::Init(GameLobbySettings settings)
{
  m_GameInfo.m_Settings = settings;

  auto level = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings.m_InitSettings->m_StageIndex);
  int max_players = kMaxPlayers;

#ifdef NET_USE_PLAYER_LIMIT
  max_players = level.m_PlayerCount;
#endif

  m_Interface.CallShared(&GameList::AddGame, m_Interface.GetLocalKey(), m_GameInfo.m_Settings.m_Name, 0, max_players,
          level.m_Name, m_GameInfo.m_Settings.m_JoinCode, !m_GameInfo.m_Settings.m_Password.emtpy(), false);
}

void Game::Cleanup()
{
  m_Interface.CallShared(&GameList::RemoveGame, m_Interface.GetLocalKey());
  m_Interface.DestroySelf();
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
  if(m_GameInfo.m_Started)
  {
    return;
  }
}

void Game::RandomizeTeams()
{

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

void Game::UpdateSettings(GameInitSettings settings)
{

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

  auto level = g_LobbyLevelList.GetLevelInfo(m_GameInfo.m_Settings.m_InitSettings->m_StageIndex);
  int max_players = kMaxPlayers;

#ifdef NET_USE_PLAYER_LIMIT
  max_players = level.m_PlayerCount;
#endif

  m_Interface.CallShared(&GameList::UpdateGame, m_Interface.GetLocalKey(), player_count, max_players, level.m_Name, false);
}

void Game::ExpireToken(DDSKey token)
{

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

