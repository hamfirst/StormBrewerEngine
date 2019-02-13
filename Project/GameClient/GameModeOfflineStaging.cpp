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

GameModeOfflineStaging::GameModeOfflineStaging(GameContainer & game, GameInitSettings & settings) :
  GameMode(game)
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

}

void GameModeOfflineStaging::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();
  container.UpdateUIManager();
}

void GameModeOfflineStaging::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();

  render_state.EnableBlendMode();
  container.RenderUIManager();
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

