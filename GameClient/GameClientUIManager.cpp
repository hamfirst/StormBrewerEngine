#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"

#include "Game/GameNetworkEvents.refl.h"
#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"
#include "Game/Configs/GameConfig.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Audio/AudioManager.h"

#include "Runtime/UI/UIResource.h"

GLOBAL_ASSET(UIResourcePtr, "./UIs/HUD.ui", g_GameClientUI);

extern ConfigPtr<GameConfig> g_GameConfig;

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container),
  m_UIManager(container.GetWindow()),
  m_WantsToQuit(false),
  m_DisabledPopup(false)
{
  auto & render_state = container.GetRenderState();

  m_QuitPopup.Emplace(m_UIManager, "quit", nullptr, Box::FromFrameCenterAndSize(Vector2(0, 0), Vector2(250, 100)),
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

  m_HudHandle = m_UIManager.AllocateElementFromDef("ui", *g_GameClientUI.GetData());
}

GameClientUIManager::~GameClientUIManager()
{

}

void GameClientUIManager::Update()
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetGlobalInstanceData();
  auto & obj_manager = m_GameContainer.GetInstanceData()->GetFullState().m_ServerObjectManager;
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto resolution = camera.GetGameResolution();
  auto input_state = m_GameContainer.GetWindow().GetInputState();

  if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_ESCAPE))
  {
    TogglePopup();
  }

  auto hud = m_HudHandle.Resolve();
  if (hud)
  {

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

  auto okay_box = Box::FromFrameCenterAndSize(Vector2(0, -40), Vector2(150, 30));
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
    auto & render_state = m_GameContainer.GetRenderState();
    auto half_res = Vector2(render_state.GetRenderWidth(), render_state.GetRenderHeight()) / 2;

    auto & resources = m_GameContainer.GetClientGlobalResources();
    m_Tutorial = m_UIManager.AllocateElementFromDef("tutorial", *resources.Tutorial.GetData());
    m_Tutorial->SetInput(COMPILE_TIME_CRC32_STR("Low"), 1.0f);

    m_MuteButton.Emplace(m_UIManager, "mute", nullptr, half_res - Vector2(60, 20), false, &m_GameContainer.GetClientGlobalResources().UISoundEffects);
    m_MusicButton.Emplace(m_UIManager, "music", nullptr, half_res - Vector2(100, 20), true, &m_GameContainer.GetClientGlobalResources().UISoundEffects);
    m_FullscreenButton.Emplace(m_UIManager, "fullscreen", nullptr, half_res - Vector2(20, 20), m_GameContainer.GetWindow(), &m_GameContainer.GetClientGlobalResources().UISoundEffects);

    m_QuitPopup->Toggle();
  }
}
