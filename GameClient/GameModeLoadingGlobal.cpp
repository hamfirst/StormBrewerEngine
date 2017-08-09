
#include "GameClient/GameModeLoadingGlobal.h"
#include "GameClient/GameModeLogo.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

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
  if(container.GetClientGlobalResources().IsLoaded() &&
     container.GetSharedGlobalResources().IsLoaded())
  {
    auto init_settings = container.GetInitSettings();
    if (init_settings)
    {
      if (init_settings->m_AutoConnect)
      {
        auto & net_settings = container.GetNetworkInitSettings();
        net_settings.m_UserName = init_settings->m_UserName;

        container.StartNetworkClient();
        container.SwitchMode(GameModeDef<GameModeConnecting>{});
      }
      else if (init_settings->m_AutoBotGame)
      {
        container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, init_settings->m_UserName, GameInitSettings{});
      }
    }
    else
    {
      container.SwitchMode(GameModeDef<GameModeLogo>{});
    }
  }
}

void GameModeLoadingGlobal::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();
}

