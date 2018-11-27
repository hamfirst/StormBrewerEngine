#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeJoinPrivateGame.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeJoinPrivateGame::GameModeJoinPrivateGame(GameContainer & game) :
        GameMode(game),
        m_UIManager(game.GetWindow())
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
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;
}

void GameModeJoinPrivateGame::Update()
{
  m_Sequencer.Update();
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeJoinPrivateGame::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  RenderUtil::SetClearColor(Color(255, 255, 255, 255));
  RenderUtil::Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeJoinPrivateGame::Submit(czstr game_code_str)
{
  if (ValidGameCode(game_code_str) == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & input_text = game_code_str;
  auto & net_init_settings = container.GetNetworkInitSettings();

  auto text = game_code_str;
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

void GameModeJoinPrivateGame::Back()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}
