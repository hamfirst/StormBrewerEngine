
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeConnecting::GameModeConnecting(GameContainer & game) :
  GameMode(game)
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
}

void GameModeConnecting::Update()
{
  auto & container = GetContainer();
  container.GetClient().Update();

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kConnected)
  {
    auto & global_data = container.GetClient().GetClientInstanceData()->GetGameState();
    if (global_data.m_Started)
    {
      container.SwitchMode(GameModeDef<GameModeOnlineGameplay>{});
    }
  }

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kDisconnected)
  {
    // Ruh roh
  }
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
      status_msg = "Connecting...";
      break;
    case ClientConnectionState::kJoining:
      status_msg = "Joining...";
      break;
    case ClientConnectionState::kLoading:
    case ClientConnectionState::kWaitingForInitialSync:
      status_msg = "Loading...";
      break;
    case ClientConnectionState::kDisconnected:
      status_msg = "Disconnected...";
      break;
    case ClientConnectionState::kConnected:
      status_msg = "Waiting for other players...";
      break;
    }

    auto text_size = g_TextManager.GetTextSize(status_msg, -1);

    auto text_pos = window_size / 2;
    text_pos.y -= texture_size.y / 2 + 4;
    text_pos.x -= text_size.Size().x / 2;

    g_TextManager.SetPrimaryColor(Color(255, 0, 0, 255));
    g_TextManager.SetTextMode();
    g_TextManager.SetTextPos(text_pos);
    g_TextManager.RenderText(status_msg, -1, render_state);
  }
}

