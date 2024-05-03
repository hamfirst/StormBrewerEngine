#pragma once

#include <StormNet/NetClient.h>
#include <StormNet/NetTransmitterReplayStream.h>

#include "Engine/Window/Window.h"

#include "Foundation/HistoryList/HistoryList.h"

#include "GameShared/GameProtocol.h"
#include "GameShared/GameEventReconciler.h"

#include "Game/GameController/GameController.refl.h"
#include "Game/State/GameFullState.refl.h"
#include "ProjectSettings/ProjectNetworkSettings.h"
#include "Game/Systems/GameDeliberateSyncSystemList.h"

#if NET_BACKEND == NET_BACKEND_WEBRTC
#include <StormNetCustomBindings/NetClientBackendWebrtc.h>
using GameNetClientBackend = NetClientBackendWebrtc;
#elif NET_BACKEND == NET_BACKEND_ENET
#include <StormNet/NetClientBackendEnet.h>
using GameNetClientBackend = NetClientBackendEnet;
#elif NET_BACKEND == NET_BACKEND_WEBSOCKET
#include <StormNetCustomBindings/NetClientBackendWebsocket.h>
using GameNetClientBackend = NetClientBackendWebsocket;
#endif


#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameClientInstanceContainer.h"

#include "ProjectSettings/ProjectPorts.h"


using ClientBase = NetClient<ServerProtocolDef, ClientProtocolDef>;

enum class ClientConnectionState
{
  kConnecting,
  kJoining,
  kLoading,
  kConnected,
  kDisconnected,
};

class RenderState;
class GameState;

enum class ClientConnectionIntent
{
  kRandom,
  kJoinPrivate,
  kCreatePrivate,
};

struct GameNetworkClientInitSettings
{
  const char * m_RemoteHost = "127.0.0.1";
  int m_RemotePort = DEFAULT_GAME_PORT;

  uint64_t m_UserId = 0;
  uint64_t m_GameId = 0;
  uint64_t m_JoinKey = 0;

#if NET_BACKEND == NET_BACKEND_WEBRTC
  std::string m_Fingerprint = "78:0A:DC:3D:8D:75:D6:A8:D3:93:E9:2D:3C:78:6C:7E:E8:DB:A5:7F:7F:FD:3E:4F:09:05:93:7E:6D:60:15:67";
#endif
};

struct GameNetworkClientTextData
{
  std::string m_UserName;
  std::string m_Text;
  int m_Team;
};

class GameNetworkClient : public ClientBase, public GameClientEventSender
{
public:
  explicit GameNetworkClient(GameContainer & game, const GameNetworkClientInitSettings & init_settings);

  void Update() override;
  bool SkipUpdate();

  ClientConnectionState GetConnectionState() const;
  const GameNetworkClientInitSettings & GetSettings() const;

  void UpdateInput(ClientInput && input, bool send_immediate);
  NullOptPtr<GameClientInstanceContainer> GetClientInstanceData();

  NullOptPtr<const GameStateLoading> GetLoadingState() const;

  std::unique_ptr<GameClientInstanceContainer> ConvertToOffline();
  void FinalizeLevelLoad();

  template <typename Visitor>
  void VisitTextChat(Visitor && visitor) const
  {
    for(auto itr = m_TextData.rbegin(), end = m_TextData.rend(); itr != end; ++itr)
    {
      visitor(*itr);
    }
  }

private:

  void HandlePong(const PongMessage & msg);
  void HandleLoadLevel(const LoadLevelMessage & load);
  void HandleTextMessage(const GotTextChatMessage & text);

  void HandleLoadingUpdate(const GameStateLoading & state);

#if NET_MODE == NET_MODE_GGPO
  void HandleSimUpdate(GameGGPOServerGameState && game_state);
#else
  void HandleSimUpdate(const GameFullState & sim);
  void HandleClientDataUpdate(ClientLocalData && client_data);

  void HandleGlobalEvent(std::size_t event_class_id, void * event_ptr);
  void HandleEntityEvent(std::size_t event_class_id, void * event_ptr);
#endif

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  void HandleDeliberateSystemSync(std::size_t type_index, void * data_ptr);
#endif

  void SendJoinServer();
  void SendPing();
  void SendClientUpdate();


  void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) override;

  void InitConnection(ProtocolType & protocol) override;
  void ConnectionFailed() override;
  void Disconnected() override;

#if NET_MODE == NET_MODE_GGPO
  int GetFutureFrames();
#endif

private:

  GameNetClientBackend m_Backend;
  GameNetworkClientInitSettings m_Settings;
  ClientConnectionState m_State = ClientConnectionState::kConnecting;

  GameContainer & m_GameContainer;
  Optional<GameStateLoading> m_LoadingState;

  std::unique_ptr<GameClientInstanceContainer> m_InstanceContainer;
  std::unique_ptr<GameClientInstanceContainer> m_LoadingInstanceContainer;

  ProtocolType * m_Protocol = nullptr;
  uint64_t m_LoadToken;

  std::vector<GameNetworkClientTextData> m_TextData;

#if NET_MODE == NET_MODE_GGPO

  Optional<GameGGPOServerGameState> m_DefaultServerUpdate;

  int m_LastAckFrame;
  int m_LastServerFrame;

  int m_FrameSkip;
#endif

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  std::unique_ptr<bool[]> m_InitialDeliberateSystemSync;
#endif

  bool m_FinalizedLoad;

  double m_SendTimer;

  double m_LastPingSent;
  double m_Ping;
};
