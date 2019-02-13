#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeJoinPrivateGame.h"
#include "GameClient/GameModeMapSettings.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameModeNameSelect.h"

#include "GameShared/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/NameSelect.ui", g_NameSelectUI);

GameModeNameSelect::GameModeNameSelect(GameContainer & game, GameModeNameSelectNextScreen next_mode) :
  GameMode(game),
  m_NextMode(next_mode)
{
  
}

GameModeNameSelect::~GameModeNameSelect()
{

}

void GameModeNameSelect::Initialize()
{
  auto & container = GetContainer();
  auto & net_init_settings = container.GetNetworkInitSettings();
  if(net_init_settings.m_UserName.empty() == false)
  {
    GoToNextMode();
  }
}

void GameModeNameSelect::OnAssetsLoaded()
{
  auto & container = GetContainer();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();
  BIND_SCRIPT_INTERFACE(game_interface, this, Submit);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckValidUserName);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckSubmitValidUserName);

  container.GetUIManager()->PushUIDef(g_NameSelectUI);
}

void GameModeNameSelect::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeNameSelect::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();

  container.RenderUIManager();
}

bool GameModeNameSelect::Submit(std::string & user_name)
{
  if (ValidUserName(user_name.c_str()) == false)
  {
    return false;
  }

  auto & container = GetContainer();
  auto & net_init_settings = container.GetNetworkInitSettings();
  net_init_settings.m_UserName = user_name;

  GoToNextMode();
  return true;
}

bool GameModeNameSelect::CheckValidUserName(std::string & user_name)
{
  return ValidUserName(user_name.c_str(), true);
}

bool GameModeNameSelect::CheckSubmitValidUserName(std::string & user_name)
{
  return ValidUserName(user_name.c_str());
}

void GameModeNameSelect::Back()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}

void GameModeNameSelect::GoToNextMode()
{
  auto & container = GetContainer();
  auto & net_init_settings = container.GetNetworkInitSettings();

  if (m_NextMode == GameModeNameSelectNextScreen::kJoinPrivate)
  {
    container.SwitchMode(GameModeDef<GameModeJoinPrivateGame>{});
  }
  else if (m_NextMode == GameModeNameSelectNextScreen::kJoinOnline)
  {
    net_init_settings.m_Intent = ClientConnectionIntent::kRandom;
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
  }
  else
  {
    container.SwitchMode(GameModeDef<GameModeMapSettings>{}, GameModeMapSettingsNextScreen::kPrivateGame);
  }
}
