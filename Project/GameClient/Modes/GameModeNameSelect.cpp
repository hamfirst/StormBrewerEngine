#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeNameSelect.h"
#include "GameClient/Modes/GameModeMainMenu.h"
#include "GameClient/Modes/GameModeConnectingLobby.h"
#include "GameClient/GameContainer.h"

#include "LobbyShared/LobbyValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/NameSelect.ui", g_NameSelectUI);

GameModeNameSelect::GameModeNameSelect(GameContainer & game, bool repick) :
  GameModeOnlineBase(game),
  m_Repick(repick)
{
  
}

GameModeNameSelect::~GameModeNameSelect()
{

}

void GameModeNameSelect::Initialize()
{
  auto & container = GetContainer();
}

void GameModeNameSelect::OnAssetsLoaded()
{
  auto & container = GetContainer();

  auto ui = container.GetUIManager();
  ui->SetGlobal("name_repick", m_Repick);

  auto & game_interface = ui->CreateGameInterface();
  BIND_SCRIPT_INTERFACE(game_interface, this, Submit);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckValidUserName);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckSubmitValidUserName);

  container.GetUIManager()->PushUIDef(g_NameSelectUI);
}

void GameModeNameSelect::Update()
{
  if(m_Repick)
  {
    if(HandleDisconnect())
    {
      return;
    }
  }

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
  if(m_Repick)
  {
    container.GetLobbyClient().SendNewUserName(user_name);
  }
  else
  {
    container.GetInitSettings()->m_UserName = user_name;
  }

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
  container.StopNetworkClient();
  container.SwitchMode<GameModeMainMenu>();
}

void GameModeNameSelect::GoToNextMode()
{
  auto & container = GetContainer();
  container.SwitchMode<GameModeConnectingLobby>();
}
