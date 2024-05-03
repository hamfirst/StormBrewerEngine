#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"
#include "GameClient/GameClientUIData.refl.meta.h"

#include "Game/NetworkEvents/GameNetworkEvents.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/GameController/Config/GameConfig.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Profiler/Profiler.h"

#include "Runtime/UI/UIResource.h"

#include "Foundation/Script/ScriptDataObject.h"

extern ConfigPtr<GameConfig> g_GameConfig;

GLOBAL_ASSET(UIResourcePtr, "./UIs/QuitPopup.ui", g_QuitPopup);

GameClientUIManager::GameClientUIManager(GameContainer & container, int local_index) :
  m_GameContainer(container),
  m_LocalIndex(local_index),
  m_WantsToQuit(false),
  m_PopupOpen(false)
{

}

GameClientUIManager::~GameClientUIManager()
{

}

void GameClientUIManager::Update()
{
  auto input_state = m_GameContainer.GetWindow().GetInputState();
  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_ESCAPE))
  {
    if(m_PopupOpen)
    {
      CancelPopup();
    }
    else
    {
      ShowQuitPopup();
    }
  }

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_F11))
  {
    m_DrawFPS = !m_DrawFPS;
  }

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_F12))
  {
    m_DrawProfileData = !m_DrawProfileData;
  }

  m_GameContainer.UpdateUIManager();

  GameClientUIData ui_data;

  auto ui_script_data = CreateScriptDataObject(m_GameContainer.GetUIManager()->GetScriptState(), GetScriptData());
  m_GameContainer.GetUIManager()->SetGlobal("hud_info", std::move(ui_script_data));
}

void GameClientUIManager::Render()
{
  auto & render_state = m_GameContainer.GetRenderState();

  m_GameContainer.GetUIManager()->RenderSpecial("DrawHud", render_state);
  m_GameContainer.GetUIManager()->Render(render_state);

  m_FPSClock.Update();

  if(m_DrawFPS)
  {
    std::string fps_data = std::to_string(m_FPSClock.GetFrameCount());
    g_TextManager.SetTextPos(Vector2f(40, 40) - render_state.GetRenderSize() / 2.0f);
    g_TextManager.SetPrimaryColor();
    g_TextManager.SetShadowColor();
    g_TextManager.SetTextMode(TextRenderMode::kOutlined);
    g_TextManager.ClearTextBounds();
    g_TextManager.RenderText(fps_data.data(), -1, 1, render_state);
  }

  if(m_DrawProfileData)
  {
    RenderProfilerData(render_state);
  }
}

void GameClientUIManager::ShowQuitPopup()
{
  auto & ui = GetUIManager();
  auto & game_interface = ui.CreateGameInterface();

  BIND_SCRIPT_INTERFACE(game_interface, this, Quit);
  BIND_SCRIPT_INTERFACE(game_interface, this, CancelPopup);

  ui.PushUIDef(g_QuitPopup);

  m_PopupOpen = true;
}

void GameClientUIManager::CancelPopup()
{
  GetUIManager().ClearUI();
  GetUIManager().ClearGameInterface();
  m_PopupOpen = false;
}

void GameClientUIManager::ShowTutorial()
{
  auto & render_state = m_GameContainer.GetRenderState();
}

bool GameClientUIManager::IsPopupOpen()
{
  return m_PopupOpen;
}

bool GameClientUIManager::IsBlocking()
{
  return GetUIManager().HasSelectedElement();
}

bool GameClientUIManager::WantsToQuit()
{
  return m_WantsToQuit;
}

UIManager & GameClientUIManager::GetUIManager()
{
  return *m_GameContainer.GetEngineState().GetUIManager();
}

GameClientUIData GameClientUIManager::GetScriptData()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetFullState();
  auto & global_data = game_state.m_InstanceData;
  auto & client_local = m_GameContainer.GetInstanceData()->GetClientLocalData(m_LocalIndex);
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  GameClientUIData data;

#ifdef NET_USE_ROUND_TIMER
  if(global_data.m_RoundState == RoundState::kPreRound || global_data.m_RoundState == RoundState::kRound)
  {
    static const bool kDisplayMinutes = true;
    if(kDisplayMinutes && global_data.m_RoundState != RoundState::kPreRound)
    {
      auto timer = global_data.m_RoundTimer / 60;
      auto minutes = timer / 60;
      auto seconds = timer % 60;

      char timer_str[20];
      snprintf(timer_str, sizeof(timer_str), "%d:%02d", minutes, seconds);

      data.timer = timer_str;
    }
    else
    {
      data.timer = std::to_string((global_data.m_RoundTimer / 60) + 1);
    }

    data.timer_scale = 1.0f - (global_data.m_RoundTimer % 60) / 60.0f;
    data.timer_pre_round = global_data.m_RoundState == RoundState::kPreRound;
  }
#endif

  return data;
}

void GameClientUIManager::Quit()
{
  m_WantsToQuit = true;
}