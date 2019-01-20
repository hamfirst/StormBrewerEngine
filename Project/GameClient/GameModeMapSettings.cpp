#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeMapSettings.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/UI/UIManager.h"

#include "Runtime/Asset/Asset.h"
#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/MapSettings.ui", g_MapSettingsSelectUI);

GameModeMapSettings::GameModeMapSettings(GameContainer &game, GameModeMapSettingsNextScreen next_screen) :
    GameMode(game),
    m_NextScreen(next_screen)
{

}

void GameModeMapSettings::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  auto ui = container.GetUIManager();

  auto & game_interface = ui->CreateGameInterface();
  //BIND_SCRIPT_INTERFACE(game_interface, this, Submit);

  container.GetUIManager()->PushUIDef(g_MapSettingsSelectUI);
}

void GameModeMapSettings::Update()
{

}

void GameModeMapSettings::Render()
{

}

void GameModeMapSettings::Ready()
{

}

void GameModeMapSettings::KickPlayer()
{

}

void GameModeMapSettings::Quit()
{

}

