#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameModeTutorial.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameContainer.h"

#include "Engine/Engine.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/MainMenu.ui", g_MainMenuUI);


czstr g_AccountName = nullptr;

GameModeMainMenu::GameModeMainMenu(GameContainer & game) :
  GameMode(game)
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
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();

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
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

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
  if (g_AccountName != nullptr)
  {
    auto & net_init_settings = container.GetNetworkInitSettings();
    net_init_settings.m_UserName = g_AccountName;
  }

  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinOnline);
}

void GameModeMainMenu::PlayOffline()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeOfflineStaging>{});
}

void GameModeMainMenu::Tutorial()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeTutorial>{}, GameInitSettings{});
}

void GameModeMainMenu::PlaySingleplayer()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, false);
}

void GameModeMainMenu::CreatePrivateMatch()
{
  auto & container = GetContainer();
  if (g_AccountName != nullptr)
  {
    auto & net_init_settings = container.GetNetworkInitSettings();
    net_init_settings.m_UserName = g_AccountName;
  }

  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kCreatePrivate);
}

void GameModeMainMenu::JoinPrivateMatch()
{
  auto & container = GetContainer();
  if (g_AccountName != nullptr)
  {
    auto & net_init_settings = container.GetNetworkInitSettings();
    net_init_settings.m_UserName = g_AccountName;
  }

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