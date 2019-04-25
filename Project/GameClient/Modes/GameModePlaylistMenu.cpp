
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModePlaylistMenu.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"

#include "Engine/UI/UIManager.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/PlaylistMenuCompetitive.ui", g_PlaylistMenuCompetitive)
GLOBAL_ASSET(UIResourcePtr, "./UIs/PlaylistMenuCasual.ui", g_PlaylistMenuCasual);

GameModePlaylistMenu::GameModePlaylistMenu(GameContainer & game, bool competitive) :
  GameModeOnlineBase(game),
  m_Competitive(competitive)
{

}

GameModePlaylistMenu::~GameModePlaylistMenu()
{

}

void GameModePlaylistMenu::Initialize()
{

}

void GameModePlaylistMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  //BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  //BIND_SCRIPT_INTERFACE(game_interface, this, ConnectComplete);

  if(m_Competitive)
  {
    container.GetUIManager()->PushUIDef(g_PlaylistMenuCompetitive);
  }
  else
  {
    container.GetUIManager()->PushUIDef(g_PlaylistMenuCasual);
  }
}

void GameModePlaylistMenu::Update()
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

void GameModePlaylistMenu::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}
