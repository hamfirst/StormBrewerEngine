#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "ProjectSettings/ProjectZones.h"

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"
#include "LobbyConfig.h"

struct GameToken
{
  STORM_REFL;
  DDSKey m_UserKey;
};

struct GameUserJoinInfo
{
  STORM_REFL;
  DDSKey m_UserKey = 0;
  DDSKey m_EndpointId = 0;
  std::string m_Name;
  std::string m_Password;
  bool m_Observer = false;
  LobbyGameType m_IntendedType;

  UserZoneInfo m_ZoneInfo;
};

struct Game
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Game(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC InitPrivateGame(const GameInitSettings & settings, std::string password);
  void STORM_REFL_FUNC InitCasualGame(const GameInitSettings & settings);
  void STORM_REFL_FUNC InitCompetitiveGame(const GameInitSettings & settings, std::vector<DDSKey> users, int zone);

  void Init(const GameInitSettings & settings);

  void STORM_REFL_FUNC Destroy();
  void STORM_REFL_FUNC Cleanup();

  void STORM_REFL_FUNC Update();

  void STORM_REFL_FUNC SetJoinCode(uint32_t join_code);

  void STORM_REFL_FUNC AddUser(DDSResponder & responder, const GameUserJoinInfo & join_info);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  void STORM_REFL_FUNC ChangeReady(DDSKey user_key, bool ready);
  bool AllPlayersReady() const;
#endif

  void STORM_REFL_FUNC BeginCountdown();
  void STORM_REFL_FUNC StartGame();
  void STORM_REFL_FUNC RequestStartGame(DDSKey user_key);
  void STORM_REFL_FUNC RequestTeamSwitch(DDSKey requesting_user, DDSKey target_user, int team);

  void STORM_REFL_FUNC RandomizeTeams();
  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message);
  void STORM_REFL_FUNC UpdateSettings(DDSKey user_key, GameInitSettings settings);
  void STORM_REFL_FUNC UpdateGameList();

  void STORM_REFL_FUNC RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key);
  void STORM_REFL_FUNC ExpireToken(DDSKey token);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);

private:

  int FindBestZoneForPlayers();
  std::vector<int> GetTeamCounts();
  void ValidateTeams();

public:
  DDSKey m_AssignedServer = 0;
  GameInfo m_GameInfo;

  int m_GameCreateTime;
  DDSKey m_GameRandomId;

  std::vector<std::pair<GameUserJoinInfo, DDSResponderData>> m_PendingJoins;

  std::vector<DDSKey> m_LockedUsers;

  std::map<DDSKey, DDSKey> m_MemberSubscriptionIds;
  std::map<DDSKey, GameToken> m_Tokens;

  std::map<std::size_t, UserZoneInfo> m_UserZoneInfo;

  int m_ZoneIndex = -1;
  uint32_t m_RemoteIp = 0;
  uint16_t m_RemotePort = 0;

private:
  DDSNodeInterface m_Interface;
};
