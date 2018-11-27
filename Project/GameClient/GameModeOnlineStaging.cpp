
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
  GameMode(game),
  m_UIManager(game.GetWindow())
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
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

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
