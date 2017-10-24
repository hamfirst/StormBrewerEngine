#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"

#include "Game/GameNetworkEvents.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Audio/AudioManager.h"

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container),
  m_UIManager(container.GetWindow()),
  m_WantsToQuit(false),
  m_DisabledPopup(false)
{
  auto & render_state = container.GetRenderState();

  m_QuitPopup.Emplace(m_UIManager, "quit", nullptr, Box::FromFrameCenterAndSize(render_state.GetRenderSize() * 0.5f, Vector2(250, 100)),
    "Quit To Main Menu?", &m_GameContainer.GetClientGlobalResources().UISoundEffects);
  m_QuitPopup->SetOnOkayCallback([this] { Quit(); });
  m_QuitPopup->SetOnCancelCallback([this] 
  { 
    if (m_Tutorial)
    {
      m_Tutorial->Destroy();
      m_Tutorial.Clear();
      m_TutorialOkay.Clear();
    }

    m_MuteButton.Clear();
    m_MusicButton.Clear();
    m_FullscreenButton.Clear();
  });

#ifdef NET_USE_COUNTDOWN
  m_CountdownCaption = m_UIManager.AllocateText("countdown_caption");
  auto & countdown_caption_data = m_CountdownCaption->GetData();
  countdown_caption_data.m_PositionX = (float)(render_state.GetRenderWidth() / 2);
  countdown_caption_data.m_PositionY = (float)(render_state.GetRenderHeight() / 2) + 20.0f;
  countdown_caption_data.m_Text = "Game Starts In...";
  countdown_caption_data.m_FontId = -1;
  countdown_caption_data.m_TextMode = 2;
  countdown_caption_data.m_Centered = 1;

  m_Countdown = m_UIManager.AllocateText("countdown");
  auto & countdown_data = m_Countdown->GetData();
  countdown_data.m_PositionX = (float)(render_state.GetRenderWidth() / 2);
  countdown_data.m_PositionY = (float)(render_state.GetRenderHeight() / 2);
  countdown_data.m_FontId = -2;
  countdown_data.m_TextMode = 2;
  countdown_data.m_Centered = 1;
#endif

#ifdef NET_USE_ROUND_TIMER
  m_RoundTimerCaption = m_UIManager.AllocateText("round_timer_caption");
  auto & round_timer_caption_data = m_RoundTimerCaption->GetData();
  round_timer_caption_data.m_PositionX = (float)(render_state.GetRenderWidth() / 2);
  round_timer_caption_data.m_PositionY = (float)(render_state.GetRenderHeight()) - 6;
  round_timer_caption_data.m_Text = "Round Timer";
  round_timer_caption_data.m_FontId = -1;
  round_timer_caption_data.m_TextMode = 2;
  round_timer_caption_data.m_Centered = 1;

  m_RoundTimer = m_UIManager.AllocateText("round_timer");
  auto & round_timer_data = m_RoundTimer->GetData();
  round_timer_data.m_PositionX = (float)(render_state.GetRenderWidth() / 2);
  round_timer_data.m_PositionY = (float)(render_state.GetRenderHeight() - 21);
  round_timer_data.m_FontId = -2;
  round_timer_data.m_TextMode = 2;
  round_timer_data.m_Centered = 1;
#endif

}

GameClientUIManager::~GameClientUIManager()
{

}

void GameClientUIManager::Update()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetGlobalInstanceData();
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto resolution = camera.GetGameResolution();

#ifdef NET_USE_COUNTDOWN
  if (game_state.m_Countdown > 0)
  {
    m_Countdown->SetEnabled();
    m_CountdownCaption->SetEnabled();
    auto & countdown_data = m_Countdown->GetData();
    countdown_data.m_Text = std::to_string((int)game_state.m_Countdown / 60 + 1);
  }
  else
  {
    m_CountdownCaption->SetDisabled();
    m_Countdown->SetDisabled();
  }
#endif

#ifdef NET_USE_ROUND_TIMER

#ifdef NET_USE_COUNTDOWN
  if (game_state.m_Countdown > 0)
  {
    m_RoundTimer->SetDisabled();
    m_RoundTimerCaption->SetDisabled();
  }
  else
  {
    m_RoundTimer->SetEnabled();
    m_RoundTimerCaption->SetEnabled();
  }
#endif

  auto & round_timer_data = m_RoundTimer->GetData();
  round_timer_data.m_Text = std::to_string((int)game_state.m_RoundTimer / 60);
#endif

  auto input_state = m_GameContainer.GetWindow().GetInputState();

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_ESCAPE))
  {
    TogglePopup();
  }

  m_UIManager.Update(*input_state, m_GameContainer.GetRenderState(), camera.GetPosition());
}

void GameClientUIManager::Render()
{
  m_UIManager.Render(m_GameContainer.GetRenderState(), m_GameContainer.GetRenderUtil());
}

void GameClientUIManager::ShowTutorial()
{
  auto & resources = m_GameContainer.GetClientGlobalResources();
  auto & render_state = m_GameContainer.GetRenderState();

  m_Tutorial = m_UIManager.AllocateElementFromDef("tutorial", *resources.Tutorial.GetData());
  m_Tutorial->SetInput(COMPILE_TIME_CRC32_STR("Low"), 0.0f);

  auto okay_box = Box::FromFrameCenterAndSize(Vector2(render_state.GetRenderWidth() / 2, render_state.GetRenderHeight() / 2 - 40), Vector2(150, 30));
  m_TutorialOkay.Emplace(m_UIManager, "tutorial_okay", nullptr, okay_box, "Okay", &resources.UISoundEffects);
  m_TutorialOkay->SetOnClickCallback([this] { TogglePopup(); });
}

bool GameClientUIManager::IsPopupOpen()
{
  return m_Tutorial || m_QuitPopup->IsShown();
}

void GameClientUIManager::DisablePopup()
{
  m_DisabledPopup = true;

  if (m_QuitPopup->IsShown())
  {
    m_QuitPopup->Toggle();
  }
}

bool GameClientUIManager::IsBlocking()
{
  return m_UIManager.HasSelectedElement();
}

bool GameClientUIManager::WantsToQuit()
{
  return m_WantsToQuit;
}

UIClickablePtr GameClientUIManager::CreateClickable(const Box & active_area)
{
  return m_UIManager.AllocateClickable(active_area);
}

UIManager & GameClientUIManager::GetUIManager()
{
  return m_UIManager;
}

void GameClientUIManager::Quit()
{
  m_WantsToQuit = true;
}

void GameClientUIManager::TogglePopup()
{
  if (m_QuitPopup->IsShown())
  {
    m_QuitPopup->Toggle();

    if (m_Tutorial)
    {
      m_Tutorial->Destroy();
      m_TutorialOkay.Clear();
      m_Tutorial.Clear();
    }

    m_MuteButton.Clear();
    m_MusicButton.Clear();
    m_FullscreenButton.Clear();
  }
  else if (m_Tutorial)
  {
    m_Tutorial->Destroy();
    m_TutorialOkay.Clear();
    m_Tutorial.Clear();
  }
  else if(m_DisabledPopup == false)
  {
    m_QuitPopup->Toggle();

    auto & resources = m_GameContainer.GetClientGlobalResources();
    m_Tutorial = m_UIManager.AllocateElementFromDef("tutorial", *resources.Tutorial.GetData());
    m_Tutorial->SetInput(COMPILE_TIME_CRC32_STR("Low"), 1.0f);

    auto & render_state = m_GameContainer.GetRenderState();

    m_MuteButton.Emplace(m_UIManager, "mute", nullptr, render_state.GetRenderSize() - Vector2(60, 20), false, &m_GameContainer.GetClientGlobalResources().UISoundEffects);
    m_MusicButton.Emplace(m_UIManager, "music", nullptr, render_state.GetRenderSize() - Vector2(100, 20), true, &m_GameContainer.GetClientGlobalResources().UISoundEffects);
    m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, render_state.GetRenderSize() - Vector2(20, 20), 
      m_GameContainer.GetWindow(), &m_GameContainer.GetClientGlobalResources().UISoundEffects);
  }
}
