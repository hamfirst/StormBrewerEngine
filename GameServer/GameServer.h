#pragma once

#include <StormNet/NetServer.h>

#include "Game/GameProtocol.h"
#include "Game/GameStageManager.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameNetworkSettings.h"

#ifdef NET_USE_WEBRTC
#include <StormNetCustomBindings/NetServerBackendWebrtc.h>
using GameNetServerBackend = NetServerBackendWebrtc;
#else
#include <StormNet/NetServerBackendEnet.h>
using GameNetServerBackend = NetServerBackendEnet;
#endif


#include "GameServer/GameClientConnection.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameInstanceManager.h"

using ServerBase = NetServer<GameClientConnection, ServerProtocolDef, ClientProtocolDef>;

class GameServer : public ServerBase
{
public:
  GameServer(int max_clients, int port, GameStageManager & stage_manager, GameSharedGlobalResources & shared_global_resource);
  ~GameServer();

  void Update() override;

  GameInstanceManager & GetGameInstanceManager();

protected:

  virtual GameClientConnection * ConstructClient(void * client_mem, uint32_t connection_id, ProtocolType & proto) override;
  virtual void CleanupClient(GameClientConnection & client, ProtocolType & proto) override;

private:
  GameStageManager & m_StageManager;
  GameSharedGlobalResources & m_SharedGlobalResources;

  GameNetServerBackend m_Backend;
  GameInstanceManager m_GameInstanceManager;
};
