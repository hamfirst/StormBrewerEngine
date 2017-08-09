#pragma once

#include <StormNet/NetClient.h>
#include <StormNet/NetTransmitterReplayStream.h>

#include "Game/GameProtocol.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameSharedInstanceResources.h"

#ifdef NET_USE_WEBRTC
#include <StormNetCustomBindings/NetClientBackendWebrtc.h>
using GameNetClientBackend = NetClientBackendWebrtc;
#else
#include <StormNet/NetClientBackendEnet.h>
using GameNetClientBackend = NetClientBackendEnet;
#endif


#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientInstanceData.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Window/Window.h"

using ClientBase = NetClient<ServerProtocolDef, ClientProtocolDef>;

enum class ClientConnectionState
{
  kConnecting,
  kJoining,
  kLoading,
  kWaitingForInitialSync,
  kDisconnected,
  kConnected,
};

class RenderUtil;
class RenderState;
class GameState;


struct GameNetworkClientInitSettings
{
  const char * m_RemoteHost = "127.0.0.1";
  int m_RemotePort = 47815;
  std::string m_UserName = "User";
  std::string m_Fingerprint = "78:0A:DC:3D:8D:75:D6:A8:D3:93:E9:2D:3C:78:6C:7E:E8:DB:A5:7F:7F:FD:3E:4F:09:05:93:7E:6D:60:15:67";
};

class GameNetworkClient : public ClientBase, public GameClientEventSender
{
public:
  GameNetworkClient(GameContainer & game, const GameNetworkClientInitSettings & init_settings);

  virtual void Update() override;

  ClientConnectionState GetConnectionState();

  void SendJoinGame();

  void UpdateInput(ClientInput & input, bool send_immediate);
  ClientLocalData & GetLocalData();
  ClientInput GetNextInput();
  NullOptPtr<GameClientInstanceData> GetClientInstanceData();

  std::unique_ptr<GameClientInstanceContainer> ConvertToOffline();
  void FinalizeMapLoad();

private:

  void CheckFinalizeConnect();

  void HandlePong(const PongMessage & msg);

  void HandleLoadLevel(const LoadLevelMessage & load);
  void HandleSimUpdate(const GameFullState & sim);
  void HandleGlobalEvent(std::size_t event_class_id, void * event_ptr);
  void HandleEntityEvent(std::size_t event_class_id, void * event_ptr);
  void HandleClientDataUpdate(ClientLocalData && client_data);

  void SendPing();

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr) override;

  virtual void InitConnection(ProtocolType & protocol) override;
  virtual void ConnectionFailed() override;
  virtual void Disconnected() override;

private:

  GameNetClientBackend m_Backend;
  ClientConnectionState m_State = ClientConnectionState::kConnecting;

  GameContainer & m_GameContainer;
  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  Optional<GameClientInstanceData> m_ClientInstanceData;

  ProtocolType * m_Protocol = nullptr;
  uint64_t m_LoadToken;

  GameNetworkClientInitSettings m_InitSettings;

#if NET_MODE == NET_MODE_GGPO
  static const int kNumFutureFrames = 128;
  int m_FutureFrameBase;
  ClientInput m_FutureInput[kNumFutureFrames];
#endif

  bool m_Loading = false;
  bool m_Loaded = false;
  bool m_GotInitialSim = false;
  bool m_GotInitialClientData = false;
  bool m_GotInitialPing = false;

  double m_SendTimer;

  double m_LastPingSent;
  double m_Ping;
};
