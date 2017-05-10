#pragma once


#include "Game/GameProtocol.h"


class GameServer;
class GameInstance;

struct GameSimulation;

class GameClient
{
public:
  GameClient(GameServer & server, uint32_t connection_id, ServerProtocol & protocol);

  void SyncState(const std::shared_ptr<GameSimulation> & sim);
  void SyncClientData(const ClientLocalData & client_data);
  void AddToSenderList(NetMessageSenderList<SimEventBase> & list);
  void RemoveFromSenderList(NetMessageSenderList<SimEventBase> & list);

  void ForceDisconnect();

  GameInstance * GetGameInstance();
  uint64_t GetGameId();

private:

  void HandlePing(const PingMessage & request);
  void HandleJoinGame(const JoinGameMessage & request);

  void HandleClientDataUpdate(ClientAuthData && client_data);

private:
  friend class GameInstanceManager;

  GameServer & m_Server;

  uint32_t m_ConnectionId;
  ServerProtocol & m_Protocol;

  GameInstance * m_GameInstance;
  uint64_t m_GameId;
};


