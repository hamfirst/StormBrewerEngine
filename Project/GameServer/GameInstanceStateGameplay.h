#pragma once


#include "Foundation/Common.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"
#include "Foundation/HistoryList/HistoryList.h"

#include "GameShared/Systems/GameLogicSystems.h"

#include "Game/GameServerEventSender.h"
#include "Game/GameFullState.refl.h"
#include "Game/Systems/GameDeliberateSyncSystemList.h"

#include "GameServer/GameInstanceStateBase.h"

#include "Runtime/ServerObject/ServerObjectEventSystem.h"

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
  int m_InputFrame;
  int m_LastAuthCommitFrame;
  HistoryList<ClientLocalData> m_LocalDataHistory;
#endif
};

class GameInstanceStateGameplay : public GameInstanceStateBase, public GameSimulationEventCallbacks, public GameServerEventSender
{
public:
  GameInstanceStateGameplay(GameInstanceStateData & state_data, const GameStateLoading & loading_data);
  ~GameInstanceStateGameplay() override;

  bool JoinPlayer(std::size_t client_index, const GameJoinInfo & join_game) override;
  void RemovePlayer(std::size_t client_index) override;

  void Update() override;

  void HandlePlayerReady(std::size_t client_index, const ReadyMessage & msg) override;
  void HandlePlayerLoaded(std::size_t client_index, const FinishLoadingMessage & msg) override;
  void HandleTextChat(std::size_t client_index, const SendTextChatMessage & msg) override;
  void HandleChangeLoadout(std::size_t client_index, const ChangeLoadoutMessage & msg) override;

#if NET_MODE == NET_MODE_GGPO

  void ProcessExternals();
  void BatchUpdate(int frames_to_rewind, int frames_to_update);
  void ComputeMaxRewind();
  void UpdatePlayer(std::size_t client_index, GameGGPOClientUpdate & update_data) override;

  void SendAuthEvent(std::size_t class_id, const void * event_ptr) override;
  bool ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos) override;
  void BlockRewind(std::size_t connection) override;

#endif

#ifdef DELIBERATE_SYNC_SYSTEM_LIST

  void SyncDeliberateSyncSystem(int system_index) override;

#endif

protected:

  GameFullState & GetCurrentState();
  GameInstanceData & GetCurrentInstanceData();
  const GameInstanceLowFrequencyData & GetCurrentLowFrequencyData() const;
  GameLogicContainer GetLogicContainer(int history_index = 0);

  void SendPacketToPlayer(std::size_t client_id, GameInstanceStateGameplayPlayer & player);

private:

  const GameStage & m_Stage;

  int m_SendTimer = 0;
  bool m_ModifiedLowFreq = false;

  GameController m_Controller;
  GameLogicSystems m_Systems;

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  GameDeliberateSyncSystemListType m_DeliberateSyncSystemData;
  std::unique_ptr<void *[]> m_DeliberateSyncSystemDataPtrs;
#endif

  SparseList<GameInstanceStateGameplayPlayer> m_PlayerInfo;
  IdAllocator m_PlayerIdAllocator;

  std::shared_ptr<GameFullState> m_CurrentState;
  std::shared_ptr<GameInstanceLowFrequencyData> m_CurrentLowFrequencyData;

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

  int m_FramesToRewind;
  int m_FramesToUpdate;

  GameFullState m_InitialState;
  std::vector<NetPolymorphic<GameNetworkExternalEvent>> m_PendingExternals;

  int m_ReconcileFrame;
  int m_FurthestRewind;
  int m_LastAuthCommit;
  GameEventReconciler m_Reconciler;
  ServerObjectEventSystem m_ServerObjectEventSystem;

  CircularBuffer<std::shared_ptr<GameFullState>, kMaxHistoryFrames> m_SimHistory;
  CircularBuffer<std::shared_ptr<GameInstanceLowFrequencyData>, kMaxHistoryFrames> m_LowFrequencyHistory;
  HistoryList<HistoryInput> m_Inputistory;
  HistoryList<HistoryEvent> m_EventHistory;
  HistoryList<HistoryClientLocal> m_ClientLocalHistory;
  HistoryList<NetPolymorphic<GameNetworkExternalEvent>> m_ExternalsHistory;
  HistoryList<NetPolymorphic<ServerAuthNetworkEvent>> m_AuthEventHistory;

#endif
};
