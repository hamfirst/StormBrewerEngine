#pragma once

#include "HurricaneDDS/DDSDataObject.h"

#include "LobbyShared/SharedTypes.refl.h"

#include "GameServerMessages.refl.h"

enum class STORM_REFL_ENUM GameServerConnectionState
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

  void STORM_REFL_FUNC CreateGame(const GameServerCreateGame & msg);
  void STORM_REFL_FUNC DestroyGame(const GameServerDestroyGame & msg);

  void STORM_REFL_FUNC RemoveUserFromGame(DDSKey game_id, DDSKey user_id);

#ifdef NET_USE_LOADOUT
  void STORM_REFL_FUNC ChangeUserLoadout(DDSKey game_id, DDSKey user_id, const GamePlayerLoadout & loadout);
#endif

  void STORM_REFL_FUNC NotifyTokenRedeemedSuccess(DDSKey game_id, const GameServerAuthenticateUserSuccess & msg);
  void STORM_REFL_FUNC NotifyTokenRedeemedFailure(DDSKey game_id, const GameServerAuthenticateUserFailure & msg);
  void STORM_REFL_FUNC NotifyUserDisconnected(DDSKey game_id, DDSKey user_key);
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
  std::vector<DDSKey> m_ActiveGameIds;

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
