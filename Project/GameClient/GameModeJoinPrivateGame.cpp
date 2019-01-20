#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeJoinPrivateGame.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/JoinPrivateGame.ui", g_JoinPrivateGameUI);

GameModeJoinPrivateGame::GameModeJoinPrivateGame(GameContainer & game) :
        GameMode(game)
{

}

GameModeJoinPrivateGame::~GameModeJoinPrivateGame()
{

}

void GameModeJoinPrivateGame::Initialize()
{

}

void GameModeJoinPrivateGame::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetDefaultClearColor();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();
  BIND_SCRIPT_INTERFACE(game_interface, this, Submit);
  BIND_SCRIPT_INTERFACE(game_interface, this, Back);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckValidGameCode);
  BIND_SCRIPT_INTERFACE(game_interface, this, CheckSubmitValidGameCode);

  container.GetUIManager()->PushUIDef(g_JoinPrivateGameUI);
}

void GameModeJoinPrivateGame::Update()
{
  m_Sequencer.Update();
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeJoinPrivateGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  RenderUtil::SetDefaultClearColor();
  RenderUtil::Clear();

  render_state.EnableBlendMode();
  container.RenderUIManager();
}

void GameModeJoinPrivateGame::Submit(std::string & game_code_str)
{
  if (ValidGameCode(game_code_str.data()) == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & input_text = game_code_str;
  auto & net_init_settings = container.GetNetworkInitSettings();

  auto & text = game_code_str;
  uint32_t game_code = 0;

  for(int index = 0; index < 4; ++index)
  {
    auto c = text[index];
    int val = 0;

    if(c >= 'a' && c <= 'z')
    {
      val = c - 'a';
    }
    else if(c >= 'A' && c <= 'A')
    {
      val = c - 'A';
    }
    else if(c >= '0' && c <= '9')
    {
      val = c - '0' + 26;
    }

    game_code <<= 8;
    game_code |= val;
  }

  net_init_settings.m_CreatePrivateGame = false;
  net_init_settings.m_JoinPrivateGameKey = game_code;
  container.StartNetworkClient();
  container.SwitchMode(GameModeDef<GameModeConnecting>{});
}

bool GameModeJoinPrivateGame::CheckValidGameCode(std::string & user_name)
{
  return ValidGameCode(user_name.c_str(), true);
}

bool GameModeJoinPrivateGame::CheckSubmitValidGameCode(std::string & user_name)
{
  return ValidGameCode(user_name.c_str());
}

void GameModeJoinPrivateGame::Back()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}
