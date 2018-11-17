
#include "GameClient/GameClientCommon.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeOnlineGameplay.h"
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameNetworkClient.h"
#include "GameClient/GameModeOnlineStaging.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"

GameModeOnlineStaging::GameModeOnlineStaging(GameContainer & game) :
  GameMode(game),
  m_UIManager(game.GetWindow())
{

}

GameModeOnlineStaging::~GameModeOnlineStaging()
{

}

void GameModeOnlineStaging::Initialize()
{

}

void GameModeOnlineStaging::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  UIElementFullTextureInitData logo_init;
  logo_init.m_TextureFile = "./Images/GameTitle.png";
  UIElementFullTextureData logo_data;
  logo_data.m_PositionX = 0;
  logo_data.m_PositionY = 0;
  logo_data.m_ColorA = 0.3f;

  m_Back.Emplace(m_UIManager, "quit", nullptr, Box::FromFrameCenterAndSize(Vector2(half_res.x - 85, 30 - half_res.y), Vector2(150, 25)),
                 "Quit", nullptr, true);
  m_Back->SetOnClickCallback([this] { Quit(); });

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, half_res - Vector2(60, 20), false);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, half_res - Vector2(100, 20), true);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, half_res - Vector2(20, 20), container.GetWindow());

  m_Fader = m_UIManager.AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 255));
  fader_data.SetBounds(Box::FromPoints(-half_res, half_res));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_Sequencer.Push(0.5f, [this](float val) {
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = 1.0f - val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { m_Fader->SetInactive(); });
}

void GameModeOnlineStaging::Update()
{

}

void GameModeOnlineStaging::Render()
{

}

void GameModeOnlineStaging::Ready()
{

}

void GameModeOnlineStaging::KickPlayer()
{

}

void GameModeOnlineStaging::Quit()
{

}
