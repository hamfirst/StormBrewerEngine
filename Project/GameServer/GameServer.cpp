
#include "Foundation/Common.h"
#include "Foundation/Random/Random.h"

#include "GameServer/GameServer.h"

#include "Game/GameFullState.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"

#include "GameShared/GameProtocol.h"

#include "LobbyServerConnection/LobbyServerConnection.h"

#include "StormNet/NetProtocolFuncs.h"


GameServer::GameServer(int max_clients, int port, GameStageManager & stage_manager, NullOptPtr<LobbyServerConnection> lobby_connection) :
  ServerBase(max_clients, &m_Backend),
  m_StageManager(stage_manager),
  m_LobbyConnection(lobby_connection),
#if NET_BACKEND == NET_BACKEND_WEBRTC
  m_Backend(this, NetServerBackendWebrtcSettings{ (uint16_t)port, (uint16_t)max_clients, "Config/localhost.key", "Config/localhost.crt", NetGetProtocolPipeModes(ServerProtocolDef{}), NetGetProtocolPipeModes(ClientProtocolDef{}) }),
#elif NET_BACKEND == NET_BACKEND_ENET
  m_Backend(this, NetServerSettingsEnet(port, 0, max_clients)),
#elif NET_BACKEND == NET_BACKEND_WEBSOCKET
  m_Backend(this, NetServerBackendWebsocketSettings{ (uint16_t)port, (uint16_t)max_clients }),
#endif
  m_GameInstanceManager(*this, stage_manager, lobby_connection)
{
  m_LobbyConnection->SetDisconnectCallback([&](uint64_t user_id, uint64_t game_id)
  {
    VisitClients([&](NotNullPtr<GameClientConnection> client_ptr)
    {
      if(client_ptr->m_UserId == user_id)
      {
        client_ptr->ForceDisconnect();
      }
    });
  });
}

GameServer::~GameServer()
{

}

void GameServer::Update()
{
  ServerBase::Update();

  if(m_LobbyConnection)
  {
    m_LobbyConnection->Update();
    
    if(m_LobbyConnected == false && m_LobbyConnection->IsConnected())
    {
      m_LobbyConnected = true;
    }
    
    if(m_LobbyConnected == true && m_LobbyConnection->IsConnected() == false)
    {
      m_WantsToQuit = true;
    }
  }
}

bool GameServer::WantsToQuit()
{
  return m_WantsToQuit;
}

int GameServer::ValidateUser(NotNullPtr<GameClientConnection> connection, const JoinServerMessage & request)
{
  if(m_LobbyConnection)
  {
    return m_LobbyConnection->RequestValidation(request, [this, connection](const Optional<GameServerAuthenticateUserSuccess> & resp)
    {
      if(resp.IsValid() == false || m_GameInstanceManager.JoinPlayer(connection, resp.Value()) == false)
      {
        connection->ForceDisconnect();
      }
    });
  }
  else
  {
    return 0;
  }
}

void GameServer::CancelUserValidation(int validation_id)
{
  if(m_LobbyConnection)
  {
    m_LobbyConnection->CancelValidation(validation_id);
  }
}

GameInstanceManager & GameServer::GetGameInstanceManager()
{
  return m_GameInstanceManager;
}

GameClientConnection * GameServer::ConstructClient(void * client_mem, uint32_t connection_id, ProtocolType & proto)
{
  auto client = new (client_mem) GameClientConnection(*this, connection_id, proto);
  return client;
}

void GameServer::CleanupClient(GameClientConnection & client, ProtocolType & proto)
{
  client.RemoveFromGame();
}
