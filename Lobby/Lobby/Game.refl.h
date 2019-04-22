#pragma once

#include <HurricaneDDS/DDSDataObject.h>
#include <HurricaneDDS/DDSConnectionId.h>

#include "ProjectSettings/ProjectZones.h"

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"
#include "LobbyConfig.h"

struct GameUserJoinInfo
{
  STORM_REFL;
  DDSKey m_UserKey = 0;
  DDSKey m_EndpointId = 0;

  std::string m_Name;

#ifdef ENABLE_SQUADS
  std::string m_SquadTag;
#endif

  int m_AdminLevel = 0;
  int m_Icon = 0;
  int m_Title = 0;
  int m_Celebration = 0;

  std::string m_Password;

  bool m_Observer = false;
  LobbyGameType m_IntendedType;

  UserZoneInfo m_ZoneInfo;
};

struct GameUserPrivateInfo
{
  STORM_REFL;

  DDSKey m_EndpointId = 0;
  DDSKey m_SubscriptionId = 0;
  DDSKey m_Token = 0;
  time_t m_TokenAssigned = 0;
  UserZoneInfo m_UserZoneInfo;
};

struct GeneratedGameUser
{
  STORM_REFL;
  DDSKey m_UserId = 0;
  DDSKey m_EndpointId = 0;
};

struct GeneratedGame
{
  STORM_REFL;
  std::vector<GeneratedGameUser> m_Users[kMaxTeams];
};

struct Game
{
  DDS_TEMPORARY_OBJECT(true, DDSDataObjectPriority::kLow);

  Game(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC InitPrivateGame(const GameInitSettings & settings, std::string password);
  void STORM_REFL_FUNC InitCasualGame(const GameInitSettings & settings, int zone);
  void STORM_REFL_FUNC InitCompetitiveGame(const GameInitSettings & settings, const GeneratedGame & game, int zone);

  void Init(const GameInitSettings & settings);
  void Update();

  void STORM_REFL_FUNC Cleanup();

  void Reset();

  void STORM_REFL_FUNC SetJoinCode(uint32_t join_code);
  void STORM_REFL_FUNC AssignGameServer(DDSKey server_id, const std::string & server_ip, int port);

  void STORM_REFL_FUNC AddUser(DDSResponder & responder, const GameUserJoinInfo & join_info);
  void STORM_REFL_FUNC RemoveUser(DDSKey user_key);

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  void STORM_REFL_FUNC ChangeReady(DDSKey user_key, bool ready);
  bool AllPlayersReady() const;
#endif

  void BeginCountdown();
  void StartGame();
  void STORM_REFL_FUNC RequestReconnect(DDSKey user_key, DDSKey endpoint_id);
  void STORM_REFL_FUNC RequestStartGame(DDSKey user_key);
  void STORM_REFL_FUNC RequestTeamSwitch(DDSKey requesting_user, DDSKey target_user, int team);

  void RandomizeTeams();
  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message);
  void STORM_REFL_FUNC UpdateSettings(DDSKey user_key, GameInitSettings settings);
  void UpdateGameList();

  void STORM_REFL_FUNC RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);
  void STORM_REFL_FUNC HandleUserQuitGame(DDSKey user_key, bool ban);
  void STORM_REFL_FUNC HandleGameComplete();
  void STORM_REFL_FUNC HandleServerDisconnected();

private:

  int FindBestZoneForPlayers();
  std::vector<int> GetTeamCounts();
  void ValidateTeams();
  void LaunchGameForUser(DDSKey user_id, GameUserPrivateInfo & info);

public:
  DDSKey m_AssignedServer = 0;
  time_t m_InitTime = 0;

  GameInfo m_GameInfo;

  time_t m_GameCreateTime = 0;
  time_t m_GameEndTime = 0;
  DDSKey m_GameRandomId = 0;

  std::vector<std::pair<GameUserJoinInfo, DDSResponderData>> m_PendingJoins;

  GeneratedGame m_CompetitiveGameInfo;
  std::map<DDSKey, GameUserPrivateInfo> m_UserPrivateInfo;

  int m_ZoneIndex = -1;
  std::string m_ServerIp;
  int m_ServerPort;

private:
  DDSNodeInterface m_Interface;
};
