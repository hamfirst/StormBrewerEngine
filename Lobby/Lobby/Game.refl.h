#pragma once

#include "HurricaneDDS/DDSDataObject.h"
#include "HurricaneDDS/DDSConnectionId.h"

#include "ProjectSettings/ProjectZones.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "GameServerMessages.refl.h"
#include "LobbyConfig.h"

struct GameUserJoinInfo
{
  STORM_REFL;
  DDSKey m_UserKey = 0;
  DDSKey m_EndpointId = 0;
  DDSKey m_MatchmakerRandomId = 0;

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
  int m_AssignedTeam = -1;
  LobbyGameType m_IntendedType;

  UserZoneInfo m_ZoneInfo;
};

struct GameUserPrivateInfo
{
  STORM_REFL;

  DDSKey m_EndpointId = 0;
  DDSKey m_SubscriptionId = 0;
  DDSKey m_Token = 0;
  DDSKey m_MatchmakerRandomId = 0;
  time_t m_TokenAssigned = 0;
  UserZoneInfo m_UserZoneInfo;
};

struct GeneratedGameUser
{
  STORM_REFL;
  DDSKey m_UserId = 0;
  DDSKey m_EndpointId = 0;
  DDSKey m_MatchmakerRandomId = 0;
};

struct GameModifyAction
{
  STORM_REFL;
  bool m_Join = true;
  GameUserJoinInfo m_JoinInfo;
  DDSResponderData m_ResponderData;
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
  void STORM_REFL_FUNC InitCasualGame(const GameInitSettings & settings, const GeneratedGame & game, int zone, const std::vector<int> & team_sizes);
  void STORM_REFL_FUNC InitCompetitiveGame(const GameInitSettings & settings, const GeneratedGame & game, int zone, const std::vector<int> & team_sizes);

  void Init(const GameInitSettings & settings);
  void Update();

  void Cleanup();
  void Reset();

  void STORM_REFL_FUNC RequestAddUser(DDSResponder & responder, const GameUserJoinInfo & join_info);
  void STORM_REFL_FUNC RequestRemoveUser(DDSKey user_key);

  void STORM_REFL_FUNC SetJoinCode(uint32_t join_code);
  void STORM_REFL_FUNC AssignGameServer(DDSKey server_id, const std::string & server_ip, int port);

#if defined(NET_USE_READY) || defined(NET_USE_READY_PRIVATE_GAME)
  void STORM_REFL_FUNC ChangeReady(DDSKey user_key, bool ready);
  bool AllPlayersReady() const;
#endif

  void STORM_REFL_FUNC RequestSwitchEndpoint(DDSKey user_key, DDSKey endpoint_id);
  void STORM_REFL_FUNC RequestStartGame(DDSKey user_key);
  void STORM_REFL_FUNC RequestTeamSwitch(DDSKey requesting_user, DDSKey target_user, int team);
  void STORM_REFL_FUNC RequestKickUser(DDSKey requesting_user, DDSKey target_user);

  void STORM_REFL_FUNC SendChat(DDSKey user_key, DDSKey endpoint_id, std::string message);
  void STORM_REFL_FUNC ChangeSettings(DDSKey user_key, const GameInitSettings & settings);

#ifdef NET_USE_LOADOUT
  void STORM_REFL_FUNC ChangeLoadout(DDSKey user_key, const GamePlayerLoadout & loadout);
#endif

  void STORM_REFL_FUNC RedeemToken(DDSKey user_key, DDSKey token, uint32_t response_id, DDSKey server_key);

  void STORM_REFL_FUNC HandleMemberUpdate(DDSKey user_key, std::string data);
  void STORM_REFL_FUNC HandleUserDisconnected(DDSKey user_key);
  void STORM_REFL_FUNC HandleGameComplete();
  void STORM_REFL_FUNC HandleServerDisconnected();
  void STORM_REFL_FUNC HandleAcceptingNewPlayers(bool accepting_new_players);

  void STORM_REFL_FUNC AdminDestroyGame();
  void STORM_REFL_FUNC MatchmakerDestroyGame();

private:

  bool AddUser(const GameUserJoinInfo & join_info);
  void RemoveUser(DDSKey user_key);

  void BeginCountdown();
  void StartGame();
  void AbandonGame();

  void RandomizeTeams();
  void UpdateGameList();


  int FindBestZoneForPlayers();
  std::vector<int> GetTeamCounts() const;
  std::vector<int> GetMaxTeamCounts() const;
  void ValidateTeams();
  void UpdateTeamSizes();
  bool FindUserInGeneratedGame(DDSKey user_id, bool remove_if_found, int & out_team);
  bool AllGeneratedUsersConnected();
  void LaunchGameForUser(DDSKey user_id, GameUserPrivateInfo & info);

public:
  DDSKey m_AssignedServer = 0;
  time_t m_InitTime = 0;

  std::vector<int> m_TeamSizeOverrides;
  GameInfo m_GameInfo;

  time_t m_GameCreateTime = 0;
  time_t m_GameEndTime = 0;
  DDSKey m_GameRandomId = 0;

  std::vector<GameModifyAction> m_PendingActions;

  GeneratedGame m_MatchmakerGameInfo;
  std::map<DDSKey, GameUserPrivateInfo> m_UserPrivateInfo;

  int m_ZoneIndex = -1;
  std::string m_ServerIp;
  int m_ServerPort;
  
  bool m_AcceptingNewPlayers = true;

private:
  DDSNodeInterface m_Interface;
};
