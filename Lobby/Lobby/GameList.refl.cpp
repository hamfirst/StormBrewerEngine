
#include "GameList.refl.meta.h"
#include "Game.refl.meta.h"
#include "GameServerConnection.refl.meta.h"
#include "User.refl.meta.h"
#include "UserConnection.refl.meta.h"

#include "StormRefl/StormReflJsonStd.h"

#include "HurricaneDDS/DDSRandom.h"
#include "HurricaneDDS/DDSResponderCall.h"



GameList::GameList(DDSObjectInterface & iface) :
  m_Interface(iface)
{

}

void GameList::AddGame(DDSKey game_key, int cur_players, int max_players,
                       std::string map, uint32_t join_code, bool password, bool started)
{
  GameListGame game_data;

#ifdef ENABLE_GAME_LIST
  game_data.m_MaxPlayers = max_players;
  game_data.m_CurPlayers = cur_players;
  game_data.m_PasswordProtected = password;
  game_data.m_Started = started;
  game_data.m_Map = map;
#endif

  game_data.m_JoinCode = join_code;
  m_GameList.InsertAt(game_key, std::move(game_data));
  m_JoinCodeLookup.insert(std::make_pair(join_code, game_key));
}

void GameList::UpdateGame(DDSKey game_key, int cur_players, int max_players, std::string map, bool started)
{
#ifdef ENABLE_GAME_LIST
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
#endif
}

void GameList::AssignJoinCode(DDSKey game_key)
{
  auto cur_data = m_GameList.TryGet(game_key);
  if(cur_data)
  {
    while(true)
    {
      uint32_t room_id = 0;
      for (int index = 0; index < 4; ++index)
      {
        room_id <<= 8;

        auto rand = DDSGetRandomNumber() % 36;
        if (rand < 26)
        {
          room_id |= (rand + 'A');
        }
        else
        {
          room_id |= (rand - 26 + '0');
        }
      }

      if(m_JoinCodeLookup.find(room_id) == m_JoinCodeLookup.end())
      {
        m_JoinCodeLookup.emplace(std::make_pair(room_id, game_key));
        cur_data->m_JoinCode = room_id;

        m_Interface.Call(&Game::SetJoinCode, game_key, room_id);
        return;
      }
    }
  }
}

void GameList::LookupJoinCode(DDSResponder & responder, uint32_t join_code, const UserGameJoinInfo & join_info)
{
  auto itr = m_JoinCodeLookup.find(join_code);
  if(itr != m_JoinCodeLookup.end())
  {
    DDSResponderCall(responder, itr->second, join_info);
  }
  else
  {
    DDSResponderCall(responder, 0, join_info);
  }
}

void GameList::RemoveGame(DDSKey game_key)
{
  auto cur_data = m_GameList.TryGet(game_key);
  if(cur_data)
  {
    if(cur_data->m_JoinCode != 0U)
    {
      m_JoinCodeLookup.erase(cur_data->m_JoinCode);
    }

    m_GameList.RemoveAt(game_key);
  }
}

