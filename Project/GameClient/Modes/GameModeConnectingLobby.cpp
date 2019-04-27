#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeConnectingLobby.h"
#include "GameClient/Modes/GameModeNameSelect.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/Modes/GameModePlaylistMenu.h"
#include "GameClient/Modes/GameModeJoinPrivateGame.h"
#include "GameClient/GameContainer.h"

#include "Engine/UI/UIManager.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/Connecting.ui", g_ConnectingMenu);

GameModeConnectingLobby::GameModeConnectingLobby(GameContainer & game, GameModeConnectingLobbyIntent intent) :
        GameMode(game),
        m_Intent(intent),
        m_FinishedConnect(false)
{
}

GameModeConnectingLobby::~GameModeConnectingLobby()
{

}

void GameModeConnectingLobby::Initialize()
{
  auto & container = GetContainer();
  if(container.HasLobbyClient() == false)
  {
    container.StartLobbyClient();
  }

  if(container.GetLobbyClient().GetState() == LobbyClientState::kDisconnected)
  {
    container.GetLobbyClient().Connect();
  }

  if(container.HasLatencyChecker() == false)
  {
    container.StartLatencyChecker();
    container.GetLatencyChecker().Start();
  }

  m_StopWatch.Start();
}

void GameModeConnectingLobby::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModeConnectingLobby::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  BIND_SCRIPT_INTERFACE(game_interface, this, ConnectComplete);

  container.GetUIManager()->PushUIDef(g_ConnectingMenu);
}

void GameModeConnectingLobby::Update()
{
  auto & container = GetContainer();
  container.GetLobbyClient().Update();

  auto & lobby_client = container.GetLobbyClient();
  if(lobby_client.HasLatencySamples() == false && container.GetLatencyChecker().IsComplete())
  {
    auto results = container.GetLatencyChecker().GetResults();
    std::vector<int> samples;

    for(int index = 0; index < kNumProjectZones; ++index)
    {
      samples.push_back(results.m_Latency[index]);
    }

    lobby_client.SetLatencySamples(samples);
  }


  if(lobby_client.GetState() == LobbyClientState::kDisconnected)
  {
    static const float kConnectScreenFailTime = 10.0f;
    if(m_StopWatch.GetTimeSinceStart() > kConnectScreenFailTime)
    {
      container.SwitchMode<GameModeMainMenu>(lobby_client.GetConnectionError());
      return;
    }
  }
  else if(lobby_client.GetState() == LobbyClientState::kConnected && lobby_client.GetUserLocalData().IsValid())
  {
    if(m_FinishedConnect == false)
    {
      auto ui = container.GetUIManager();
      ui->Call("ConnectComplete");

      m_FinishedConnect = true;
    }
  }

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeConnectingLobby::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

void GameModeConnectingLobby::Back()
{
  auto & container = GetContainer();
  container.StopLobbyClient();
  container.SwitchMode<GameModeMainMenu>();
}

void GameModeConnectingLobby::ConnectComplete()
{
  auto & container = GetContainer();
  auto & lobby_client = container.GetLobbyClient();
  switch(lobby_client.GetState())
  {
    case LobbyClientState::kNewUser:
      container.SwitchMode<GameModeNameSelect>(false);
      break;
    case LobbyClientState::kNewUserRepick:
      container.SwitchMode<GameModeNameSelect>(true);
      break;
    case LobbyClientState::kConnected:
      switch(m_Intent)
      {
        case GameModeConnectingLobbyIntent::kOnlineMenu:
          container.SwitchMode<GameModePlayOnline>();
          break;
        case GameModeConnectingLobbyIntent::kCompetitive:
          container.SwitchMode<GameModePlaylistMenu>(true);
          break;
        case GameModeConnectingLobbyIntent::kCasual:
          container.SwitchMode<GameModePlaylistMenu>(false);
          break;
        case GameModeConnectingLobbyIntent::kHostPrivate:
          container.SwitchMode<GameModeMapSettings>(GameModeMapSettingsNextScreen::kPrivateGame);
          break;
        case GameModeConnectingLobbyIntent::kJoinPrivate:
          container.SwitchMode<GameModeJoinPrivateGame>();
          break;
      }
      break;

    default:
      Back();
      break;
  }

}