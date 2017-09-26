#pragma once


#include "Foundation/Common.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"
#include "Foundation/HistoryList/HistoryList.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameFullState.refl.h"

#include "GameServer/GameInstanceStateBase.h"

struct GameInstanceStateGameplayPlayer
{
  int m_PlayerIndex;
  bool m_Loaded;
  uint64_t m_LoadToken;

#ifdef NET_ALLOW_OBSERVERS
  int m_ObserverIndex;
#endif

#if NET_MODE == NET_MODE_GGPO
  int m_ClientFrame;
  HistoryList<ClientLocalData> m_LocalDataHistory;
#endif
};

class GameInstanceStateGameplay : public GameInstanceStateBase, public GameSimulationEventCallbacks, public GameServerEventSender
{
public:
  GameInstanceStateGameplay(GameInstanceStateData & state_data, const GameStateLoading & loading_data, std::unique_ptr<GameSharedInstanceResources> && resources);

  virtual bool JoinPlayer(std::size_t client_index, const JoinGameMessage & join_game) override;
  virtual void RemovePlayer(std::size_t client_index) override;

  virtual void Update() override;

  virtual void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  virtual void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;

#if NET_MODE == NET_MODE_GGPO

  virtual void UpdatePlayer(std::size_t client_index, GameGGPOClientUpdate & update_data) override;

  virtual bool ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos) override;

#else

  virtual void UpdatePlayer(std::size_t client_index, ClientAuthData & update_data) override;
  virtual void HandleClientEvent(std::size_t client_index, std::size_t class_id, void * event_ptr) override;

  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr) override;
  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) override;

#endif

protected:

  GameFullState & GetCurrentState();
  GameInstanceData & GetCurrentInstanceData();
  GameLogicContainer GetLogicContainer(int history_index = 0);

  void SendPacketToPlayer(std::size_t client_id, GameInstanceStateGameplayPlayer & player);

private:

  const GameStage & m_Stage;
  std::unique_ptr<GameSharedInstanceResources> m_InstanceResources;

  int m_SendTimer;

  GameController m_Controller;
  SparseList<GameInstanceStateGameplayPlayer> m_PlayerInfo;
  IdAllocator m_PlayerIdAllocator;

  std::shared_ptr<GameFullState> m_CurrentState;

#ifdef NET_ALLOW_OBSERVERS
  IdAllocator m_ObserverIdAllocator;
#endif

#if NET_MODE == NET_MODE_GGPO

  struct HistoryInput
  {
    int m_PlayerIndex;
    ClientInput m_Input;
  };

  struct HistoryEvent
  {
    int m_PlayerIndex;
    NetPolymorphic<ClientNetworkEvent> m_Event;
  };

  struct HistoryClientLocal
  {
    int m_PlayerIndex;
    ClientLocalData m_Data;
  };

  GameFullState m_InitialState;
  std::vector<NetPolymorphic<GameNetworkExternalEvent>> m_PendingExternals;

  int m_ReconcileFrame;
  GameEventReconciler m_Reconciler;

  CircularBuffer<std::shared_ptr<GameFullState>, kMaxHistoryFrames> m_SimHistory;
  HistoryList<HistoryInput> m_Inputistory;
  HistoryList<HistoryEvent> m_EventHistory;
  HistoryList<HistoryClientLocal> m_ClientLocalHistory;
  HistoryList<NetPolymorphic<GameNetworkExternalEvent>> m_ExternalsHistory;
  HistoryList<NetPolymorphic<ServerAuthNetworkEvent>> m_AuthEventHistory;

#endif
};
