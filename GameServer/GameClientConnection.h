#pragma once


#include "Game/GameProtocol.h"
#include "Game/GameNetworkSettings.h"


class GameServer;
class GameInstance;

class GameClientConnection
{
public:
  GameClientConnection(GameServer & server, uint32_t connection_id, ServerProtocol & protocol);

#if NET_MODE == NET_MODE_GGPO
  void SyncState(const std::shared_ptr<GameFullState> & sim);
#else
  void SyncState(const GameFullState & sim);
#endif
  void SendLoadLevel(const LoadLevelMessage & load_msg);
  void SyncClientData(const ClientLocalData & client_data);

  void SendGlobalEvent(std::size_t class_id, void * event_ptr);
  void SendEntityEvent(std::size_t class_id, void * event_ptr);

  void ForceDisconnect();

  GameInstance * GetGameInstance();
  uint64_t GetGameId();

private:

  void HandlePing(const PingMessage & request);
  void HandleJoinGame(const JoinGameMessage & request);
  void HandleFinishLoading(const FinishLoadingMessage & request);
  void HandleClientEvent(std::size_t class_id, void * event_ptr);

  void HandleClientDataUpdate(ClientAuthData && client_data);

private:
  friend class GameInstanceManager;

  GameServer & m_Server;

  uint32_t m_ConnectionId;
  ServerProtocol & m_Protocol;

  GameInstance * m_GameInstance;
  uint64_t m_GameId;
};


