#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeOnlineGameplay.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/Modes/GameModeOnlineStaging.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeConnectingGame::GameModeConnectingGame(GameContainer & game) :
  GameModeOnlineBase(game),
  m_ConnectFailed(false),
  m_Start(GetTimeSeconds()),
  m_LastConnect(GetTimeSeconds())
{
}

GameModeConnectingGame::~GameModeConnectingGame()
{

}

void GameModeConnectingGame::Initialize()
{
  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeConnectingGame::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  render_state.SetDefaultClearColor();

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  m_FrameClock.Start();
}

void GameModeConnectingGame::Update()
{
  if(HandleDisconnect())
  {
    return;
  }

  auto & container = GetContainer();
  container.GetWindow().Update();

  if (m_FrameClock.ShouldSkipFrameUpdate() == false)
  {
    m_FrameClock.BeginFrame();

    if(container.HasClient())
    {
      container.GetGameClient().Update();
    }
  }

  if(container.HasClient() == false)
  {
#ifndef NET_FORCE_CASUAL_GAMES
    if(container.HasLobbyClient())
    {
      GetContainer().SwitchMode<GameModePlayOnline>("Failed to connect to game server");
      return;
    }
#endif

    GetContainer().SwitchMode<GameModeMainMenu>("Failed to connect to game server");
    return;
  }

  if (container.GetGameClient().GetConnectionState() == ClientConnectionState::kConnected)
  {
    container.SwitchMode<GameModeOnlineGameplay>();
    return;
  }

  if (container.GetGameClient().GetConnectionState() == ClientConnectionState::kDisconnected)
  {
    m_ConnectFailed = true;

    auto cur_time = GetTimeSeconds();

    if(cur_time - m_Start > 20.0f)
    {
      container.StopNetworkClient();

#ifndef NET_FORCE_CASUAL_GAMES
      if(container.HasLobbyClient())
      {
        GetContainer().SwitchMode<GameModePlayOnline>("Failed to connect to game server");
        return;
      }
#endif

      GetContainer().StopLobbyClient();
      GetContainer().SwitchMode<GameModeMainMenu>("Failed to connect to game server");
      return;
    }

    if (cur_time - m_LastConnect > 5.0f && container.HasClient())
    {
      m_LastConnect = cur_time;

      auto settings = container.GetGameClient().GetSettings();
      container.StopNetworkClient();
      container.StartNetworkClient(settings);
    }
  }
}

void GameModeConnectingGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.Clear();
  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture && texture->IsLoaded())
  {
    auto window_size = render_state.GetRenderSize();
    auto texture_size = texture->GetSize();

    render_state.DrawDebugTexturedQuad(Box::FromFrameCenterAndSize({}, texture_size), Color(255, 255, 255, 255), texture->GetTexture(), true);

    const char * status_msg = "";
    switch (container.GetGameClient().GetConnectionState())
    {
    case ClientConnectionState::kConnecting:
    case ClientConnectionState::kDisconnected:
      status_msg = "Connecting...";
      break;
    case ClientConnectionState::kJoining:
      status_msg = "Joining...";
      break;
    case ClientConnectionState::kLoading:
      status_msg = "Loading...";
      break;
    case ClientConnectionState::kConnected:
      status_msg = "Waiting for other players...";
      break;
    }

    std::string full_status_msg;
    auto text_size = g_TextManager.GetTextSize(status_msg, -1, 1);

    Vector2 text_pos = {};
    text_pos.y -= texture_size.y / 2 + 4;
    text_pos.x -= text_size.Size().x / 2;

    g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
    g_TextManager.SetTextMode();
    g_TextManager.SetTextPos(text_pos);
    g_TextManager.RenderText(status_msg, -1, 1, render_state);
  }

  container.RenderUIManager();
}

void GameModeConnectingGame::Back()
{
  auto & container = GetContainer();
  container.StopNetworkClient();
  container.SwitchMode<GameModeMainMenu>();
}
