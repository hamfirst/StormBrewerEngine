#include "GameClient/GameClientCommon.h"
#include "GameClient/Modes/GameModeLoadingGlobal.h"
#include "GameClient/Modes/GameModeLogo.h"
#include "GameClient/Modes/GameModeConnectingGame.h"
#include "GameClient/Modes/GameModeSinglePlayerBots.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

#include "Runtime/Asset/Asset.h"

GameModeLoadingGlobal::GameModeLoadingGlobal(GameContainer & game) :
  GameMode(game)
{

}

GameModeLoadingGlobal::~GameModeLoadingGlobal()
{

}

void GameModeLoadingGlobal::Initialize()
{

}

void GameModeLoadingGlobal::OnAssetsLoaded()
{
}

void GameModeLoadingGlobal::Update()
{
  auto & container = GetContainer();
  container.GetWindow().Update();
  container.UpdateUIManager();

  if(container.GetSave().IsLoaded() &&
     g_GlobalAssetList.AllAssetsLoaded())
  {
    auto init_settings = container.GetInitSettings();
    if (init_settings)
    {
      if (init_settings->m_AutoConnect)
      {
        GameNetworkClientInitSettings net_settings;
        container.StartNetworkClient(net_settings);
        container.SwitchMode(GameModeDef<GameModeConnectingGame>{});
      }
      else if (init_settings->m_AutoBotGame)
      {
        container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, false);
      }
      else
      {
        container.SwitchMode(GameModeDef<GameModeLogo>{});
      }
    }
  }
}

void GameModeLoadingGlobal::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  render_state.SetDefaultClearColor();
  render_state.Clear();
}

