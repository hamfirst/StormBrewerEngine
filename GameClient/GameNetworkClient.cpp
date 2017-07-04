
#include "Foundation/Common.h"
#include "Foundation/Time/FrameClock.h"

#include "Engine/Text/TextManager.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Audio/AudioManager.h"

#include "Game/GameLogicContainer.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameFullState.refl.meta.h"

#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameContainer.h"

#include <SDL2/SDL.h>

GameNetworkClient::GameNetworkClient(GameContainer & game, const char * remote_ip, int remote_port) :
  ClientBase(&m_Backend),
  m_Backend(this, remote_ip, remote_port),
  m_GameContainer(game),
  m_ClientController(game),
  m_LevelLoader(game),
  m_EntitySync(game),
  m_LastPingSent(0),
  m_Ping(0)
{
}

void GameNetworkClient::Update()
{
  if (m_GotInitialSim)
  {
    int send_timer = 0;
    GameLogicContainer logic_container(m_Sim->m_GlobalData, m_Sim->m_ServerObjectManager, m_ClientController, m_ClientController, *m_Stage.get(), true, send_timer);
    m_GameController.Update(logic_container);

    m_EntitySync.Sync(m_Sim->m_ServerObjectManager);
  }

  ClientBase::Update();

  if (m_State == ClientConnectionState::kConnected && m_Loaded)
  {
    double cur_time = GetTimeSeconds();
    if (m_SendTimer <= cur_time)
    {
      m_SendTimer = cur_time + 0.12;
      m_Protocol->GetSenderChannel<2>().SyncState(m_ClientAuthData);

      if (cur_time - m_LastPingSent > 5)
      {
        SendPing();
      }
    }
  }
}

ClientConnectionState GameNetworkClient::GetConnectionState()
{
  return m_State;
}

void GameNetworkClient::SendJoinGame()
{
  m_Protocol->GetSenderChannel<0>().SendMessage(JoinGameMessage{});
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
  m_ClientAuthData.m_Input = input;
#endif

  if (send_immediate)
  {
    m_SendTimer = 0;
  }
}

ClientLocalData & GameNetworkClient::GetLocalData()
{
  return m_ClientData;
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
  return m_ClientAuthData.m_Input;
#endif
}

NullOptPtr<GameGlobalData> GameNetworkClient::GetGlobalData()
{
  return m_Sim ? &m_Sim->m_GlobalData : nullptr;
}

void GameNetworkClient::FinalizeConnect()
{
  m_State = ClientConnectionState::kConnected;
  m_SendTimer = GetTimeSeconds();

  m_ClientController.Connected();
}

void GameNetworkClient::HandlePong(const PongMessage & msg)
{
  m_Ping = GetTimeSeconds() - m_LastPingSent;

  if (m_GotInitialPing == false)
  {
    m_GotInitialPing = true;
    if (m_GotInitialClientData && m_GotInitialSim && m_GotInitialPing)
    {
      FinalizeConnect();
    }
  }
}

void GameNetworkClient::HandleLoadLevel(const LoadLevelMessage & load)
{
  m_State = ClientConnectionState::kLoading;

  m_InitSettings = load.m_Settings;

  m_Loading = true;
  m_Loaded = false;

  m_GotInitialSim = false;
  m_GotInitialClientData = false;

  m_Protocol->GetReceiverChannel<3>().SetDefault(nullptr);

  m_ClientController.PreloadLevel();
  m_LevelLoader.LoadLevel(load.m_Settings, load.m_LoadToken, LevelLoadCallback(&GameNetworkClient::HandleLevelLoadComplete, this));
}

void GameNetworkClient::HandleLevelLoadComplete(uint64_t load_token, const Map & map)
{
  m_Loading = false;
  m_Loaded = true;

  FinishLoadingMessage load_msg;
  load_msg.m_LoadToken = load_token;

  m_Protocol->GetSenderChannel<0>().SendMessage(load_msg);
  m_Stage = std::make_unique<GameStage>(map);
  m_Sim = m_Stage->CreateDefaultGameState();

  m_DefaultSim = m_Sim;
  m_Protocol->GetReceiverChannel<3>().SetDefault(&m_DefaultSim.Value());
}

void GameNetworkClient::HandleSimUpdate(const GameFullState & sim)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_Sim = sim;
  if (m_GotInitialSim == false)
  {
    m_GotInitialSim = true;
    if (m_GotInitialClientData && m_GotInitialSim && m_GotInitialPing)
    {
      FinalizeConnect();
    }
  }

  m_EntitySync.Sync(m_Sim->m_ServerObjectManager);
}

void GameNetworkClient::HandleGlobalEvent(std::size_t event_class_id, void * event_ptr)
{
  m_ClientController.HandleGlobalEvent(event_class_id, event_ptr);
}

void GameNetworkClient::HandleEntityEvent(std::size_t event_class_id, void * event_ptr)
{
  TargetNetworkEvent * target_ev = static_cast<TargetNetworkEvent *>(event_ptr);
  
  auto & type_info = TargetNetworkEvent::__s_TypeDatabase.GetTypeInfo(event_class_id);
  m_EntitySync.SendEntityEvent(target_ev->m_Target, type_info.m_TypeNameHash, event_ptr);
}

void GameNetworkClient::HandleClientDataUpdate(ClientLocalData && client_data)
{
  if (m_Loaded == false)
  {
    return;
  }

  m_ClientData = client_data;
  if (m_GotInitialClientData == false)
  {
    m_GotInitialClientData = true;
    if (m_GotInitialClientData && m_GotInitialSim && m_GotInitialPing)
    {
      FinalizeConnect();
    }
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

  m_ClientController.Disconnected();
}
