
#include "GameClient.h"
#include "GameServer.h"

#include "Game/GameSimulation.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"

GameClient::GameClient(GameServer & server, uint32_t connection_id, ServerProtocol & protocol) :
  m_Server(server),
  m_ConnectionId(connection_id),
  m_Protocol(protocol),
  m_GameInstance(nullptr),
  m_GameId(0)
{
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClient::HandlePing, this);
  m_Protocol.GetReceiverChannel<0>().RegisterCallback(&GameClient::HandleJoinGame, this);
  m_Protocol.GetReceiverChannel<1>().RegisterCallback(&GameClient::HandleClientDataUpdate, this);
}

void GameClient::SyncState(const std::shared_ptr<GameSimulation> & sim)
{
  m_Protocol.GetSenderChannel<1>().SyncState(sim);
}

void GameClient::SyncClientData(const ClientLocalData & client_data)
{
  m_Protocol.GetSenderChannel<2>().SyncState(client_data);
}

void GameClient::AddToSenderList(NetMessageSenderList<SimEventBase> & list)
{
  list.AddSender(m_ConnectionId, m_Protocol.GetSenderChannel<3>());
}

void GameClient::RemoveFromSenderList(NetMessageSenderList<SimEventBase> & list)
{
  list.RemoveSender(m_ConnectionId);
}

void GameClient::ForceDisconnect()
{
  m_Server.DisconnectClient(m_ConnectionId);
}

GameInstance * GameClient::GetGameInstance()
{
  return m_GameInstance;
}

uint64_t GameClient::GetGameId()
{
  return m_GameId;
}

void GameClient::HandlePing(const PingMessage & request)
{
  m_Protocol.GetSenderChannel<0>().SendMessage(PongMessage{});
}

void GameClient::HandleJoinGame(const JoinGameMessage & request)
{
  if (m_GameInstance != nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_Server.GetGameInstanceManager().JoinPlayer(this, request);
}

void GameClient::HandleClientDataUpdate(ClientAuthData && client_data)
{
  if (m_GameInstance == nullptr)
  {
    m_Server.DisconnectClient(m_ConnectionId);
    return;
  }

  m_GameInstance->UpdatePlayer(this, client_data);
}


