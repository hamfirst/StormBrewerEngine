
#include "ServerList.refl.meta.h"
#include "GameServerConnection.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ServerListGame);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(ServerListServer);

ServerList::ServerList(DDSObjectInterface & iface) :
  m_Interface(iface)
{

}

void ServerList::AddServer(DDSKey server_key, std::string server_name, std::string location, std::string server_host, int ping_port)
{
  ServerListServer server;
  server.m_Name = server_name;
  server.m_Location = location;
  server.m_Host = server_host;
  server.m_PingPort = ping_port;

  m_ServerList.Emplace(server_key, server);
}

void ServerList::RemoveServer(DDSKey server_key)
{
  m_ServerList.Remove(server_key);
}

void ServerList::AddGame(DDSKey server_key, int game_id, std::string name, std::string map, int cur_players, int max_players, bool password)
{
  ServerListGame game;
  game.m_Name = name;
  game.m_Map = map;
  game.m_CurPlayers = cur_players;
  game.m_MaxPlayers = max_players;
  game.m_PasswordProtected = password;

  m_ServerList[server_key].m_Games.EmplaceAt(game_id, std::move(game));
}

void ServerList::UpdateGame(DDSKey server_key, int game_id, int cur_players, int cur_observer)
{
  if (m_ServerList[server_key].m_Games[game_id].m_CurPlayers != cur_players)
  {
    m_ServerList[server_key].m_Games[game_id].m_CurPlayers = cur_players;
  }

  if (m_ServerList[server_key].m_Games[game_id].m_CurObservers != cur_observer)
  {
    m_ServerList[server_key].m_Games[game_id].m_CurObservers = cur_observer;
  }
}

void ServerList::StartGame(DDSKey server_key, int game_id)
{
  m_ServerList[server_key].m_Games[game_id].m_Started = true;
}

void ServerList::RemoveGame(DDSKey server_key, int game_id)
{
  m_ServerList[server_key].m_Games.RemoveAt(game_id);
}

void ServerList::HangUpAllServers()
{
  for (auto server_info : m_ServerList)
  {
    m_Interface.Call(&GameServerConnection::SendHangUp, server_info.first);
  }
}
