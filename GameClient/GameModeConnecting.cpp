
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeConnecting::GameModeConnecting(GameContainer & game) :
  GameMode(game),
  m_UIManager(game.GetWindow()),
  m_ConnectFailed(false),
  m_LastConnect(0)
{
}

GameModeConnecting::~GameModeConnecting()
{

}

void GameModeConnecting::Initialize()
{
  auto & container = GetContainer();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");

}

void GameModeConnecting::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  m_Back.Emplace(m_UIManager, "back", nullptr,
    Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 35, 30), Vector2(60, 25)), "Back", &container.GetClientGlobalResources().UISoundEffects, true);
  m_Back->SetOnClickCallback([this]() { Back(); });

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, render_state.GetRenderSize() - Vector2(80, 40), false, &container.GetClientGlobalResources().UISoundEffects);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, render_state.GetRenderSize() - Vector2(120, 40), true, &container.GetClientGlobalResources().UISoundEffects);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, render_state.GetRenderSize() - Vector2(40, 40), container.GetWindow(), &container.GetClientGlobalResources().UISoundEffects);

  m_FrameClock.Start();
}

void GameModeConnecting::Update()
{
  auto & container = GetContainer();

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

  auto & render_state = container.GetRenderState();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeConnecting::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.Clear();

  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture && texture->IsLoaded())
  {
    auto window_size = render_state.GetRenderSize();
    auto texture_size = texture->GetSize();

    render_util.DrawTexturedQuad(window_size / 2 - texture_size / 2, Color(255, 255, 255, 255), texture->GetTexture(), window_size);

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

    auto text_size = g_TextManager.GetTextSize(status_msg, -1);

    auto text_pos = window_size / 2;
    text_pos.y -= texture_size.y / 2 + 4;
    text_pos.x -= text_size.Size().x / 2;

    g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
    g_TextManager.SetTextMode();
    g_TextManager.SetTextPos(text_pos);
    g_TextManager.RenderText(status_msg, -1, render_state);

    if (m_ConnectFailed &&
      container.GetClient().GetConnectionState() != ClientConnectionState::kStaging &&
      container.GetClient().GetConnectionState() != ClientConnectionState::kLoading)
    {
      status_msg = "The servers may be offline";
      auto text_size = g_TextManager.GetTextSize(status_msg, -1);

      auto text_pos = window_size / 2;
      text_pos.y -= texture_size.y / 2 + 25;
      text_pos.x -= text_size.Size().x / 2;

      g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
      g_TextManager.SetTextMode();
      g_TextManager.SetTextPos(text_pos);
      g_TextManager.RenderText(status_msg, -1, render_state);
    }

    if (container.GetClient().GetConnectionState() == ClientConnectionState::kStaging)
    {
      auto staging_state = container.GetClient().GetStagingState();

      if (staging_state->m_WaitTimer != 0)
      {
        char text[512];

        auto timer = staging_state->m_WaitTimer / 60;
        snprintf(text, sizeof(text), "Starting in %d:%02d", timer / 60, timer % 60);

        auto text_size = g_TextManager.GetTextSize(text, -1);

        auto text_pos = window_size / 2;
        text_pos.y -= 200;
        text_pos.x -= text_size.Size().x / 2;

        g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
        g_TextManager.SetTextMode();
        g_TextManager.SetTextPos(text_pos);
        g_TextManager.RenderText(text, -1, render_state);
      }
    }
  }

  m_UIManager.Render(render_state, render_util);
}

void GameModeConnecting::Back()
{
  auto & container = GetContainer();
  container.StopNetworkClient();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}
