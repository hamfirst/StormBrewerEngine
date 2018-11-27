#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeLocalMultiplayer.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/Asset/Asset.h"
#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/Staging.ui", g_GameClientStagingUI);

GameModeOfflineStaging::GameModeOfflineStaging(GameContainer & game) :
  GameMode(game),
  m_UIManager(game.GetWindow())
{
  for (int index = 0; index < kMaxPlayers; ++index)
  {
    m_Attached[index] = false;
  }
}

GameModeOfflineStaging::~GameModeOfflineStaging()
{

}

void GameModeOfflineStaging::Initialize()
{

}

void GameModeOfflineStaging::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;
}

void GameModeOfflineStaging::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeOfflineStaging::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeOfflineStaging::Start()
{
  auto num_attached = 0;
  for (auto attached : m_Attached)
  {
    if (attached)
    {
      num_attached++;
    }
  }

  if (num_attached == 0)
  {
    return;
  }
}


void GameModeOfflineStaging::Back()
{
  auto & container = GetContainer();
  container.SwitchMode(GameModeDef<GameModeMainMenu>{});
}

