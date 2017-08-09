
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"


GameModeMainMenu::GameModeMainMenu(GameContainer & game) :
  GameMode(game),
  m_UIManager(game.GetWindow())
{

}

GameModeMainMenu::~GameModeMainMenu()
{

}

void GameModeMainMenu::Initialize()
{
  GetAssets().LoadAsset<TextureAsset>("./Images/GameTitle.png");
}

void GameModeMainMenu::OnAssetsLoaded()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();
  render_util.SetClearColor(Color(255, 255, 255, 255));

  UIElementFullTextureInitData logo_init;
  logo_init.m_TextureFile = "./Images/GameTitle.png";
  UIElementFullTextureData logo_data;
  logo_data.m_CenterX = 150.0f;
  logo_data.m_CenterY = render_state.GetRenderHeight() - 150.0f;

  m_TitleImage = m_UIManager.AllocateFullTexture("logo", nullptr, logo_init, logo_data);

  m_PlayOnline.Emplace(m_UIManager, "playonline", nullptr, Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 85, 30), Vector2(150, 50)), "Play", &container.GetClientGlobalResources().UISoundEffects);
  m_PlayOnline->SetOnClickCallback([this] { PlayOnline(); });

  m_Fader = m_UIManager.AllocateShape("fader", nullptr);
  m_Fader->SetActive();
  auto & fader_data = m_Fader->GetData();
  fader_data.SetColor(Color(255, 255, 255, 255));
  fader_data.SetBounds(Box::FromPoints(Vector2(0, 0), Vector2(kDefaultResolutionWidth, kDefaultResolutionHeight)));
  fader_data.m_Shape = kUIElementShapeFilledRectangle;

  m_Sequencer.Push(0.5f, [this](float val) {
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = 1.0f - val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { m_Fader->SetInactive(); });

/*
  auto resolution = render_state.GetRenderSize();
  auto screen_center = resolution / 2;
  auto popup_size = Vector2(250, 80);
  m_Shit.Emplace(m_UIManager, "shit", nullptr, Box::FromFrameCenterAndSize(screen_center, popup_size), "yo yo yo?", &container.GetClientGlobalResources().UISoundEffects);*/
}

void GameModeMainMenu::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);

}

void GameModeMainMenu::Render()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();
  auto & render_util = container.GetRenderUtil();

  render_util.SetClearColor(Color(255, 255, 255, 255));
  render_util.Clear();

  render_state.EnableBlendMode();

  m_UIManager.Render(render_state, render_util);
}

void GameModeMainMenu::PlayOnline()
{
  auto & container = GetContainer();
  container.StartNetworkClient();
  container.SwitchMode(GameModeDef<GameModeConnecting>{});
}
