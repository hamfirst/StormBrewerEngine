#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeLogo.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeSinglePlayerBots.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeLogo::GameModeLogo(GameContainer & game) :
  GameMode(game)
{

}

GameModeLogo::~GameModeLogo()
{

}

void GameModeLogo::Initialize()
{
  GetAssets().LoadAsset<TextureAsset>("./Images/stormbrewers_logo.png", "logo");
}

void GameModeLogo::OnAssetsLoaded()
{
  m_Timer.Start();
}

void GameModeLogo::Update()
{
  auto & container = GetContainer();
  container.GetWindow().Update();

  bool timer_allowed = m_Timer.GetTimeSinceStart() > 1.0;
  bool global_loaded = container.AllGlobalResourcesLoaded();

  if (timer_allowed && global_loaded)
  {
    container.SwitchMode(GameModeDef<GameModeMainMenu>{});
    return;
  }
}

void GameModeLogo::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetDefaultClearColor();
  render_util.Clear();
  
  render_state.EnableBlendMode();

  auto texture = GetAssets().GetTexture("logo");
  if (texture && texture->IsLoaded())
  {
    auto window_size = render_state.GetRenderSize();
    auto texture_size = texture->GetSize();
   
    render_util.DrawTexturedQuad(texture->GetSize() / -2, Color(255, 255, 255, 255), texture->GetTexture(), window_size, render_state);
  }
}

