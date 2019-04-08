
#include "GameList.refl.meta.h"
#include "GameServerConnection.refl.meta.h"

#include "StormRefl/StormReflJsonStd.h"

#ifdef ENABLE_GAME_LIST

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameListGame);

GameList::GameList(DDSObjectInterface & iface) :
  m_Interface(iface)
{

}

void GameList::AddGame(DDSKey game_key, std::string name, int cur_players, int max_players,
                       std::string map, std::string join_code, bool password, bool started)
{
  GameListGame game_data;
  game_data.m_MaxPlayers = max_players;
  game_data.m_CurPlayers = cur_players;
  game_data.m_PasswordProtected = password;
  game_data.m_Started = started;
  game_data.m_Name = name;
  game_data.m_Map = map;
  game_data.m_JoinCode = join_code;
  m_GameList.InsertAt(game_key, std::move(game_data));
  m_JoinCodeLookup.insert(std::make_pair(crc64(join_code), game_key));
}

void GameList::UpdateGame(DDSKey game_key, int cur_players, int max_players, std::string map, bool started)
{
  auto cur_data = m_GameList.TryGet(game_key);
  if(cur_data)
  {
    auto new_data = *cur_data;
    new_data.m_MaxPlayers = max_players;
    new_data.m_CurPlayers = cur_players;
    new_data.m_Started = started;
    new_data.m_Map = map;
    *cur_data = std::move(new_data);
  }
}

void GameList::RemoveGame(DDSKey game_key)
{
  auto cur_data = m_GameList.TryGet(game_key);
  if(cur_data)
  {
    m_JoinCodeLookup.erase(crc64(cur_data->m_JoinCode));
    m_GameList.RemoveAt(game_key);
  }
}

#endif
