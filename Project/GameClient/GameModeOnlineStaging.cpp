
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeOnlineStaging.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeOnlineStaging::GameModeOnlineStaging(GameContainer & game) :
  GameMode(game)
{

}

GameModeOnlineStaging::~GameModeOnlineStaging()
{

}

void GameModeOnlineStaging::Initialize()
{

}

void GameModeOnlineStaging::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();  

  render_state.SetDefaultClearColor();
  render_state.Clear();

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;
}

void GameModeOnlineStaging::Update()
{

}

void GameModeOnlineStaging::Render()
{

}

void GameModeOnlineStaging::Ready()
{

}

void GameModeOnlineStaging::KickPlayer()
{

}

void GameModeOnlineStaging::Quit()
{

}
