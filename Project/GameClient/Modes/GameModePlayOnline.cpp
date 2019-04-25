
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/Modes/GameModePlaylistMenu.h"
#include "GameClient/GameContainer.h"

#include "Engine/UI/UIManager.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/PlayOnline.ui", g_PlayOnlineMenu);

GameModePlayOnline::GameModePlayOnline(GameContainer & game) :
        GameModeOnlineBase(game)
{

}

GameModePlayOnline::~GameModePlayOnline()
{

}

void GameModePlayOnline::Initialize()
{

}

void GameModePlayOnline::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  //BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  //BIND_SCRIPT_INTERFACE(game_interface, this, ConnectComplete);

  container.GetUIManager()->PushUIDef(g_PlayOnlineMenu);
}

void GameModePlayOnline::Update()
{
  if(HandleDisconnect())
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModePlayOnline::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}
