#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"
#include "LobbyConfig.h"

struct GameToken
{
  STORM_REFL;
  DDSKey m_UserKey;
};


struct Game
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Game(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC Init(GameInitSettings settings);
  void STORM_REFL_FUNC Cleanup();

  void STORM_REFL_FUNC Update();

  void STORM_REFL_FUNC SetJoinCode(uint32_t join_code);

  void STORM_REFL_FUNC AddUser(DDSResponder & responder, DDSKey user_key);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  void STORM_REFL_FUNC ChangeReady(DDSKey user_key, bool ready);
  bool AllPlayersReady() const;
#endif

  void STORM_REFL_FUNC StartGame();
  void STORM_REFL_FUNC RequestStartGame(DDSKey user_key);

  void STORM_REFL_FUNC RandomizeTeams();
  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message, std::string title);
  void STORM_REFL_FUNC UpdateSettings(DDSKey user_key, GameInitSettings settings);
  void STORM_REFL_FUNC UpdateGameList();

  void STORM_REFL_FUNC RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key);
  void STORM_REFL_FUNC ExpireToken(DDSKey token);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);

private:

  std::vector<int> GetTeamCounts();

public:
  DDSKey m_AssignedServer = 0;
  GameInfo m_GameInfo;
  RInt m_GameCreateTime;

  std::map<DDSKey, DDSKey> m_MemberSubscriptionIds;
  std::map<DDSKey, GameToken> m_Tokens;

private:
  DDSNodeInterface m_Interface;
};
