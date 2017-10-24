#pragma once

#include <StormNet/NetClient.h>
#include <StormNet/NetTransmitterReplayStream.h>

#include "Game/GameProtocol.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameSharedInstanceResources.h"
#include "Game/GameEventReconciler.h"

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
#include "GameClient/GameClientInstanceContainer.h"

#include "Engine/Window/Window.h"

#include "Foundation/HistoryList/HistoryList.h"

using ClientBase = NetClient<ServerProtocolDef, ClientProtocolDef>;

enum class ClientConnectionState
{
  kConnecting,
  kJoining,
  kStaging,
  kLoading,
  kConnected,
  kDisconnected,
};

class RenderUtil;
class RenderState;
class GameState;


struct GameNetworkClientInitSettings
{
  //const char * m_RemoteHost = "52.161.102.44";
  const char * m_RemoteHost = "192.168.56.1";

  int m_RemotePort = 47816;
  std::string m_UserName = "User";
  std::string m_Fingerprint = "78:0A:DC:3D:8D:75:D6:A8:D3:93:E9:2D:3C:78:6C:7E:E8:DB:A5:7F:7F:FD:3E:4F:09:05:93:7E:6D:60:15:67";
};

class GameNetworkClient : public ClientBase, public GameClientEventSender
{
public:
  GameNetworkClient(GameContainer & game);

  virtual void Update() override;
  bool SkipUpdate();

  ClientConnectionState GetConnectionState();

  void SendJoinGame();

  void UpdateInput(ClientInput && input, bool send_immediate);
  NullOptPtr<GameClientInstanceContainer> GetClientInstanceData();

  NullOptPtr<const GameStateStaging> GetStagingState() const;
  NullOptPtr<const GameStateLoading> GetLoadingState() const;

  std::unique_ptr<GameClientInstanceContainer> ConvertToOffline();
  void FinalizeLevelLoad();


private:

  void HandlePong(const PongMessage & msg);
  void HandleLoadLevel(const LoadLevelMessage & load);

  void HandleStagingUpdate(const GameStateStaging & state);
  void HandleLoadingUpdate(const GameStateLoading & state);

#if NET_MODE == NET_MODE_GGPO
  void HandleSimUpdate(GameGGPOServerGameState && game_state);
#else
  void HandleSimUpdate(const GameFullState & sim);
  void HandleClientDataUpdate(ClientLocalData && client_data);

  void HandleGlobalEvent(std::size_t event_class_id, void * event_ptr);
  void HandleEntityEvent(std::size_t event_class_id, void * event_ptr);
#endif

  void SendPing();
  void SendClientUpdate();

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) override;

  virtual void InitConnection(ProtocolType & protocol) override;
  virtual void ConnectionFailed() override;
  virtual void Disconnected() override;

#if NET_MODE == NET_MODE_GGPO
  int GetFutureFrames();
#endif

private:

  GameNetClientBackend m_Backend;
  ClientConnectionState m_State = ClientConnectionState::kConnecting;

  GameContainer & m_GameContainer;
  Optional<GameStateStaging> m_StagingState;
  Optional<GameStateLoading> m_LoadingState;

  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientInstanceContainer> m_LoadingInstanceContainer;

  ProtocolType * m_Protocol = nullptr;
  uint64_t m_LoadToken;

#if NET_MODE == NET_MODE_GGPO

  Optional<GameGGPOServerGameState> m_DefaultServerUpdate;

  int m_LastAckFrame;
  int m_LastServerFrame;

  int m_FrameSkip;
#endif

  bool m_FinalizedLoad;

  double m_SendTimer;

  double m_LastPingSent;
  double m_Ping;
};
