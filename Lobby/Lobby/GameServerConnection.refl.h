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

  void STORM_REFL_FUNC GotMessage(GameServerMessageType cmd, std::string data);

  void STORM_REFL_FUNC CreateGame(DDSKey game_id, const GameInitSettings & game_creation_data);
  void STORM_REFL_FUNC DestroyGame(DDSKey game_id);

  void STORM_REFL_FUNC NotifyTokenRedeemed(RKey user_key, RKey game_key, uint32_t response_id, bool success);
  void STORM_REFL_FUNC NotifyUserLeaveGame(DDSKey game_, DDSKey user_key);
  void STORM_REFL_FUNC NotifyGameEnded(DDSKey game_id);

public:

  RMergeList<RKey> m_Games;

public:

  void ConnectToEndpoint(DDSConnectionId connection_id);

  void PreDestroy();
  void PreMoveObject();

public:

  GameServerConnectionState m_State;
  GameServerInfo m_ServerInfo;

  uint64_t m_ExpectedChallengeResponse;

  std::vector<std::string> m_PendingMessages;
  std::string m_RemoteHost;
  bool m_Error;

private:

  template <typename T>
  void SendPacket(const T & t);

  void ForceDisconnect();

private:
  DDSNodeInterface m_Interface;
  std::optional<DDSConnectionId> m_ConnectionId;

  bool m_Relocating;
};
