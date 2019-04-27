#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeConnectingLobby.h"
#include "GameClient/Modes/GameModeNameSelect.h"
#include "GameClient/Modes/GameModeTutorial.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GamePlayListAsset.refl.meta.h"

#include "Runtime/UI/UIResource.h"

#include "Engine/Engine.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "Engine/UI/UIManager.h"


GLOBAL_ASSET(UIResourcePtr, "./UIs/MainMenu.ui", g_MainMenuUI);

GameModeMainMenu::GameModeMainMenu(GameContainer & game, const std::string_view & error_msg) :
  GameMode(game),
  m_ErrorMessage(error_msg)
{

}

GameModeMainMenu::~GameModeMainMenu()
{

}

void GameModeMainMenu::Initialize()
{

}

void GameModeMainMenu::Deinit()
{
  auto & container = GetContainer();
  container.GetUIManager()->ClearUI();
  container.GetUIManager()->ClearGameInterface();
}

void GameModeMainMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

#ifdef NET_ALLOW_OFFLINE_GAME
  game_interface.AddVariable("allow_local", true);
#else
  game_interface.AddVariable("allow_local", false);
#endif

#ifdef NET_ALLOW_TUTORIAL
  game_interface.AddVariable("allow_tutorial", true);
#else
  game_interface.AddVariable("allow_tutorial", false);
#endif

#if defined(_WEB) || defined(_ANDROID) || defined(_IOS)
  game_interface.AddVariable("allow_quit", false);
#else
  game_interface.AddVariable("allow_quit", true);
#endif

  BIND_SCRIPT_INTERFACE(game_interface, this, PlayOnline);
  BIND_SCRIPT_INTERFACE(game_interface, this, PlayOffline);
  BIND_SCRIPT_INTERFACE(game_interface, this, Tutorial);
  BIND_SCRIPT_INTERFACE(game_interface, this, PlaySingleplayer);
  BIND_SCRIPT_INTERFACE(game_interface, this, Quit);

  container.GetUIManager()->PushUIDef(g_MainMenuUI);

  if(!m_ErrorMessage.empty())
  {
    ui->Call("ShowErrorPopup", { m_ErrorMessage });
  }
}

void GameModeMainMenu::Update()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeMainMenu::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();
  container.RenderUIManager();
}

void GameModeMainMenu::InputEvent()
{
  auto & container = GetContainer();
  container.RenderUIManager();
}

void GameModeMainMenu::PlayOnline()
{
  auto & container = GetContainer();

  if(container.GetInitSettings()->m_LoginMode == LobbyLoginMode::kGuest)
  {
    container.SwitchMode<GameModeNameSelect>(false);
  }
  else
  {
    container.SwitchMode<GameModeConnectingLobby>();
  }
}

void GameModeMainMenu::PlayOffline()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeMapSettings>(GameModeMapSettingsNextScreen::kOfflineStaging);
}

void GameModeMainMenu::Tutorial()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeTutorial>();
}

void GameModeMainMenu::PlaySingleplayer()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeTutorial>();
}


void GameModeMainMenu::Quit()
{
  EngineQuit();
}