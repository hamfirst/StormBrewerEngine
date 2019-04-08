#pragma once

#include <HurricaneDDS/DDSDataObject.h>

#include "SharedTypes.refl.h"
#include "GameServerMessages.refl.h"

enum STORM_REFL_ENUM class GameServerConnectionState
{
  kWaitingForConnection,
  kAuthenticating,
  kConnected,
};

struct GameServerConnection
{
public:
  DDS_TEMPORARY_OBJECT(false, DDSDataObjectPriority::kHigh);

  GameServerConnection(DDSNodeInterface node_interface);

  void STORM_REFL_FUNC SetRemoteHost(std::string host);
  void STORM_REFL_FUNC GotMessage(GameServerMessageType cmd, std::string data);

  void STORM_REFL_FUNC CreateGame(GameInitSettings game_creation_data);
  void STORM_REFL_FUNC DestroyGame(int game_id);
  void STORM_REFL_FUNC UserLeaveGame(int game_id, DDSKey user_key);

  void STORM_REFL_FUNC SendLaunchGame(int game_id, DDSKey user_id, DDSKey endpoint_id);
  void STORM_REFL_FUNC ExpireToken(DDSKey token);

public:

  RMergeList<RKey> m_Games;

public:

  void ConnectToEndpoint(DDSConnectionId connection_id);

  void PreDestroy();
  void PreMoveObject();

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
