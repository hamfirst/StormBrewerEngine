#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameModeTutorial.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"

#include "Runtime/Atlas/AtlasResource.h"

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
  GetAssets().LoadAsset<TextureAsset>("./Images/GameTitle.png");

}

void GameModeMainMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  //g_MusicManager.CutTo(GetContainer().GetClientGlobalResources().MainMenuMusic, 0.5f);
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

  container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinOnline);
}