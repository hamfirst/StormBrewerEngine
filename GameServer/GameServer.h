#pragma once

#include <StormNet/NetServerBackendEnet.h>
#include <StormNet/NetServer.h>

#include "GameServer/GameClientConnection.h"
#include "GameServer/GameInstance.h"
#include "GameServer/GameInstanceManager.h"

#include "Game/GameProtocol.h"
#include "Game/GameStageManager.h"

using ServerBase = NetServer<GameClientConnection, ServerProtocolDef, ClientProtocolDef>;

class GameServer : public ServerBase
{
public:
  GameServer(int max_clients, int port, GameStageManager & stage_manager);
  ~GameServer();

  void Update() override;

  GameInstanceManager & GetGameInstanceManager();

protected:

  virtual GameClientConnection * ConstructClient(void * client_mem, uint32_t connection_id, ProtocolType & proto) override;
  virtual void CleanupClient(GameClientConnection & client, ProtocolType & proto) override;

private:
  GameStageManager & m_StageManager;

  NetServerBackendEnet m_Backend;
  GameInstanceManager m_GameInstanceManager;
};
