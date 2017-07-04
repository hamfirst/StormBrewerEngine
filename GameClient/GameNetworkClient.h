#pragma once

#include <StormNet/NetClient.h>
#include <StormNet/NetClientBackendEnet.h>
#include <StormNet/NetTransmitterReplayStream.h>

#include "Game/GameProtocol.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"

#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"

#include "Engine/Window/Window.h"

using ClientBase = NetClient<ServerProtocolDef, ClientProtocolDef>;

enum class ClientConnectionState
{
  kConnecting,
  kJoining,
  kLoading,
  kDisconnected,
  kConnected,
};

class RenderUtil;
class RenderState;
class GameState;

class GameNetworkClient : public ClientBase, public GameClientEventSender
{
public:
  GameNetworkClient(GameContainer & game, const char * remote_ip, int remote_port);

  virtual void Update() override;

  ClientConnectionState GetConnectionState();

  void SendJoinGame();

  void UpdateInput(ClientInput & input, bool send_immediate);
  ClientLocalData & GetLocalData();
  ClientInput GetNextInput();
  NullOptPtr<GameGlobalData> GetGlobalData();

private:

  void FinalizeConnect();

  void HandlePong(const PongMessage & msg);

  void HandleLoadLevel(const LoadLevelMessage & load);
  void HandleLevelLoadComplete(uint64_t load_token, const Map & map);
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

  NetClientBackendEnet m_Backend;
  ClientConnectionState m_State = ClientConnectionState::kConnecting;

  GameContainer & m_GameContainer;

  GameController m_GameController;
  GameClientController m_ClientController;
  GameClientLevelLoader m_LevelLoader;
  GameClientEntitySync m_EntitySync;

  GameInitSettings m_InitSettings;

  Optional<GameFullState> m_Sim;
  Optional<GameFullState> m_DefaultSim;
  std::unique_ptr<GameStage> m_Stage;

  ProtocolType * m_Protocol = nullptr;

  ClientLocalData m_ClientData;
  ClientAuthData m_ClientAuthData;

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
