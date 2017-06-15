
#include "GameClient.h"
#include "GameServer.h"

#include "Game/GameSimulation.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"

GameClientConnection::GameClientConnection(GameServer & server, uint32_t connection_id, ServerProtocol & protocol) :
  m_Server(server),
  m_ConnectionId(connection_id),
  m_Protocol(protocol),
  m_GameInstance(nullptr),
  m_GameId(0)
{
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandlePing, this);
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClientConnection::HandleJoinGame, this);
  m_Protocol.GetReceiverChannel<1>().RegisterCallback(&GameClientConnection::HandleClientDataUpdate, this);
}

void GameClientConnection::SyncState(const std::shared_ptr<GameSimulation> & sim)
{
  m_Protocol.GetSenderChannel<1>().SyncState(sim);
}

void GameClientConnection::SyncClientData(const ClientLocalData & client_data)
{
  m_Protocol.GetSenderChannel<2>().SyncState(client_data);
}

void GameClientConnection::AddToSenderList(NetMessageSenderList<SimEventBase> & list)
{
  list.AddSender(m_ConnectionId, m_Protocol.GetSenderChannel<3>());
}

void GameClientConnection::RemoveFromSenderList(NetMessageSenderList<SimEventBase> & list)
{
  list.RemoveSender(m_ConnectionId);
}

void GameClientConnection::ForceDisconnect()
{
  m_Server.DisconnectClient(m_ConnectionId);
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

void GameClientConnection::HandleJoinGame(const JoinGameMessage & request)
{
  if (m_GameInstance != nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_Server.GetGameInstanceManager().JoinPlayer(this, request);
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


