#include "GameClient/GameClientCommon.h"

#include "Foundation/Time/FrameClock.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Audio/AudioManager.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"
#include "Game/GameProtocol.h"
#include "Game/Systems/GameDeliberateSyncSystemList.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

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
  m_LastAckFrame = 0;
  m_LastServerFrame = 0;
  m_FrameSkip = 0;
#endif

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  m_InitialDeliberateSystemSync = std::make_unique<bool[]>(std::tuple_size<GameDeliberateSyncSystemListType>::value);
#endif
}

void GameNetworkClient::Update()
{
  ClientBase::Update();

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
      m_SendTimer = cur_time + 0.05;
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

bool GameNetworkClient::SkipUpdate()
{
  if (m_State != ClientConnectionState::kConnected)
  {
    return false;
  }

  if (m_FrameSkip > 2)
  {
    m_FrameSkip -= 2;
    return true;
  }

  return false;
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

  auto future_frames = GetFutureFrames();

  m_InstanceContainer->PushLocalInput(0, input, future_frames);

#endif

  if (send_immediate)
  {
    m_SendTimer = 0;
  }
}

NullOptPtr<GameClientInstanceContainer> GameNetworkClient::GetClientInstanceData()
{
  return m_InstanceContainer.get();
}

NullOptPtr<const GameStateStaging> GameNetworkClient::GetStagingState() const
{
  return m_StagingState.GetPtr();
}

NullOptPtr<const GameStateLoading> GameNetworkClient::GetLoadingState() const
{
  return m_LoadingState.GetPtr();
}

std::unique_ptr<GameClientInstanceContainer> GameNetworkClient::ConvertToOffline()
{
  Disconnect();
  m_State = ClientConnectionState::kDisconnected;

  auto old_instance_container = std::move(m_InstanceContainer);

  m_FinalizedLoad = false;
  m_LastPingSent = 0;
  m_Ping = 0;
  m_LastAckFrame = 0;
  m_LastServerFrame = 0;

  return old_instance_container;
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
  m_LoadingInstanceContainer = std::make_unique<GameClientInstanceContainer>(m_GameContainer, *this, 1, false);
  m_LoadingInstanceContainer->Load(load.m_Settings, load.m_LoadToken);
  m_FinalizedLoad = false;

  m_LoadToken = load.m_LoadToken;
}

void GameNetworkClient::HandleStagingUpdate(const GameStateStaging & state)
{
  m_State = ClientConnectionState::kStaging;
  m_StagingState = state;
  m_LoadingState.Clear();
}

void GameNetworkClient::HandleLoadingUpdate(const GameStateLoading & state)
{
  m_State = ClientConnectionState::kLoading;
  m_StagingState.Clear();
  m_LoadingState = state;
}

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
void GameNetworkClient::HandleDeliberateSystemSync(std::size_t type_index, void * data_ptr)
{
  m_InitialDeliberateSystemSync[type_index] = true;
  GameClientInstanceContainer * inst = (m_State != ClientConnectionState::kConnected ? m_LoadingInstanceContainer.get() : m_InstanceContainer.get());

  inst->SyncDeliberateSyncSystem(type_index, data_ptr);
}
#endif

#if NET_MODE == NET_MODE_GGPO
void GameNetworkClient::HandleSimUpdate(GameGGPOServerGameState && game_state)
{
#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  if (m_State != ClientConnectionState::kConnected)
  {
    auto size = std::tuple_size<GameDeliberateSyncSystemListType>::value;
    for (std::size_t index = 0; index < size; ++index)
    {
      if (m_InitialDeliberateSystemSync[index] == false)
      {
        return;
      }
    }
  }
#endif

  m_LastAckFrame = game_state.m_AckFrame;
  if (m_State != ClientConnectionState::kConnected)
  {
    if (m_FinalizedLoad == false)
    {
      return;
    }

    m_LoadingState.Clear();
    m_StagingState.Clear();

    m_InstanceContainer = std::move(m_LoadingInstanceContainer);
    m_InstanceContainer->InitializeFromRemoteState(std::make_shared<GameFullState>(*game_state.m_State.get()));
    m_FinalizedLoad = false;

    m_State = ClientConnectionState::kConnected;
  }

  auto current_frame = m_InstanceContainer->GetGlobalInstanceData().m_FrameCount;

#ifdef NET_SYNC_OLD_STATE
  auto history_frame = game_state.m_ServerFrame - NET_SYNC_HISTORY_FRAMES;

  if (current_frame > history_frame)
  {
    m_FrameSkip += current_frame - history_frame;
  }

#else
  auto dest_frame = std::max(game_state.m_ServerFrame, current_frame);

  if (current_frame > game_state.m_ServerFrame)
  {
    m_FrameSkip += current_frame - game_state.m_ServerFrame;
  }

#endif

  auto frames_to_rewind = current_frame - game_state.m_State->m_InstanceData.m_FrameCount;

  m_LastServerFrame = game_state.m_ServerFrame;

  m_InstanceContainer->Rewind(game_state.m_State->m_InstanceData.m_FrameCount, std::make_shared<GameFullState>(*game_state.m_State.get()));
  m_InstanceContainer->PurgeLocalData(game_state.m_AckFrame);
  m_InstanceContainer->PurgeRemoteData(game_state.m_EventStartFrame);

  if (game_state.m_Inputs)
  {
    for (auto & elem : game_state.m_Inputs.Value())
    {
      m_InstanceContainer->PushRemoteInput(elem.m_PlayerIndex, elem.m_Input, elem.m_Frame);
    }
  }

  if (game_state.m_Events)
  {
    for (auto & elem : game_state.m_Events.Value())
    {
      m_InstanceContainer->PushRemoteEvent(elem.m_PlayerIndex, std::move(elem.m_Event), elem.m_Frame);
    }
  }

  if (game_state.m_LocalData)
  {
    for (auto & elem : game_state.m_LocalData.Value())
    {
      m_InstanceContainer->PushClientLocalDataChange(0, elem.m_Data, elem.m_Frame);
    }
  }

  if (game_state.m_Externals)
  {
    for (auto & elem : game_state.m_Externals.Value())
    {
      m_InstanceContainer->PushExternalEvent(std::move(elem.m_Event), elem.m_Frame);
    }
  }

  if (game_state.m_ServerAuthEvents)
  {
    for (auto & elem : game_state.m_ServerAuthEvents.Value())
    {
      m_InstanceContainer->GetClientController().HandleAuthEvent(elem.m_Event.GetClassId(), elem.m_Event.GetBase());
      m_InstanceContainer->PushAuthorityEvent(std::move(elem.m_Event), elem.m_Frame);
    }
  }

  for(int index = 0; index < frames_to_rewind; ++index)
  {
    m_InstanceContainer->Update();
  }

  m_InstanceContainer->SyncEntities();
}

#else

void GameNetworkClient::HandleSimUpdate(const GameFullState & sim)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_InstanceContainer->GetFullState() = sim;
  if (m_GotInitialSim == false)
  {
    m_GotInitialSim = true;
    CheckFinalizeConnect();
  }

  m_InstanceContainer->GetEntitySync().Sync(m_InstanceContainer->GetFullState().m_ServerObjectManager);
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
  update.m_ClientFrame = m_InstanceContainer->GetGlobalInstanceData().m_FrameCount;

  auto input_visitor = [&](int frame, ClientInput & elem)
  {
    if (update.m_Inputs == false)
    {
      update.m_Inputs.Emplace();
    }

    update.m_Inputs->emplace_back(ClientAuthData{ frame, elem });
  };

  m_InstanceContainer->VisitLocalInput(m_LastAckFrame, input_visitor);

  static int send = 0;
  send++;
  auto event_visitor = [&](int frame, NetPolymorphic<ClientNetworkEvent> & elem)
  {
    if (update.m_Events == false)
    {
      update.m_Events.Emplace();
    }

    update.m_Events->emplace_back(GameHistoryClientEvent{ frame, elem });
  };

  m_InstanceContainer->VisitLocalEvents(m_LastAckFrame, event_visitor);

  m_Protocol->GetSenderChannel<1>().SyncState(update);
#else
  m_Protocol->GetSenderChannel<2>().SyncState(m_InstanceContainer->GetClientAuthData(0));
#endif
}

void GameNetworkClient::SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index)
{
#if NET_MODE == NET_MODE_GGPO
  auto future_frames = GetFutureFrames();
  m_InstanceContainer->PushLocalEvent(0, NetPolymorphic<ClientNetworkEvent>(class_id, event_ptr), future_frames);

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

#ifdef DELIBERATE_SYNC_SYSTEM_LIST
  m_Protocol->GetReceiverChannel<2>().RegisterGenericCallback(&GameNetworkClient::HandleDeliberateSystemSync, this);
#endif

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

#ifdef NET_SYNC_OLD_STATE
  future_frames += NET_SYNC_HISTORY_FRAMES;
#endif

  return future_frames;
}
#endif