
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"


void GameModeConnecting::Initialize(GameContainer & container)
{
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(0, 0, 0, 255));

  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeConnecting::OnAssetsLoaded(GameContainer & container)
{
}

void GameModeConnecting::Update(GameContainer & container)
{
  container.GetClient().Update();

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kConnected)
  {
    auto global_data = container.GetClient().GetGlobalData();
    if (global_data && global_data->m_Started)
    {
      container.SwitchMode(GameModeDef<GameModeOnlineGameplay>{});
    }
  }

  if (container.GetClient().GetConnectionState() == ClientConnectionState::kDisconnected)
  {
    // Ruh roh
  }
}

void GameModeConnecting::Render(GameContainer & container)
{
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.Clear();

  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture->IsLoaded())
  {
    auto window_size = container.GetWindow().GetSize();
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
    g_TextManager.SetTextPos(text_pos);
    g_TextManager.RenderText(status_msg, -1, render_state);

  }
}

