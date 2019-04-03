#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"

struct GameLobbySettings : public GameInitSettings
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameLobbySettings);
};

enum STORM_REFL_ENUM class GameServerConnectionState
{
  kWaitingForConnection,
  kAuthenticating,
  kConnected,
};

struct GameLobbyPlayer
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameLobbyPlayer);

  std::string m_Name;
  std::string m_Squad;
  int m_AdminLevel;
  int m_Celebration;
  bool m_NewPlayer;
  RInt m_Team;
  DDSKey m_UserId;
  DDSKey m_UserRandomId;
  DDSKey m_EndpointId;
};

struct GameLobby
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameLobby);

  DDSKey m_GameRandomKey;
  GameLobbySettings m_InstanceData;
  int m_MaxTeams;

  RString m_Creator;
  std::string m_Server;

  RBool m_Started = false;
  bool m_Competive = false;

  RMergeList<GameLobbyPlayer> m_Players;
  RString m_Score;
};

struct GameLobbyPrivateData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(GameLobbyPrivateData);

  std::string m_Password;
  std::vector<std::pair<DDSKey, int>> m_Reservations;
  
  DDSKey m_BotId = 0;
  DDSKey m_BotGameId = 0;
};

struct GameServerConnection
{
public:
  DDS_TEMPORARY_OBJECT(false, DDSDataObjectPriority::kHigh);

  GameServerConnection(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC SetRemoteHost(std::string host);
  void STORM_REFL_FUNC GotMessage(GameServerMessageType cmd, std::string data);

  void STORM_REFL_FUNC CreateGame(GamePlayerData creator_data, std::string password, GameInitSettings game_creation_data);
  void STORM_REFL_FUNC JoinUserToGame(int game_id, GamePlayerData user_data, std::string password, bool observer, bool force);
  void STORM_REFL_FUNC DestroyGame(int game_id);
  void STORM_REFL_FUNC UserSwitchTeams(int game_id, DDSKey user_key);
  void STORM_REFL_FUNC UserSetTeam(int game_id, DDSKey user_key, int team, bool force);
  void STORM_REFL_FUNC UserLeaveGame(int game_id, DDSKey user_key);
  void STORM_REFL_FUNC RandomizeTeams(int game_id);
  void STORM_REFL_FUNC KillGame(int game_id);

#ifdef ENABLE_BOTS
  void STORM_REFL_FUNC CreateBotGame(DDSKey bot_id, DDSKey bot_game_id, GameInitSettings game_creation_data, std::vector<std::tuple<DDSKey, DDSKey, int>> player_info);
#endif

  void STORM_REFL_FUNC SendChatToGame(int game_id, DDSKey user_id, std::string chat);
  void STORM_REFL_FUNC SendMessageToGame(int game_id, std::string chat);

  void STORM_REFL_FUNC StartGame(int game_id, DDSKey game_random_id, std::string creator_name);
  void STORM_REFL_FUNC SendLaunchGame(int game_id, DDSKey user_id, DDSKey endpoint_id);
  void STORM_REFL_FUNC ExpireToken(DDSKey token);
  void STORM_REFL_FUNC ExpireGame(int game_id);

  void STORM_REFL_FUNC SendHangUp();

public:

  RMergeList<GameLobby> m_GameList;
  RMergeList<GameLobbyPrivateData> m_GamePrivateData;
  std::map<DDSKey, std::tuple<std::size_t, DDSKey, DDSKey, DDSKey>> m_Tokens;

public:

  void ConnectToEndpoint(DDSConnectionId connection_id);

  void PreDestroy();
  void PreMoveObject();

  bool RedeemToken(DDSKey token, GameLobby *& game, GameLobbyPrivateData *& game_private, GameLobbyPlayer *& player);
  bool FindPlayer(DDSKey game_random_id, DDSKey user_random_id, GameLobby *& game, int & game_id, GameLobbyPlayer *& player, int & player_index);

  void UpdateGamePlayerCount(int game_id);
  void PickNewCreator(int game_id);

public:

  GameServerConnectionState m_State;
  uint64_t m_ExpectedChallengeResponse;

  std::vector<std::string> m_PendingMessages;
  std::string m_RemoteHost;
  bool m_Error;

  std::string m_ServerName;
  std::string m_ServerZone;
  std::string m_ServerResourceId;
  std::string m_ServerExternalIp;

private:

  template <typename T>
  void SendPacket(const T & t);

  void ForceDisconnect();

private:
  DDSNodeInterface m_Interface;
  std::optional<DDSConnectionId> m_ConnectionId;

  bool m_Relocating;
};
