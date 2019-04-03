
#include "ServerList.refl.meta.h"
#include "GameServerConnection.refl.meta.h"

#ifdef ENABLE_GAME_LIST

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ServerListGame);

ServerList::ServerList(DDSObjectInterface & iface) :
  m_Interface(iface)
{

}

void ServerList::AddGame(DDSKey game_key, std::string name, std::string map, int cur_players, int max_players, bool password)
{
  ServerListGame game;
  game.m_Name = name;
  game.m_Map = map;
  game.m_CurPlayers = cur_players;
  game.m_MaxPlayers = max_players;
  game.m_PasswordProtected = password;

  m_GameList.Emplace(game_key, std::move(game));
}

void ServerList::UpdateGame(DDSKey game_key, int cur_players, int cur_observer)
{
  if (m_GameList[game_key].m_CurPlayers != cur_players)
  {
    m_GameList[game_key].m_CurPlayers = cur_players;
  }

  if (m_GameList[game_key].m_CurObservers != cur_observer)
  {
    m_GameList[game_key].m_CurObservers = cur_observer;
  }
}

void ServerList::StartGame(DDSKey game_key)
{
  m_GameList[game_key].m_Started = true;
}

void ServerList::RemoveGame(DDSKey game_key)
{
  m_GameList.RemoveAt(game_key);
}


#endif
