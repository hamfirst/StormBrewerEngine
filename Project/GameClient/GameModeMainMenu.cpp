#include "GameClient/GameClientCommon.h"
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

#include "Runtime/Atlas/AtlasResource.h"

GLOBAL_ASSET(AtlasPtr, "./UIs/TestAtlas.atlas", g_TestAtlas);

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
  logo_data.m_PositionX = 0;
  logo_data.m_PositionY = 0;

  auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

  m_TitleImage = m_UIManager.AllocateFullTexture("logo", nullptr, logo_init, logo_data);

  m_PlayOnline.Emplace(m_UIManager, "playonline", nullptr, 
    Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 125 - half_res.y), Vector2(120, 25)), "Play Online");
  m_PlayOnline->SetOnClickCallback([this] { PlayOnline(); });

  m_Tutorial.Emplace(m_UIManager, "tutorial", nullptr,
    Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 100 - half_res.y), Vector2(120, 18)), "Tutorial");
  m_Tutorial->SetOnClickCallback([this] { Tutorial(); });

  m_PlayOffline.Emplace(m_UIManager, "playoffline", nullptr, 
    Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 80 - half_res.y), Vector2(120, 18)), "Local Multiplayer");
  m_PlayOffline->SetOnClickCallback([this] { PlayOffline(); });

  m_PlaySingleplayer.Emplace(m_UIManager, "playsingleplayer", nullptr,
    Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 60 - half_res.y), Vector2(120, 18)), "Single Player");
  m_PlaySingleplayer->SetOnClickCallback([this] { PlaySingleplayer(); });

  m_CreateOnlineMatch.Emplace(m_UIManager, "creategame", nullptr,
                             Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 35 - half_res.y), Vector2(120, 18)), "Create Private Match");
  m_CreateOnlineMatch->SetOnClickCallback([this] { CreatePrivateMatch(); });

  m_JoinOnlineMatch.Emplace(m_UIManager, "joingame", nullptr,
                             Box::FromFrameCenterAndSize(Vector2(-half_res.x + 75, 15 - half_res.y), Vector2(120, 18)), "Join Private Match");
  m_JoinOnlineMatch->SetOnClickCallback([this] { JoinPrivateMatch(); });

  m_MuteButton.Emplace(m_UIManager, "mute", nullptr, half_res - Vector2(60, 20), false);
  m_MusicButton.Emplace(m_UIManager, "music", nullptr, half_res - Vector2(100, 20), true);
  m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, half_res - Vector2(20, 20), container.GetWindow());

  if (container.GetSave().GetSaveData().m_WatchedTutorial == false)
  {
    m_TutorialPrompt.Emplace(m_UIManager, "tutorialprompt", nullptr, 
      Box::FromFrameCenterAndSize(render_state.GetRenderSize() * 0.5f, Vector2(270, 100)), 
      "First time playing? Why not watch the tutorial?");
    m_TutorialPrompt->SetOnOkayCallback([this] { Tutorial(); });
    m_TutorialPrompt->Show();

    container.GetSave().GetSaveData().m_WatchedTutorial = true;
    container.GetSave().RequestSave();
  }


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

  //g_MusicManager.CutTo(GetContainer().GetClientGlobalResources().MainMenuMusic, 0.5f);
}

void GameModeMainMenu::Update()
{
  m_Sequencer.Update();

  auto & container = GetContainer();
  auto & render_state = container.GetRenderState();

  container.GetWindow().Update();

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
  g_TestAtlas->Render(render_state, "Bubble", Box::FromPoints(Vector2(0, 0), Vector2(128, 128)));
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

    auto & container = GetContainer();
    if (g_AccountName != nullptr)
    {
      auto & net_init_settings = container.GetNetworkInitSettings();
      net_init_settings.m_UserName = g_AccountName;
    }

    container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinOnline);
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

    auto & game_container = GetContainer();
    game_container.SwitchMode(GameModeDef<GameModeSinglePlayerBots>{}, GameInitSettings{}, false);
  });
}


void GameModeMainMenu::CreatePrivateMatch()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {

    auto & game_container = GetContainer();
    if (g_AccountName != nullptr)
    {
      auto & net_init_settings = game_container.GetNetworkInitSettings();
      net_init_settings.m_UserName = g_AccountName;
    }

    game_container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kCreatePrivate);
  });
}

void GameModeMainMenu::JoinPrivateMatch()
{
  auto & container = GetContainer();

  m_Sequencer.Push(0.5f, [this](float val) {
    m_Fader->SetActive();
    auto & fader_data = m_Fader->GetData();
    fader_data.m_ColorA = val;
  });

  m_Sequencer.Push(0.0f, [this](float val) {

    auto & game_container = GetContainer();
    if (g_AccountName != nullptr)
    {
      auto & net_init_settings = game_container.GetNetworkInitSettings();
      net_init_settings.m_UserName = g_AccountName;
    }

    game_container.SwitchMode(GameModeDef<GameModeNameSelect>{}, GameModeNameSelectNextScreen::kJoinOnline);
  });
}