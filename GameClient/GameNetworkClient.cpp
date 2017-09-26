
#include "Foundation/Common.h"
#include "Foundation/Time/FrameClock.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Audio/AudioManager.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"
#include "Game/GameProtocol.h"

#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameContainer.h"

#include <SDL2/SDL.h>

#include "StormNet/NetProtocolFuncs.h"

#undef SendMessage

GameNetworkClient::GameNetworkClient(GameContainer & game) :
  ClientBase(&m_Backend),

#ifdef NET_USE_WEBRTC
  m_Backend(this, game.GetNetworkInitSettings().m_RemoteHost, game.GetNetworkInitSettings().m_RemotePort, 
                  game.GetNetworkInitSettings().m_Fingerprint.data(), NetGetProtocolPipeModes(ClientProtocolDef{}), NetGetProtocolPipeModes(ServerProtocolDef{})),
#else
  m_Backend(this, game.GetNetworkInitSettings().m_RemoteHost, game.GetNetworkInitSettings().m_RemotePort),
#endif

  m_GameContainer(game),
  m_LastPingSent(0),
  m_Ping(0)
{
#if NET_MODE == NET_MODE_GGPO
  m_AckFrame = 0;
  m_LastServerFrame = 0;
  m_LastClientSendFrame = 0;
  m_ReconcileFrame = 0;
#endif
}

void GameNetworkClient::Update()
{
  m_ReconcileFrame = 0;

  ClientBase::Update();
  m_Reconciler.AdvanceFrame();

  double cur_time = GetTimeSeconds();      
  if (cur_time - m_LastPingSent > 5)
  {
    SendPing();
  }

  if (m_State == ClientConnectionState::kConnected)
  {
    m_InstanceContainer->Update();

    if (m_SendTimer <= cur_time)
    {
      m_SendTimer = cur_time + 0.12;
      SendClientUpdate();
    }
  }

  if (m_State == ClientConnectionState::kStaging)
  {
    m_StagingState->m_WaitTimer--;
  }

  if (m_LoadingInstanceContainer && m_LoadingInstanceContainer->IsLoaded() && m_FinalizedLoad == false)
  {
    FinishLoadingMessage load_msg;
    load_msg.m_LoadToken = m_LoadToken;

    m_Protocol->GetSenderChannel<0>().SendMessage(load_msg);
    m_FinalizedLoad = true;

    m_DefaultServerUpdate.Emplace();
    m_DefaultServerUpdate->m_State = std::make_shared<GameFullState>(m_LoadingInstanceContainer->GetDefaultState());
    m_Protocol->GetReceiverChannel<1>().SetDefault(&m_DefaultServerUpdate.Value());
  }
}

ClientConnectionState GameNetworkClient::GetConnectionState()
{
  return m_State;
}

void GameNetworkClient::SendJoinGame()
{
  JoinGameMessage join_msg = {};
  join_msg.m_UserName = m_GameContainer.GetNetworkInitSettings().m_UserName;

  m_Protocol->GetSenderChannel<0>().SendMessage(join_msg);
}

void GameNetworkClient::UpdateInput(ClientInput && input, bool send_immediate)
{
  if (m_InstanceContainer == nullptr)
  {
    return;
  }

#if NET_MODE == NET_MODE_GGPO

  auto last_input = m_InputHistory.GetTailElement();
  if (last_input && StormReflCompare(*last_input, input))
  {
    return;
  }

  auto future_frames = GetFutureFrames();

  auto input_frame = m_InstanceContainer->GetInstanceData().m_FrameCount + future_frames;
  m_InputHistory.Push(input_frame, std::move(input));

#endif

  if (send_immediate)
  {
    m_SendTimer = 0;
  }
}

NullOptPtr<GameClientInstanceData> GameNetworkClient::GetClientInstanceData()
{
  return m_ClientInstanceData.get();
}

NullOptPtr<const GameStateStaging> GameNetworkClient::GetStagingState() const
{
  return m_StagingState.GetPtr();
}

NullOptPtr<const GameStateLoading> GameNetworkClient::GetLoadingState() const
{
  return m_LoadingState.GetPtr();
}

std::pair<std::unique_ptr<GameClientInstanceContainer>, std::unique_ptr<GameClientInstanceData>> GameNetworkClient::ConvertToOffline()
{
  Disconnect();
  m_State = ClientConnectionState::kDisconnected;

  auto old_instance_container = std::move(m_InstanceContainer);
  auto old_instance_data = std::move(m_ClientInstanceData);

  m_FinalizedLoad = false;
  m_LastPingSent = 0;
  m_Ping = 0;
  m_AckFrame = 0;

  return std::make_pair(std::move(old_instance_container), std::move(old_instance_data));
}

void GameNetworkClient::FinalizeLevelLoad()
{
  m_InstanceContainer->GetLevelLoader().FinalizeLevel();
  m_InstanceContainer->GetEntitySync().ActivateEntities();
}

void GameNetworkClient::HandlePong(const PongMessage & msg)
{
  m_Ping = GetTimeSeconds() - m_LastPingSent;
}

void GameNetworkClient::HandleLoadLevel(const LoadLevelMessage & load)
{
  m_LoadingInstanceContainer = std::make_unique<GameClientInstanceContainer>(m_GameContainer, 1, false, &m_Reconciler, &m_ReconcileFrame);
  m_LoadingInstanceContainer->Load(load.m_Settings, load.m_LoadToken);
  m_FinalizedLoad = false;

  m_LoadToken = load.m_LoadToken;
}

void GameNetworkClient::HandleStagingUpdate(const GameStateStaging & state)
{
  m_State = ClientConnectionState::kStaging;
  m_StagingState = state;
  m_LoadingState.Clear();

  m_InputHistory.Clear();
  m_EventHistory.Clear();
}

void GameNetworkClient::HandleLoadingUpdate(const GameStateLoading & state)
{
  m_State = ClientConnectionState::kLoading;
  m_StagingState.Clear();
  m_LoadingState = state;

  m_InputHistory.Clear();
  m_EventHistory.Clear();
}

#if NET_MODE == NET_MODE_GGPO
void GameNetworkClient::HandleSimUpdate(const GameGGPOServerGameState & game_state)
{
  m_AckFrame = game_state.m_AckFrame;
  if (m_State != ClientConnectionState::kConnected)
  {
    if (m_FinalizedLoad == false)
    {
      return;
    }

    m_LoadingState.Clear();
    m_StagingState.Clear();

    m_InstanceContainer = std::move(m_LoadingInstanceContainer);
    m_FinalizedLoad = false;

    m_State = ClientConnectionState::kConnected;
    m_ClientInstanceData = std::make_unique<GameClientInstanceData>(m_InstanceContainer->GetClientInstanceData(*this));
  }

  m_InstanceContainer->GetState() = *game_state.m_State.get();
  auto start_frame = game_state.m_State->m_InstanceData.m_FrameCount;
  auto frames_to_rewind = game_state.m_ServerFrame - start_frame;

  const GameHistoryInput * input_history_cur = nullptr;
  const GameHistoryInput * input_history_end = nullptr;

  const GameHistoryEvent * event_history_cur = nullptr;
  const GameHistoryEvent * event_history_end = nullptr;

  const GameHistoryExternal * external_history_cur = nullptr;
  const GameHistoryExternal * external_history_end = nullptr;

  const GameHistoryAuthEvent * auth_history_cur = nullptr;
  const GameHistoryAuthEvent * auth_history_end = nullptr;

  const GameHistoryClientLocal * local_history_cur = nullptr;
  const GameHistoryClientLocal * local_history_end = nullptr;

  if (game_state.m_Inputs)
  {
    input_history_cur = game_state.m_Inputs.Value().data();
    input_history_end = input_history_cur + game_state.m_Inputs.Value().size();
  }

  if (game_state.m_Events)
  {
    event_history_cur = game_state.m_Events.Value().data();
    event_history_end = event_history_cur + game_state.m_Events.Value().size();
  }

  if (game_state.m_Externals)
  {
    external_history_cur = game_state.m_Externals.Value().data();
    external_history_end = external_history_cur + game_state.m_Externals.Value().size();
  }

  if (game_state.m_ServerAuthEvents)
  {
    auth_history_cur = game_state.m_ServerAuthEvents.Value().data();
    auth_history_end = auth_history_cur + game_state.m_ServerAuthEvents.Value().size();
  }
    
  if (game_state.m_LocalData)
  {
    local_history_cur = game_state.m_LocalData.Value().data();
    local_history_end = local_history_cur + game_state.m_LocalData.Value().size();

    const GameHistoryClientLocal * previous_client_local = nullptr;
    while (local_history_cur->m_Frame < start_frame)
    {
      previous_client_local = local_history_cur;
      local_history_cur++;

      if (local_history_cur == local_history_end)
      {
        break;
      }
    }

    if (previous_client_local)
    {
      m_InstanceContainer->GetClientLocalData(0) = previous_client_local->m_Data;
    }
  }


  auto input_iter = m_InputHistory.IterateElementsSince(start_frame);
  auto event_iter = m_EventHistory.IterateElementsSince(start_frame);

  int local_player_index = m_InstanceContainer->GetClientLocalData(0).m_PlayerIndex;

  while (frames_to_rewind)
  {
    m_ReconcileFrame = frames_to_rewind;

    auto logic_container = m_InstanceContainer->GetLogicContainer();
    auto cur_frame = m_InstanceContainer->GetInstanceData().m_FrameCount;

    auto & controller = m_InstanceContainer->GetGameController();

    while (local_history_cur != local_history_end && local_history_cur->m_Frame == cur_frame)
    {
      m_InstanceContainer->GetClientLocalData(0) = local_history_cur->m_Data;
      local_history_cur++;
    }

    while (input_history_cur != input_history_end && input_history_cur->m_Frame == cur_frame)
    {
      controller.ApplyInput(input_history_cur->m_PlayerIndex, logic_container, input_history_cur->m_Input);
      input_history_cur++;
    }

    if (local_player_index != -1)
    {
      auto input_visitor = [&](ClientInput & elem)
      {
        controller.ApplyInput(local_player_index, logic_container, elem);
      };

      input_iter.VisitElementsForCurrentTime(input_visitor);
      input_iter.Advance();
    }

    while (event_history_cur != event_history_end && event_history_cur->m_Frame == cur_frame)
    {
      controller.HandleClientEvent(event_history_cur->m_PlayerIndex, logic_container, 
        event_history_cur->m_Event.GetClassId(), event_history_cur->m_Event.GetBase());

      event_history_cur++;
    }

    if (local_player_index != -1)
    {
      auto event_visitor = [&](NetPolymorphic<ClientNetworkEvent> & elem)
      {
        controller.HandleClientEvent(local_player_index, logic_container, elem.GetClassId(), elem.GetBase());
      };

      event_iter.VisitElementsForCurrentTime(event_visitor);
      event_iter.Advance();
    }

    while (external_history_cur != external_history_end && external_history_cur->m_Frame == cur_frame)
    {
      controller.ProcessExternal(external_history_cur->m_Event, logic_container);
      external_history_cur++;
    }

    controller.Update(logic_container);
    frames_to_rewind--;
  }
}

#else

void GameNetworkClient::HandleSimUpdate(const GameFullState & sim)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_InstanceContainer->GetState() = sim;
  if (m_GotInitialSim == false)
  {
    m_GotInitialSim = true;
    CheckFinalizeConnect();
  }

  m_InstanceContainer->GetEntitySync().Sync(m_InstanceContainer->GetState().m_ServerObjectManager);
}

void GameNetworkClient::HandleClientDataUpdate(ClientLocalData && client_data)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_InstanceContainer->GetClientLocalData(0) = client_data;
  if (m_GotInitialClientData == false)
  {
    m_GotInitialClientData = true;
    CheckFinalizeConnect();
  }
}

void GameNetworkClient::HandleGlobalEvent(std::size_t event_class_id, void * event_ptr)
{
  m_InstanceContainer->GetClientController().HandleGlobalEvent(event_class_id, event_ptr);
}

void GameNetworkClient::HandleEntityEvent(std::size_t event_class_id, void * event_ptr)
{
  TargetNetworkEvent * target_ev = static_cast<TargetNetworkEvent *>(event_ptr);

  auto & type_info = TargetNetworkEvent::__s_TypeDatabase.GetTypeInfo(event_class_id);
  m_InstanceContainer->GetEntitySync().SendEntityEvent(target_ev->m_Target, type_info.m_TypeNameHash, event_ptr);
}

#endif

void GameNetworkClient::SendPing()
{
  if (m_Protocol)
  {
    m_LastPingSent = GetTimeSeconds();
    m_Protocol->GetSenderChannel<0>().SendMessage(PingMessage{});
  }
}

void GameNetworkClient::SendClientUpdate()
{
#if NET_MODE == NET_MODE_GGPO

  GameGGPOClientUpdate update;
  update.m_AckFrame = m_LastServerFrame;
  update.m_ClientFrame = m_InstanceContainer->GetInstanceData().m_FrameCount;

  m_LastClientSendFrame = m_InstanceContainer->GetInstanceData().m_FrameCount;
  
  auto input_visitor = [&](int frame, ClientInput & elem)
  {
    if (update.m_Inputs == false)
    {
      update.m_Inputs.Emplace();
    }

    update.m_Inputs->emplace_back(ClientAuthData{ frame, elem });
  };

  m_InputHistory.VisitElementsSince(m_AckFrame, input_visitor);

  auto event_visitor = [&](int frame, NetPolymorphic<ClientNetworkEvent> & elem)
  {
    if (update.m_Events == false)
    {
      update.m_Events.Emplace();
    }

    update.m_Events->emplace_back(GameHistoryClientEvent{ frame, elem });
  };

  m_EventHistory.VisitElementsSince(m_AckFrame, event_visitor);

  m_Protocol->GetSenderChannel<1>().SyncState(update);
#else
  m_Protocol->GetSenderChannel<2>().SyncState(m_InstanceContainer->GetClientAuthData(0));
#endif
}

void GameNetworkClient::SendClientEvent(std::size_t class_id, const void * event_ptr)
{
#if NET_MODE == NET_MODE_GGPO
  auto future_frames = GetFutureFrames();

  auto input_frame = m_InstanceContainer->GetInstanceData().m_FrameCount + future_frames;
  m_EventHistory.Push(input_frame, NetPolymorphic<ClientNetworkEvent>(class_id, event_ptr));

#else
  m_Protocol->GetSenderChannel<1>().SendMessage(class_id, event_ptr);
#endif
}

void GameNetworkClient::InitConnection(ProtocolType & protocol)
{
  m_Protocol = &protocol;

  m_State = ClientConnectionState::kJoining;

  m_Protocol->GetReceiverChannel<0>().RegisterCallback(&GameNetworkClient::HandlePong, this);
  m_Protocol->GetReceiverChannel<0>().RegisterCallback(&GameNetworkClient::HandleLoadLevel, this);

#if NET_MODE == NET_MODE_GGPO

  m_Protocol->GetReceiverChannel<1>().RegisterCallback(&GameNetworkClient::HandleStagingUpdate, this);
  m_Protocol->GetReceiverChannel<1>().RegisterCallback(&GameNetworkClient::HandleLoadingUpdate, this);
  m_Protocol->GetReceiverChannel<1>().RegisterCallback(&GameNetworkClient::HandleSimUpdate, this);

#else
  m_Protocol->GetReceiverChannel<3>().RegisterCallback(&GameNetworkClient::HandleSimUpdate, this);
  m_Protocol->GetReceiverChannel<1>().RegisterGenericCallback(&GameNetworkClient::HandleGlobalEvent, this);
  m_Protocol->GetReceiverChannel<2>().RegisterGenericCallback(&GameNetworkClient::HandleEntityEvent, this);
  m_Protocol->GetReceiverChannel<4>().RegisterCallback(&GameNetworkClient::HandleClientDataUpdate, this);
#endif

  SendPing();
  SendJoinGame();
}

void GameNetworkClient::ConnectionFailed()
{
  m_State = ClientConnectionState::kDisconnected;
}

void GameNetworkClient::Disconnected()
{
  m_State = ClientConnectionState::kDisconnected;
}

#if NET_MODE == NET_MODE_GGPO
int GameNetworkClient::GetFutureFrames()
{
#ifdef NET_MODE_GGPO_SLIDING_WINDOW

  int future_frames = (int)(m_Ping / 0.020f) + 3;
  if (future_frames >= kNumFutureFrames)
  {
    future_frames = kNumFutureFrames - 1;
  }
#else
  int future_frames = 0;
#endif

  auto frame_count = m_InstanceContainer->GetInstanceData().m_FrameCount;
  if (frame_count + future_frames < m_LastClientSendFrame)
  {
    future_frames = m_LastClientSendFrame - frame_count + 1;
  }

  return future_frames;
}
#endif