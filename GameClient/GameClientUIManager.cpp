
#include "GameClient/GameClientUIManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"
#include "GameClient/GameCamera.h"
#include "GameClient/GameClientSystems.h"

#include "Game/GameNetworkEvents.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"

GameClientUIManager::GameClientUIManager(GameContainer & container) :
  m_GameContainer(container)
{

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

  m_UIManager.Update(*m_GameContainer.GetWindow().GetInputState(), m_GameContainer.GetRenderState());
}

void GameClientUIManager::Render()
{
  m_UIManager.Render(m_GameContainer.GetRenderState(), m_GameContainer.GetRenderUtil());
}

bool GameClientUIManager::IsBlocking()
{
  return m_UIManager.HasSelectedElement();
}
