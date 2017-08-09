
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"

#include "Game/GameNetworkEvents.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container),
  m_UIManager(container.GetWindow())
{
  auto & render_state = container.GetRenderState();

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
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
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

  m_UIManager.Update(*m_GameContainer.GetWindow().GetInputState(), m_GameContainer.GetRenderState(), camera.GetPosition());
}

void GameClientUIManager::Render()
{
  m_UIManager.Render(m_GameContainer.GetRenderState(), m_GameContainer.GetRenderUtil());
}

bool GameClientUIManager::IsBlocking()
{
  return m_UIManager.HasSelectedElement();
}

UIClickablePtr GameClientUIManager::CreateClickable(const Box & active_area)
{
  return m_UIManager.AllocateClickable(active_area);
}
