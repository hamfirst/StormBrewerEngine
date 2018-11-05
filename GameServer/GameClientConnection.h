#pragma once


#include "Game/GameProtocol.h"
#include "Game/GameNetworkSettings.h"
#include "Game/Systems/GameDeliberateSyncSystemList.h"


class GameServer;
class GameInstance;

class GameClientConnection
{
public:
  GameClientConnection(GameServer & server, uint32_t connection_id, ServerProtocol & protocol);

  void SyncStagingState(const GameStateStaging & state);
  void SyncLoadingState(const GameStateLoading & state);

#if NET_MODE == NET_MODE_GGPO
  void SyncGameState(const GameGGPOServerGameState & state);
#else

  void SyncClientData(const ClientLocalData & client_data);
  void SendGlobalEvent(std::size_t class_id, const void * event_ptr);
  void SendEntityEvent(std::size_t class_id, const void * event_ptr);
#endif

  void SendLoadLevel(const LoadLevelMessage & load_msg);
  void SendTextChat(const GotTextChatMessage & text_msg);

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  void SendDeliberateSync(void * data, int type_index);
#endif

  void ForceDisconnect();
  void RemoveFromGame();

  GameInstance * GetGameInstance();
  uint64_t GetGameId();

private:

  void HandlePing(const PingMessage & request);
  void HandleCreatePrivateGame(const CreatePrivateGameMessage & request);
  void HandleJoinGame(const JoinGameMessage & request);
  void HandleReady(const ReadyMessage & request);
  void HandleFinishLoading(const FinishLoadingMessage & request);
  void HandleTextChat(const SendTextChatMessage & request);

#if NET_MODE == NET_MODE_GGPO

  void HandleClientDataUpdate(GameGGPOClientUpdate && update_data);

#else

  void HandleClientDataUpdate(ClientAuthData && client_data);
  void HandleClientEvent(std::size_t class_id, void * event_ptr);

#endif


private:
  friend class GameInstanceManager;

  GameServer & m_Server;

  uint32_t m_ConnectionId;
  ServerProtocol & m_Protocol;

  GameInstance * m_GameInstance;
  uint64_t m_GameId;
};


