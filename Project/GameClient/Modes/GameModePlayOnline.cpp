
#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModePlayOnline.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/Modes/GameModePlaylistMenu.h"
#include "GameClient/Modes/GameModeJoinPrivateGame.h"
#include "GameClient/GameContainer.h"

#include "Engine/UI/UIManager.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/PlayOnline.ui", g_PlayOnlineMenu);

GameModePlayOnline::GameModePlayOnline(GameContainer & game, const std::string_view & error_msg) :
        GameModeOnlineBase(game),
        m_ErrorMessage(error_msg)
{

}

GameModePlayOnline::~GameModePlayOnline()
{

}

void GameModePlayOnline::Initialize()
{

}

void GameModePlayOnline::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModePlayOnline::OnAssetsLoaded()
{
#ifndef NET_FORCE_CASUAL_GAMES
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  BIND_SCRIPT_INTERFACE(game_interface, this, SearchCompetitive);
  BIND_SCRIPT_INTERFACE(game_interface, this, SearchCasual);
  BIND_SCRIPT_INTERFACE(game_interface, this, CreatePrivate);
  BIND_SCRIPT_INTERFACE(game_interface, this, JoinPrivate);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);

  container.GetUIManager()->PushUIDef(g_PlayOnlineMenu);

  if(!m_ErrorMessage.empty())
  {
    ui->Call("ShowErrorPopup", { m_ErrorMessage });
  }
#endif
}

void GameModePlayOnline::Update()
{
#ifndef NET_FORCE_CASUAL_GAMES
  if(HandleDisconnect())
  {
    return;
  }

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
#else
  SearchCasual();
#endif
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

void GameModePlayOnline::SearchCompetitive()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModePlaylistMenu>(true);
}

void GameModePlayOnline::SearchCasual()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModePlaylistMenu>(false);
}

void GameModePlayOnline::CreatePrivate()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeMapSettings>(GameModeMapSettingsNextScreen::kPrivateGame);
}

void GameModePlayOnline::JoinPrivate()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeJoinPrivateGame>();
}

void GameModePlayOnline::Back()
{
  auto & container = GetContainer();
  container.StopLobbyClient();
  container.SwitchMode<GameModeMainMenu>();
}