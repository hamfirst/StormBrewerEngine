#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeOnlineStaging.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeConnecting::GameModeConnecting(GameContainer & game) :
  GameMode(game),
  m_ConnectFailed(false),
  m_LastConnect(0)
{
}

GameModeConnecting::~GameModeConnecting()
{

}

void GameModeConnecting::Initialize()
{
  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeConnecting::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  render_state.SetDefaultClearColor();

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  m_FrameClock.Start();
}

void GameModeConnecting::Update()
{
  auto & container = GetContainer();
  container.GetWindow().Update();

  if(container.GetClient().InPrivateGameStaging())
  {
    container.SwitchMode(GameModeDef<GameModeOnlineStaging>{});
    return;
  }

  if (m_FrameClock.ShouldSkipFrameUpdate() == false)
  {
    m_FrameClock.BeginFrame();
    container.GetClient().Update();
  }

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kConnected)
  {
    container.SwitchMode(GameModeDef<GameModeOnlineGameplay>{});
  }

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kDisconnected)
  {
    m_ConnectFailed = true;

    auto cur_time = GetTimeSeconds();
    if (cur_time - m_LastConnect > 5.0f)
    {
      m_LastConnect = cur_time;

      container.StopNetworkClient();
      container.StartNetworkClient();
    }
  }
}

void GameModeConnecting::Render()
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

    render_state.DrawDebugTexturedQuad(Box::FromFrameCenterAndSize(window_size / 2.0f, texture_size), Color(255, 255, 255, 255), texture->GetTexture(), true);

    const char * status_msg = "";
    switch (container.GetClient().GetConnectionState())
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
    case ClientConnectionState::kStaging:
    case ClientConnectionState::kConnected:
      status_msg = "Waiting for other players...";
      break;
    }

    std::string full_status_msg;
    if (container.GetClient().GetConnectionState() == ClientConnectionState::kStaging)
    {
      auto num_players = container.GetClient().GetStagingState()->m_Players.Size();
      full_status_msg = std::string(status_msg) + " (" + std::to_string(num_players) + "/" + std::to_string(kMaxPlayers) + ")";
      status_msg = full_status_msg.data();
    }

    auto text_size = g_TextManager.GetTextSize(status_msg, -1, 1);

    Vector2 text_pos = {};
    text_pos.y -= texture_size.y / 2 + 4;
    text_pos.x -= text_size.Size().x / 2;

    g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
    g_TextManager.SetTextMode();
    g_TextManager.SetTextPos(text_pos);
    g_TextManager.RenderText(status_msg, -1, 1, render_state);

    if (m_ConnectFailed &&
      container.GetClient().GetConnectionState() != ClientConnectionState::kStaging &&
      container.GetClient().GetConnectionState() != ClientConnectionState::kLoading)
    {
      status_msg = "The servers may be offline";
      auto text_size = g_TextManager.GetTextSize(status_msg, -1, 1);

      Vector2 text_pos = {};
      text_pos.y -= texture_size.y / 2 + 25;
      text_pos.x -= text_size.Size().x / 2;

      g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
      g_TextManager.SetTextMode();
      g_TextManager.SetTextPos(text_pos);
      g_TextManager.RenderText(status_msg, -1, 1, render_state);
    }

    if (container.GetClient().GetConnectionState() == ClientConnectionState::kStaging)
    {
      auto staging_state = container.GetClient().GetStagingState();

      if (staging_state->m_WaitTimer != 0)
      {
        char text[512];

        auto timer = staging_state->m_WaitTimer / 60;
        snprintf(text, sizeof(text), "Starting in %d:%02d", timer / 60, timer % 60);

        auto text_size = g_TextManager.GetTextSize(text, -1, 1);

        Vector2 text_pos = {};
        text_pos.y -= 120;
        text_pos.x -= text_size.Size().x / 2;

        g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
        g_TextManager.SetTextMode();
        g_TextManager.SetTextPos(text_pos);
        g_TextManager.RenderText(text, -1, 1, render_state);
      }
    }
  }

  container.RenderUIManager();
}

void GameModeConnecting::Back()
{
  auto & container = GetContainer();
  container.StopNetworkClient();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}
