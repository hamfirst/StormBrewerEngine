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
GLOBAL_ASSET(UIResourcePtr, "./UIs/Tutorial.ui", g_GameTutorialUI);

extern ConfigPtr<GameConfig> g_GameConfig;

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container),
  m_UIManager(container.GetWindow()),
  m_WantsToQuit(false),
  m_DisabledPopup(false)
{
  auto & render_state = container.GetRenderState();
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

  m_UIManager.Update(*input_state, m_GameContainer.GetRenderState(), camera.GetPosition());
}

void GameClientUIManager::Render()
{
  m_UIManager.Render(m_GameContainer.GetRenderState(), m_GameContainer.GetRenderUtil());
}

void GameClientUIManager::ShowTutorial()
{
  auto & render_state = m_GameContainer.GetRenderState();
}

bool GameClientUIManager::IsPopupOpen()
{
  return false;
}

void GameClientUIManager::DisablePopup()
{
  m_DisabledPopup = true;
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

}
