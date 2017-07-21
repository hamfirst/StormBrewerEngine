
#include "GameClient/GameClientInputManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

GameClientInputManager::GameClientInputManager(GameContainer & container) :
  m_GameContainer(container)
{
  auto input_state = m_GameContainer.GetWindow().GetInputState();

  m_PointerHandle = 
    input_state->BindPointerControl(CreateMousePointerBinding(), 0, ControlBindingMode::kIgnoreLowerPriority, [this](PointerState & state) { HandleMouseMove(state); });

  m_MouseButtonHandle = 
    input_state->BindBinaryControl(CreateMouseButtonBinding(kMouseLeftButton), 0, ControlBindingMode::kIgnoreLowerPriority, [this](bool state) { HandleClick(state); });

  m_KeyboardCallbackLink =
    input_state->RegisterKeyboardPassThroughCallback([this](bool state, ControlId control_id) { HandleButtonPress(state, control_id.m_Index); });
}

GameClientInputManager::~GameClientInputManager()
{
  auto input_state = m_GameContainer.GetWindow().GetInputState();

  input_state->UnbindPointerControl(m_PointerHandle);
  input_state->UnbindBinaryControl(m_MouseButtonHandle);
}

void GameClientInputManager::Update()
{
  m_UIBlocking = m_GameContainer.GetClientSystems()->GetUIManager().IsBlocking();

  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
}

void GameClientInputManager::Render()
{

}

void GameClientInputManager::HandleMouseMove(PointerState & pointer_state)
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & stage = m_GameContainer.GetInstanceData()->GetStage();
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto world_space = camera.TransformFromScreenSpaceToWorldSpace(pointer_state.m_Pos);
  auto game_space = camera.TransformWorldSpaceToGameplaySpace(world_space);

}

void GameClientInputManager::HandleClick(bool state)
{
  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData();
  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

}

void GameClientInputManager::HandleButtonPress(bool state, int button)
{
  
}
