#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientInstanceContainer.h"
#include "GameClient/GameContainer.h"

int s_BogusSendTimer = 0;

GameClientInstanceContainer::GameClientInstanceContainer(GameContainer & game_container, GameClientEventSender & event_sender, int num_local_clients, bool authority) :
  m_ReconcileFrame(0),
  m_GameContainer(game_container),
  m_EventSender(event_sender),
  m_ClientController(game_container),
  m_LevelLoader(game_container),
  m_EntitySync(game_container),
  m_ServerEventResponder(authority, this, &m_ClientController, &m_Reconciler, &m_ReconcileFrame),
  m_Loaded(false),
  m_Authority(authority),
  m_ConfirmedRemoteFrame(0),
  m_SendTimer(0),
  m_NumLocalClients(num_local_clients)
{

  m_ClientData.resize(num_local_clients);
}

GameClientInstanceContainer::~GameClientInstanceContainer()
{

}

void GameClientInstanceContainer::Load(const GameInitSettings & init_settings, uint64_t load_token)
{
  m_ClientController.PreloadLevel();
  m_InitSettings = init_settings;

  m_LevelLoader.LoadLevel(init_settings, load_token, [this, load_token](uint64_t, const Map & map) 
  {
    m_Loaded = true;
    m_Stage = std::make_unique<GameStage>(map);

    m_DefaultSim = std::make_shared<GameFullState>(m_Stage->CreateDefaultGameState());
    m_CurrentSim = m_DefaultSim;
    m_SimHistory.Push(m_CurrentSim);
  });

  m_SharedResources.Emplace(init_settings);
  m_ClientResources.Emplace(init_settings);
}

bool GameClientInstanceContainer::IsLoaded()
{
  if (m_Loaded)
  {
    return m_SharedResources->IsLoaded() && m_ClientResources->IsLoaded();
  }

  return false;
}

void GameClientInstanceContainer::Update()
{
  auto new_state = std::make_shared<GameFullState>(*m_CurrentSim.get());
  auto frame = new_state->m_InstanceData.m_FrameCount;

  auto & controller = GetGameController();

  GameLogicContainer logic_container(GetGameController(), new_state->m_InstanceData, new_state->m_ServerObjectManager, m_ServerObjectEventSystem,
    m_ServerEventResponder, GetClientController(), m_GameContainer.GetSharedGlobalResources(), GetSharedResources(), GetStage(), m_Authority, s_BogusSendTimer);

  auto remote_input_visitor = [&](int frame_count, HistoryInput & elem)
  {
    controller.ApplyInput(elem.m_PlayerIndex, logic_container, elem.m_Input);
  };

  m_RemoteInputistory.IterateElementsSince(frame).VisitElementsForCurrentTime(remote_input_visitor);

  auto local_input_visitor = [&](int frame_count, HistoryInput & elem)
  {
    if (frame_count < m_ConfirmedRemoteFrame)
    {
      return;
    }

    int player_index = m_ClientData[elem.m_PlayerIndex].m_PlayerIndex;
    if (player_index == -1)
    {
      return;
    }

    controller.ApplyInput(player_index, logic_container, elem.m_Input);
  };

  m_LocalInputistory.IterateElementsSince(frame).VisitElementsForCurrentTime(local_input_visitor);

  auto remote_event_visitor = [&](int frame_count, HistoryEvent & elem)
  {
    controller.HandleClientEvent(elem.m_PlayerIndex, logic_container, elem.m_Event.GetClassId(), elem.m_Event.GetBase());
  };

  m_RemoteEventHistory.IterateElementsSince(frame).VisitElementsForCurrentTime(remote_event_visitor);

  auto local_event_visitor = [&](int frame_count, HistoryEvent & elem)
  {
    if (frame_count < m_ConfirmedRemoteFrame)
    {
      return;
    }

    int player_index = m_ClientData[elem.m_PlayerIndex].m_PlayerIndex;
    if (player_index == -1)
    {
      return;
    }

    controller.HandleClientEvent(player_index, logic_container, elem.m_Event.GetClassId(), elem.m_Event.GetBase());
  };

  m_LocalEventHistory.IterateElementsSince(frame).VisitElementsForCurrentTime(local_event_visitor);

  auto local_data_visitor = [&](int frame_count, HistoryClientLocal & elem)
  {
    m_ClientData[elem.m_ClientIndex] = elem.m_Data;
  };

  m_ClientLocalHistory.IterateElementsSince(frame).VisitElementsForCurrentTime(local_data_visitor);

  auto externals_visitor = [&](int frame_count, NetPolymorphic<GameNetworkExternalEvent> & elem)
  {
    controller.ProcessExternal(elem, logic_container);
  };

  m_ExternalsHistory.IterateElementsSince(frame).VisitElementsForCurrentTime(externals_visitor);

  controller.Update(logic_container);

  m_SimHistory.Push(new_state);
  m_CurrentSim = new_state;

  if (m_ReconcileFrame > 0)
  {
    m_ReconcileFrame--;
  }
  else
  {
    m_Reconciler.AdvanceFrame();
  }
}

void GameClientInstanceContainer::SyncEntities()
{
  GetEntitySync().Sync(*this);
}

void GameClientInstanceContainer::InitializeFromRemoteState(const std::shared_ptr<GameFullState> & state)
{
  m_CurrentSim = state;
  m_SimHistory.Clear();
  m_SimHistory.Push(m_CurrentSim);

  m_LocalInputistory.Clear();
  m_LocalEventHistory.Clear();
  m_RemoteInputistory.Clear();
  m_RemoteEventHistory.Clear();
  m_ClientLocalHistory.Clear();
  m_ExternalsHistory.Clear();
  m_AuthEventHistory.Clear();
}

int GameClientInstanceContainer::Rewind(int target_frame, const Optional<std::shared_ptr<GameFullState>> & state)
{
  int rewind_frames = m_CurrentSim->m_InstanceData.m_FrameCount - target_frame;
  if (rewind_frames < 0)
  {
    if (state)
    {
      while (rewind_frames < -1)
      {
        Update();
        rewind_frames++;
      }

      m_CurrentSim = state.Value();
      m_SimHistory.Push(m_CurrentSim);
    }
    else
    {
      while (rewind_frames < 0)
      {
        Update();
        rewind_frames++;
      }
    }

    return 0;
  }

  m_ReconcileFrame += rewind_frames;

  if (rewind_frames > m_SimHistory.Count())
  {
    ASSERT(state.IsValid(), "Couldn't rewind to state beyond the beginning of time");

    m_CurrentSim = state.Value();

    m_SimHistory.Clear();
    m_SimHistory.Push(state.Value());
  }
  else
  {
    m_SimHistory.Purge(rewind_frames);

    if (state)
    {
      auto ptr = m_SimHistory.Get(0);
      m_CurrentSim = state.Value();

      m_SimHistory.SetAt(state.Value(), 0);
    }
    else
    {
      m_CurrentSim = *m_SimHistory.Get(0);
    }
  }

  return rewind_frames;
}

void GameClientInstanceContainer::PurgeLocalData(int target_frame)
{
  m_ConfirmedRemoteFrame = target_frame;
}

void GameClientInstanceContainer::PurgeRemoteData(int target_frame)
{
  m_RemoteInputistory.PurgeElementsSince(target_frame);
  m_RemoteEventHistory.PurgeElementsSince(target_frame);
  m_ClientLocalHistory.PurgeElementsSince(target_frame);
  m_ExternalsHistory.PurgeElementsSince(target_frame);
  m_AuthEventHistory.PurgeElementsSince(target_frame);
}

void GameClientInstanceContainer::PushLocalInput(std::size_t client_index, const ClientInput & input, int future_frames)
{
  auto last_input = m_LocalInputistory.GetTailElement();
  if (last_input && StormReflCompare(last_input->m_Input, input))
  {
    return;
  }

  m_LocalInputistory.Push(m_CurrentSim->m_InstanceData.m_FrameCount + future_frames, HistoryInput{ (int)client_index, input });
}

void GameClientInstanceContainer::PushRemoteInput(int player_index, const ClientInput & input, int frame)
{
  m_RemoteInputistory.Push(frame, HistoryInput{ player_index, input });
}

void GameClientInstanceContainer::PushLocalEvent(std::size_t client_index, NetPolymorphic<ClientNetworkEvent> && event, int future_frames)
{
  m_LocalEventHistory.Push(m_CurrentSim->m_InstanceData.m_FrameCount + future_frames, HistoryEvent{ (int)client_index, std::move(event) });
}

void GameClientInstanceContainer::PushRemoteEvent(int player_index, NetPolymorphic<ClientNetworkEvent> && event, int frame)
{
  m_RemoteEventHistory.Push(frame, HistoryEvent{ player_index, std::move(event) });
}

void GameClientInstanceContainer::PushClientLocalDataChange(std::size_t client_index, const ClientLocalData & client_local_data, int frame)
{
  m_ClientLocalHistory.Push(frame, HistoryClientLocal{ client_index, client_local_data });
}

void GameClientInstanceContainer::PushExternalEvent(NetPolymorphic<GameNetworkExternalEvent> && event, int frame)
{
  m_ExternalsHistory.Push(frame, std::move(event));
}

void GameClientInstanceContainer::PushAuthorityEvent(NetPolymorphic<ServerAuthNetworkEvent> && event, int frame)
{
  m_AuthEventHistory.Push(frame, std::move(event));
}

void GameClientInstanceContainer::HandleLocalServerAuthorityEvent(std::size_t class_id, const void * ev)
{
  if (m_Authority == false)
  {
    return;
  }

  auto logic_container = GetLogicContainer(true);
  m_GameController.HandleAuthEvent(logic_container, class_id, ev);
  m_ClientController.HandleAuthEvent(class_id, ev);
}

GameLogicContainer GameClientInstanceContainer::GetLogicContainer(bool authority, int & send_timer)
{
  return GameLogicContainer(
    GetGameController(),
    GetFullState().m_InstanceData,
    GetFullState().m_ServerObjectManager,
    m_ServerObjectEventSystem,
    m_ServerEventResponder,
    GetClientController(),
    m_GameContainer.GetSharedGlobalResources(),
    GetSharedResources(),
    GetStage(),
    authority, send_timer);
}

GameController & GameClientInstanceContainer::GetGameController()
{
  return m_GameController;
}

GameClientEventSender & GameClientInstanceContainer::GetEventSender()
{
  return m_EventSender;
}

GameClientController & GameClientInstanceContainer::GetClientController()
{
  return m_ClientController;
}

GameClientLevelLoader & GameClientInstanceContainer::GetLevelLoader()
{
  return m_LevelLoader;
}

GameClientEntitySync & GameClientInstanceContainer::GetEntitySync()
{
  return m_EntitySync;
}

std::size_t GameClientInstanceContainer::GetNumLocalData() const
{
  return m_ClientData.size();
}

GameInitSettings & GameClientInstanceContainer::GetInitSettings()
{
  return m_InitSettings;
}

ClientLocalData & GameClientInstanceContainer::GetClientLocalData(std::size_t client_index)
{
  return m_ClientData[client_index];
}

GameFullState & GameClientInstanceContainer::GetFullState()
{
  return *m_CurrentSim.get();
}

GameFullState & GameClientInstanceContainer::GetDefaultState()
{
  return *m_DefaultSim.get();
}

GameFullState & GameClientInstanceContainer::GetHistoryState(std::size_t history_index)
{
  return *m_SimHistory.Get((int)history_index)->get();
}

GameInstanceData & GameClientInstanceContainer::GetGlobalInstanceData()
{
  return GetFullState().m_InstanceData;
}

GameSharedInstanceResources & GameClientInstanceContainer::GetSharedResources()
{
  return m_SharedResources.Value();
}

GameClientInstanceResources & GameClientInstanceContainer::GetClientResources()
{
  return m_ClientResources.Value();
}

GameStage & GameClientInstanceContainer::GetStage()
{
  return *m_Stage.get();
}
