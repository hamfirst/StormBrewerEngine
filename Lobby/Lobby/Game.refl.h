#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"
#include "LobbyConfig.h"

struct GameToken
{
  DDSKey m_Token;
  DDSKey m_UserKey;
};

struct Game
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Game(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC Init(GameLobbySettings settings);
  void STORM_REFL_FUNC Cleanup();
  void STORM_REFL_FUNC CheckIfNobodyJoined();
  void STORM_REFL_FUNC AddUser(DDSResponder & responder, DDSKey user_key);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  void STORM_REFL_FUNC ChangeReady(DDSKey user_key, bool ready);
#endif

  void STORM_REFL_FUNC StartGame();

  void STORM_REFL_FUNC RandomizeTeams();
  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title);
  void STORM_REFL_FUNC UpdateSettings(GameInitSettings settings);
  void STORM_REFL_FUNC UpdateGameList();

  void STORM_REFL_FUNC SendLaunchGame(int game_id, DDSKey user_id, DDSKey endpoint_id);
  void STORM_REFL_FUNC ExpireToken(DDSKey token);
  void STORM_REFL_FUNC ExpireGame(int game_id);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);

public:
  DDSKey m_AssignedServer = 0;
  GameInfo m_GameInfo;

  std::map<DDSKey, DDSKey> m_MemberSubscriptionIds;
  std::map<DDSKey, GameToken> m_Tokens;

private:
  DDSNodeInterface m_Interface;
};
