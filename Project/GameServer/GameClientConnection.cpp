
#include "GameServer/GameClientConnection.h"
#include "GameServer/GameServer.h"

#include "Game/State/GameFullState.refl.meta.h"
#include "Game/NetworkEvents/GameNetworkData.refl.meta.h"
#include "Game/NetworkEvents/GameMessages.refl.meta.h"

GameClientConnection::GameClientConnection(GameServer & server, uint32_t connection_id, ServerProtocol & protocol) :
  m_Server(server),
  m_ConnectionId(connection_id),
  m_Protocol(protocol),
  m_GameInstance(nullptr),
  m_GameId(0),
  m_UserId(0),
  m_GotJoin(false)
{
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandlePing, this);
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandleJoinServer, this);
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandleFinishLoading, this);
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandleTextChat, this);

#if NET_MODE == NET_MODE_GGPO
  m_Protocol.GetReceiverChannel<1>().RegisterCallback(&GameClientConnection::HandleClientDataUpdate, this);
#else
  m_Protocol.GetReceiverChannel<1>().RegisterGenericCallback(&GameClientConnection::HandleClientEvent, this);
  m_Protocol.GetReceiverChannel<2>().RegisterCallback(&GameClientConnection::HandleClientDataUpdate, this);
#endif
}

void GameClientConnection::SyncLoadingState(const GameStateLoading & state)
{
#if NET_MODE == NET_MODE_GGPO
  m_Protocol.GetSenderChannel<1>().SendMessage(state);
#endif
}

#if NET_MODE == NET_MODE_GGPO
void GameClientConnection::SyncGameState(const GameGGPOServerGameState & state)
{
  m_Protocol.GetSenderChannel<1>().SendMessage(state);
}
#else
void GameClientConnection::SyncState(const GameFullState & sim)
{
  m_Protocol.GetSenderChannel<3>().SyncState(sim);
}

void GameClientConnection::SyncClientData(const ClientLocalData & client_data)
{
  m_Protocol.GetSenderChannel<4>().SyncState(client_data);
}

void GameClientConnection::SendGlobalEvent(std::size_t class_id, const void * event_ptr)
{
  m_Protocol.GetSenderChannel<1>().SendMessage(class_id, event_ptr);
}

void GameClientConnection::SendEntityEvent(std::size_t class_id, const void * event_ptr)
{
  m_Protocol.GetSenderChannel<2>().SendMessage(class_id, event_ptr);
}
#endif

void GameClientConnection::SendLoadLevel(const LoadLevelMessage & load_msg)
{
  m_Protocol.GetSenderChannel<0>().SendMessage(load_msg);
}

void GameClientConnection::SendTextChat(const GotTextChatMessage & text_msg)
{
  m_Protocol.GetSenderChannel<0>().SendMessage(text_msg);
}

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
void GameClientConnection::SendDeliberateSystemSync(void * data, int type_index)
{
  m_Protocol.GetSenderChannel<2>().SendMessage(type_index, data);
}
#endif

void GameClientConnection::ForceDisconnect()
{
  printf("Forcing user disconnected\n");
  RemoveFromGame();
  m_Server.DisconnectClient(m_ConnectionId);
}

void GameClientConnection::RemoveFromGame()
{
  if (m_GameInstance)
  {
    m_Server.GetGameInstanceManager().RemovePlayer(this);
    m_GameInstance = nullptr;
  }
}

GameInstance * GameClientConnection::GetGameInstance()
{
  return m_GameInstance;
}

uint64_t GameClientConnection::GetGameId()
{
  return m_GameId;
}

void GameClientConnection::HandlePing(const PingMessage & request)
{
  m_Protocol.GetSenderChannel<0>().SendMessage(PongMessage{});
}

void GameClientConnection::HandleJoinServer(const JoinServerMessage & request)
{
  printf("Got join server\n");
  if(m_GameInstance || m_GotJoin)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_Server.ValidateUser(this, request);
  m_GotJoin = true;
}

void GameClientConnection::HandleFinishLoading(const FinishLoadingMessage & request)
{
  printf("Got finish loading\n");
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->HandlePlayerLoaded(this, request);
}

void GameClientConnection::HandleTextChat(const SendTextChatMessage &request)
{
  printf("Got text chat\n");
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->HandleTextChat(this, request);
}

#if NET_MODE == NET_MODE_GGPO

void GameClientConnection::HandleClientDataUpdate(GameGGPOClientUpdate && update_data)
{
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->UpdatePlayer(this, update_data);
}

#else

void GameClientConnection::HandleClientEvent(std::size_t class_id, void * event_ptr)
{
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->HandleClientEvent(this, class_id, event_ptr);
}

void GameClientConnection::HandleClientDataUpdate(ClientAuthData && client_data)
{
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->UpdatePlayer(this, client_data);
}
#endif
