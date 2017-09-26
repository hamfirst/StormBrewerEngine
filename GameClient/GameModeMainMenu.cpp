
#include "GameClient/GameModeMainMenu.h"
#include "GameClient/GameModeConnecting.h"
#include "GameClient/GameModeNameSelect.h"
#include "GameClient/GameModeSinglePlayerBots.h"
#include "GameClient/GameModeTutorial.h"
#include "GameClient/GameModeOfflineStaging.h"
#include "GameClient/GameContainer.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"

czstr g_AccountName = nullptr;

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
  logo_data.m_PositionX = kDefaultResolutionWidth / 2.0f;
  logo_data.m_PositionY = kDefaultResolutionHeight / 2.0f;

  m_TitleImage = m_UIManager.AllocateFullTexture("logo", nullptr, logo_init, logo_data);

  m_PlayOnline.Emplace(m_UIManager, "playonline", nullptr, 
    Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 85, 160), Vector2(150, 50)), "Play Online", &container.GetClientGlobalResources().UISoundEffects);
  m_PlayOnline->SetOnClickCallback([this] { PlayOnline(); });

  m_Tutorial.Emplace(m_UIManager, "tutorial", nullptr,
    Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 85, 100), Vector2(150, 30)), "Tutorial", &container.GetClientGlobalResources().UISoundEffects);
  m_Tutorial->SetOnClickCallback([this] { Tutorial(); });

  m_PlayOffline.Emplace(m_UIManager, "playoffline", nullptr, 
    Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 85, 65), Vector2(150, 30)), "Local Multiplayer", &container.GetClientGlobalResources().UISoundEffects);
  m_PlayOffline->SetOnClickCallback([this] { PlayOffline(); });

  m_PlaySingleplayer.Emplace(m_UIManager, "playsingleplayer", nullptr,
    Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() - 85, 30), Vector2(150, 30)), "Single Player", &container.GetClientGlobalResources().UISoundEffects);
  m_PlaySingleplayer->SetOnClickCallback([this] { PlaySingleplayer(); });

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, render_state.GetRenderSize() - Vector2(80, 40), false, &container.GetClientGlobalResources().UISoundEffects);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, render_state.GetRenderSize() - Vector2(120, 40), true, &container.GetClientGlobalResources().UISoundEffects);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, render_state.GetRenderSize() - Vector2(40, 40), container.GetWindow(), &container.GetClientGlobalResources().UISoundEffects);

  if (container.GetSave().GetSaveData().m_WatchedTutorial == false)
  {
    m_TutorialPrompt.Emplace(m_UIManager, "tutorialprompt", nullptr, 
      Box::FromFrameCenterAndSize(render_state.GetRenderSize() * 0.5f, Vector2(270, 100)), 
      "First time playing? Why not watch the tutorial?", &container.GetClientGlobalResources().UISoundEffects);
    m_TutorialPrompt->SetOnOkayCallback([this] { Tutorial(); });
    m_TutorialPrompt->Show();

    container.GetSave().GetSaveData().m_WatchedTutorial = true;
    container.GetSave().RequestSave();
  }

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

  g_MusicManager.CutTo(GetContainer().GetClientGlobalResources().MainMenuMusic, 0.5f);

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

void GameModeMainMenu::InputEvent()
{
  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  auto input_state = container.GetWindow().GetInputState();
  m_UIManager.Update(*input_state, render_state);
}

void GameModeMainMenu::PlayOnline()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive(); 
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) { 
    if (g_AccountName == nullptr)
    {
      auto & container = GetContainer();
      container.SwitchMode(GameModeDef<GameModeNameSelect>{});
    }
    else
    {
      auto & container = GetContainer();
      auto & net_init_settings = container.GetNetworkInitSettings();

      net_init_settings.m_UserName = g_AccountName;
      container.StartNetworkClient();
      container.SwitchMode(GameModeDef<GameModeConnecting>{});
    }
  });
}

void GameModeMainMenu::PlayOffline()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeOfflineStaging>{});
  });
}

void GameModeMainMenu::Tutorial()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeTutorial>{}, GameInitSettings{});
  });
}

void GameModeMainMenu::PlaySingleplayer()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {
    auto & container = GetContainer();
    container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, false);
  });
}