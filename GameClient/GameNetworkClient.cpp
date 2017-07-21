
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

GameNetworkClient::GameNetworkClient(GameContainer & game, const GameNetworkClientInitSettings & init_settings) :
  ClientBase(&m_Backend),

#ifdef NET_USE_WEBRTC
  m_Backend(this, init_settings.m_RemoteHost, init_settings.m_RemotePort, init_settings.m_Fingerprint.data(), NetGetProtocolPipeModes(ServerProtocolDef{}), NetGetProtocolPipeModes(ClientProtocolDef{})),
#else
  m_Backend(this, init_settings.m_RemoteHost, init_settings.m_RemotePort),
#endif

  m_GameContainer(game),
  m_InstanceContainer(std::make_unique<GameClientInstanceContainer>(game)),
  m_InitSettings(init_settings),
  m_LastPingSent(0),
  m_Ping(0)
{
}

void GameNetworkClient::Update()
{
  if (m_GotInitialSim)
  {
    m_InstanceContainer->Update();
  }

  ClientBase::Update();

  if (m_State == ClientConnectionState::kConnected && m_Loaded)
  {
    double cur_time = GetTimeSeconds();
    if (m_SendTimer <= cur_time)
    {
      m_SendTimer = cur_time + 0.12;
      m_Protocol->GetSenderChannel<2>().SyncState(m_InstanceContainer->GetClientAuthData());

      if (cur_time - m_LastPingSent > 5)
      {
        SendPing();
      }
    }
  }

  if (m_State == ClientConnectionState::kLoading && m_InstanceContainer->IsLoaded())
  {
    m_State = ClientConnectionState::kWaitingForInitialSync;

    m_Loading = false;
    m_Loaded = true;

    FinishLoadingMessage load_msg;
    load_msg.m_LoadToken = m_LoadToken;

    m_Protocol->GetSenderChannel<0>().SendMessage(load_msg);
    m_Protocol->GetReceiverChannel<3>().SetDefault(&m_InstanceContainer->GetDefaultSim());

    CheckFinalizeConnect();
  }
}

ClientConnectionState GameNetworkClient::GetConnectionState()
{
  return m_State;
}

void GameNetworkClient::SendJoinGame()
{
  JoinGameMessage join_msg = {};
  join_msg.m_UserName = m_InitSettings.m_UserName;

  m_Protocol->GetSenderChannel<0>().SendMessage(join_msg);
}

void GameNetworkClient::UpdateInput(ClientInput & input, bool send_immediate)
{
#if NET_MODE == NET_MODE_GGPO
  int future_frames = (int)(m_Ping / 0.020f) + 3;
  if (future_frames >= kNumFutureFrames)
  {
    future_frames = kNumFutureFrames - 1;
  }

  m_ClientAuthData.m_Frame = m_Sim.m_FrameCount + future_frames;
  m_ClientAuthData.m_Input = input;

  for (int index = m_ClientAuthData.m_Frame - m_FutureFrameBase; index < kNumFutureFrames; ++index)
  {
    m_FutureInput[index] = input;
  }
#else
  m_InstanceContainer->GetClientAuthData().m_Input = input;
#endif

  if (send_immediate)
  {
    m_SendTimer = 0;
  }
}

ClientLocalData & GameNetworkClient::GetLocalData()
{
  return m_InstanceContainer->GetClientData();
}

ClientInput GameNetworkClient::GetNextInput()
{
#if NET_MODE == NET_MODE_GGPO
  if (m_FutureFrameBase > m_Sim.m_FrameCount)
  {
    return{};
  }

  if (m_Sim.m_FrameCount - m_FutureFrameBase > kNumFutureFrames)
  {
    return{};
  }

  return m_FutureInput[m_Sim.m_FrameCount - m_FutureFrameBase];
#else
  return m_InstanceContainer->GetClientAuthData().m_Input;
#endif
}

NullOptPtr<GameClientInstanceData> GameNetworkClient::GetClientInstanceData()
{
  return m_ClientInstanceData.GetPtr();
}

std::unique_ptr<GameClientInstanceContainer> GameNetworkClient::ConvertToOffline()
{
  Disconnect();
  m_State = ClientConnectionState::kDisconnected;

  m_Loading = false;
  m_Loaded = false;
  m_GotInitialSim = false;
  m_GotInitialClientData = false;
  m_GotInitialPing = false;

  auto old_instance_container = std::move(m_InstanceContainer);
  m_InstanceContainer = std::make_unique<GameClientInstanceContainer>(m_GameContainer);
  m_LastPingSent = 0;
  m_Ping = 0;

  return old_instance_container;
}

void GameNetworkClient::CheckFinalizeConnect()
{
  if (m_GotInitialClientData && m_GotInitialSim && m_GotInitialPing && m_State == ClientConnectionState::kWaitingForInitialSync)
  {
    m_State = ClientConnectionState::kConnected;
    m_SendTimer = GetTimeSeconds();

    m_InstanceContainer->GetClientController().Connected();
    m_ClientInstanceData.Emplace(m_InstanceContainer->GetInstanceData(*this));
  }
}

void GameNetworkClient::HandlePong(const PongMessage & msg)
{
  m_Ping = GetTimeSeconds() - m_LastPingSent;

  if (m_GotInitialPing == false)
  {
    m_GotInitialPing = true;
    CheckFinalizeConnect();
  }
}

void GameNetworkClient::HandleLoadLevel(const LoadLevelMessage & load)
{
  m_State = ClientConnectionState::kLoading;

  m_Loading = true;
  m_Loaded = false;

  m_GotInitialSim = false;
  m_GotInitialClientData = false;

  m_Protocol->GetReceiverChannel<3>().SetDefault(nullptr);
  m_InstanceContainer->Load(load.m_Settings, load.m_LoadToken);
  m_LoadToken = load.m_LoadToken;
}

void GameNetworkClient::HandleSimUpdate(const GameFullState & sim)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_InstanceContainer->GetSim() = sim;
  if (m_GotInitialSim == false)
  {
    m_GotInitialSim = true;
    CheckFinalizeConnect();
  }

  m_InstanceContainer->GetEntitySync().Sync(m_InstanceContainer->GetSim().m_ServerObjectManager);
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

void GameNetworkClient::HandleClientDataUpdate(ClientLocalData && client_data)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_InstanceContainer->GetClientData() = client_data;
  if (m_GotInitialClientData == false)
  {
    m_GotInitialClientData = true;
    CheckFinalizeConnect();
  }
}

void GameNetworkClient::SendPing()
{
  m_LastPingSent = GetTimeSeconds();
  m_Protocol->GetSenderChannel<0>().SendMessage(PingMessage{});
}

void GameNetworkClient::SendClientEvent(std::size_t class_id, const void * event_ptr)
{
  m_Protocol->GetSenderChannel<1>().SendMessage(class_id, event_ptr);
}

void GameNetworkClient::InitConnection(ProtocolType & protocol)
{
  m_Protocol = &protocol;

  m_State = ClientConnectionState::kJoining;

  m_Protocol->GetReceiverChannel<0>().RegisterCallback(&GameNetworkClient::HandlePong, this);
  m_Protocol->GetReceiverChannel<0>().RegisterCallback(&GameNetworkClient::HandleLoadLevel, this);
  m_Protocol->GetReceiverChannel<1>().RegisterGenericCallback(&GameNetworkClient::HandleGlobalEvent, this);
  m_Protocol->GetReceiverChannel<2>().RegisterGenericCallback(&GameNetworkClient::HandleEntityEvent, this);
  m_Protocol->GetReceiverChannel<3>().RegisterCallback(&GameNetworkClient::HandleSimUpdate, this);
  m_Protocol->GetReceiverChannel<4>().RegisterCallback(&GameNetworkClient::HandleClientDataUpdate, this);

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
  m_InstanceContainer->GetClientController().Disconnected();
}
