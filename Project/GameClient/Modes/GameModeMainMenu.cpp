#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeNameSelect.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"
#include "GameClient/Modes/GameModeTutorial.h"
#include "GameClient/Modes/GameModeMapSettings.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GamePlayListAsset.refl.meta.h"

#include "Foundation/Script/ScriptDataObject.h"

#include "Runtime/UI/UIResource.h"

#include "Engine/Engine.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "Engine/UI/UIManager.h"


GLOBAL_ASSET(UIResourcePtr, "./UIs/MainMenu.ui", g_MainMenuUI);

GameModeMainMenu::GameModeMainMenu(GameContainer & game) :
  GameMode(game),
  m_CasualPlaylist("./CasualPlaylist.txt"),
  m_CompetitivePlaylist("./CompetitivePlaylist.txt")
{

}

GameModeMainMenu::~GameModeMainMenu()
{

}

void GameModeMainMenu::Initialize()
{

}

void GameModeMainMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

  game_interface.AddVariable("casual_playlist",
          CreateScriptDataObject(ui->GetScriptState(), m_CasualPlaylist.GetPlayListAsset().GetData()));
  game_interface.AddVariable("competitive_playlist",
          CreateScriptDataObject(ui->GetScriptState(), m_CompetitivePlaylist.GetPlayListAsset().GetData()));

  BIND_SCRIPT_INTERFACE(game_interface, this, PlayOnline);
  BIND_SCRIPT_INTERFACE(game_interface, this, PlayOffline);
  BIND_SCRIPT_INTERFACE(game_interface, this, Tutorial);
  BIND_SCRIPT_INTERFACE(game_interface, this, PlaySingleplayer);
  BIND_SCRIPT_INTERFACE(game_interface, this, CreatePrivateMatch);
  BIND_SCRIPT_INTERFACE(game_interface, this, JoinPrivateMatch);
  BIND_SCRIPT_INTERFACE(game_interface, this, CanQuit);
  BIND_SCRIPT_INTERFACE(game_interface, this, Quit);

  container.GetUIManager()->PushUIDef(g_MainMenuUI);
}

void GameModeMainMenu::Update()
{
  m_Sequencer.Update();

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
  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinOnline);
}

void GameModeMainMenu::PlayOffline()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMapSettings>{}, GameModeMapSettingsNextScreen::kPrivateGame);
}

void GameModeMainMenu::Tutorial()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeTutorial>{});
}

void GameModeMainMenu::PlaySingleplayer()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMapSettings>{}, GameModeMapSettingsNextScreen::kOfflineBots);
}

void GameModeMainMenu::CreatePrivateMatch()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kCreatePrivate);
}

void GameModeMainMenu::JoinPrivateMatch()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinPrivate);
}

bool GameModeMainMenu::CanQuit()
{
#if defined(_WEB) || defined(_ANDROID) || defined(_IOS)
  return false;
#else
  return true;
#endif
}

void GameModeMainMenu::Quit()
{
  EngineQuit();
}