#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include <HurricaneDDS/DDSDataObject.h>

#include "LobbyConfig.h"

#ifdef ENABLE_GAME_LIST

struct GameListGame
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameListGame);

  RInt m_MaxPlayers;
  RInt m_CurPlayers;
  RBool m_PasswordProtected;
  RBool m_Started;
  RString m_Map;
  RUInt m_JoinCode;
};


struct GameList
{
public:
  DDS_SHARED_OBJECT;

  GameList(DDSObjectInterface & iface);

  void STORM_REFL_FUNC AddGame(DDSKey game_key, int cur_players, int max_players,
          std::string map, uint32_t join_code, bool password, bool started);
  void STORM_REFL_FUNC UpdateGame(DDSKey game_key, int cur_players, int max_players, std::string map, bool started);
  void STORM_REFL_FUNC RemoveGame(DDSKey game_key);

  void STORM_REFL_FUNC AssignJoinCode(DDSKey game_key);
public:

  RMap<DDSKey, GameListGame> m_GameList;
  std::map<uint32_t, DDSKey> m_JoinCodeLookup;

private:
  STORM_REFL_IGNORE DDSObjectInterface & m_Interface;
};

#endif
