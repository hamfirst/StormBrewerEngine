#pragma once

#include <StormNet/NetServer.h>

#include "GameShared/GameProtocol.h"
#include "GameShared/GameStageManager.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#if NET_BACKEND == NET_BACKEND_WEBRTC
#include <StormNetCustomBindings/NetServerBackendWebrtc.h>
using GameNetServerBackend = NetServerBackendWebrtc;
#elif NET_BACKEND == NET_BACKEND_ENET
#include <StormNet/NetServerBackendEnet.h>
using GameNetServerBackend = NetServerBackendEnet;
#elif NET_BACKEND == NET_BACKEND_WEBSOCKET
#include <StormNetCustomBindings/NetServerBackendWebsocket.h>
using GameNetServerBackend = NetServerBackendWebsocket;
#endif


#include "GameServer/GameClientConnection.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameInstanceManager.h"

class LobbyServerConnection;

using ServerBase = NetServer<GameClientConnection, ServerProtocolDef, ClientProtocolDef>;

class GameServer : public ServerBase
{
public:
  GameServer(int max_clients, int port, GameStageManager & stage_manager, NullOptPtr<LobbyServerConnection> lobby_connection);
  ~GameServer();

  void Update() override;

  int ValidateUser(NotNullPtr<GameClientConnection> connection, const JoinServerMessage & request);
  void CancelUserValidation(int validation_id);

  GameInstanceManager & GetGameInstanceManager();

protected:

  virtual GameClientConnection * ConstructClient(void * client_mem, uint32_t connection_id, ProtocolType & proto) override;
  virtual void CleanupClient(GameClientConnection & client, ProtocolType & proto) override;

private:
  friend class GameInstanceManager;

  GameStageManager & m_StageManager;
  NullOptPtr<LobbyServerConnection> m_LobbyConnection;

  GameNetServerBackend m_Backend;
  GameInstanceManager m_GameInstanceManager;
};
