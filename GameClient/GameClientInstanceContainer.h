#pragma once

#include "Game/GameProtocol.h"
#include "Game/GameStage.h"
#include "Game/GameController.refl.h"
#include "Game/GameFullState.refl.h"
#include "Game/GameNetworkSettings.h"
#include "Game/GameLogicContainer.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameSharedInstanceResources.h"
#include "Game/GameEventReconciler.h"
#include "Game/Systems/GameLogicSystems.h"
#include "Game/Systems/GameDeliberateSyncSystemList.h"

#include "GameClient/GameClientController.refl.h"
#include "GameClient/GameClientLevelLoader.h"
#include "GameClient/GameClientEntitySync.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameClientInstanceResources.h"
#include "GameClient/GameServerEventResponder.h"

#include "Foundation/HistoryList/HistoryList.h"
#include "Foundation/CircularBuffer/CircularBuffer.h"

#include "Runtime/ServerObject/ServerObjectEventSystem.h"

extern int s_BogusSendTimer;

class GameContainer;

class GameClientInstanceContainer
{
public:

  GameClientInstanceContainer(GameContainer & game_container, GameClientEventSender & event_sender, int num_local_clients, bool authority);

  GameClientInstanceContainer(const GameClientInstanceContainer & rhs) = delete;
  GameClientInstanceContainer(GameClientInstanceContainer && rhs) = delete;

  GameClientInstanceContainer & operator = (const GameClientInstanceContainer & rhs) = delete;
  GameClientInstanceContainer & operator = (GameClientInstanceContainer && rhs) = delete;

  ~GameClientInstanceContainer();

  void Load(const GameInitSettings & init_settings, uint64_t load_token = 0);
  bool IsLoaded();

  void Update();
  void SyncEntities();
  void InitializeFromRemoteState(const std::shared_ptr<GameFullState> & state);
  int Rewind(int target_frame, const Optional<std::shared_ptr<GameFullState>> & state);
  void PurgeLocalData(int target_frame);
  void PurgeRemoteData(int target_frame);

  void PushLocalInput(std::size_t client_index, const ClientInput & input, int future_frames);
  void PushRemoteInput(int player_index, const ClientInput & input, int frame);
  void PushLocalEvent(std::size_t client_index, NetPolymorphic<ClientNetworkEvent> && event, int future_frames);
  void PushRemoteEvent(int player_index, NetPolymorphic<ClientNetworkEvent> && event, int frame);

  void PushClientLocalDataChange(std::size_t client_index, const ClientLocalData & client_local_data, int frame);
  void PushExternalEvent(NetPolymorphic<GameNetworkExternalEvent> && event, int frame);
  void PushAuthorityEvent(NetPolymorphic<ServerAuthNetworkEvent> && event, int frame);
  void HandleLocalServerAuthorityEvent(std::size_t class_id, const void * ev);

  GameLogicContainer GetLogicContainer(NullOptPtr<bool> authority = nullptr, int & send_timer = s_BogusSendTimer);

  GameController & GetGameController();
  GameClientEventSender & GetEventSender();
  GameClientController & GetClientController();
  GameClientLevelLoader & GetLevelLoader();
  GameClientEntitySync & GetEntitySync();

  GameInitSettings & GetInitSettings();
  std::size_t GetNumLocalData() const;
  ClientLocalData & GetClientLocalData(std::size_t client_index);

  GameFullState & GetFullState();
  GameFullState & GetDefaultState();
  GameFullState & GetHistoryState(std::size_t history_index);
  GameInstanceData & GetGlobalInstanceData();
  GameSharedInstanceResources & GetSharedResources();
  GameClientInstanceResources & GetClientResources();
  GameLogicSystems & GetSystems();
  GameStage & GetStage();

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  void SyncDeliberateSyncSystem(std::size_t index, void * data);
#endif

  template <typename Visitor>
  void VisitLocalInput(int since_frame, Visitor && visitor)
  {
    auto marshaler = [&](int frame, HistoryInput & elem)
    {
      visitor(frame, elem.m_Input);
    };

    m_LocalInputistory.VisitElementsSince(since_frame, marshaler);
  }

  template <typename Visitor>
  void VisitLocalEvents(int since_frame, Visitor && visitor)
  {
    auto marshaler = [&](int frame, HistoryEvent & elem)
    {
      visitor(frame, elem.m_Event);
    };

    m_LocalEventHistory.VisitElementsSince(since_frame, marshaler);
  }


private:

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
    std::size_t m_ClientIndex;
    ClientLocalData m_Data;
  };

  GameEventReconciler m_Reconciler;
  int m_ReconcileFrame;

  GameContainer & m_GameContainer;
  GameClientEventSender & m_EventSender;
  GameController m_GameController;
  Optional<GameLogicSystems> m_Systems;

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  using GameDeliberateSyncSystemCallback = void(*)(void *, void *);
  GameDeliberateSyncSystemListType m_DeliberateSyncSystemData;
  std::unique_ptr<std::pair<void *, GameDeliberateSyncSystemCallback>[]> m_DeliberateSyncSystemCallback;
#endif

  GameClientController m_ClientController;
  GameClientLevelLoader m_LevelLoader;
  GameClientEntitySync m_EntitySync;
  GameServerEventResponder m_ServerEventResponder;
  ServerObjectEventSystem m_ServerObjectEventSystem;
  bool m_Loaded;
  bool m_Authority;
  int m_ConfirmedRemoteFrame;
  int m_SendTimer;

  GameInitSettings m_InitSettings;
  std::vector<ClientLocalData> m_ClientData;
  std::size_t m_NumLocalClients;

  std::shared_ptr<GameFullState> m_CurrentSim;
  std::shared_ptr<GameFullState> m_DefaultSim;
  CircularBuffer<std::shared_ptr<GameFullState>, kMaxHistoryFrames> m_SimHistory;

  HistoryList<HistoryInput> m_LocalInputistory;
  HistoryList<HistoryEvent> m_LocalEventHistory;
  HistoryList<HistoryInput> m_RemoteInputistory;
  HistoryList<HistoryEvent> m_RemoteEventHistory;
  HistoryList<HistoryClientLocal> m_ClientLocalHistory;
  HistoryList<NetPolymorphic<GameNetworkExternalEvent>> m_ExternalsHistory;
  HistoryList<NetPolymorphic<ServerAuthNetworkEvent>> m_AuthEventHistory;

  Optional<GameSharedInstanceResources> m_SharedResources;
  Optional<GameClientInstanceResources> m_ClientResources;
  std::unique_ptr<GameStage> m_Stage;
};

