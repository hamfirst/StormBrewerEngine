#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeJoinPrivateGame.h"
#include "GameClient/GameContainer.h"

#include "GameShared/GameValidation.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "GameModeNameSelect.h"


GameModeNameSelect::GameModeNameSelect(GameContainer & game, GameModeNameSelectNextScreen next_mode) :
  GameMode(game),
  m_NextMode(next_mode),
  m_UIManager(game.GetWindow())
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
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;
}

void GameModeNameSelect::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeNameSelect::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  RenderUtil::SetClearColor(Color(255, 255, 255, 255));
  RenderUtil::Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeNameSelect::Submit(czstr user_name)
{
  if (ValidUserName(user_name) == false)
  {
    return;
  }

  auto & container = GetContainer();
  auto & net_init_settings = container.GetNetworkInitSettings();
  net_init_settings.m_UserName = user_name;

  GoToNextMode();
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
  else
  {
    net_init_settings.m_CreatePrivateGame = (m_NextMode == GameModeNameSelectNextScreen::kCreatePrivate);
    container.StartNetworkClient();
    container.SwitchMode(GameModeDef<GameModeConnecting>{});
  }
}
