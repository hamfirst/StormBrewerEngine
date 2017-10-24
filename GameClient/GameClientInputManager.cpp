#include "GameClient/GameClientCommon.h"
#include "GameClient/GameClientInputManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"

#include "Game/ServerObjects/Player/PlayerServerObject.refl.h"

#include "Engine/Window/Window.h"
#include "Engine/Input/ControlId.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"

#include "SDL2/SDL_keycode.h"

GameClientInputManager::GameClientInputManager(GameContainer & container) :
  m_GameContainer(container),
  m_PrevControls(0)
{
  for (int index = 0; index < kMaxPlayers; ++index)
  {
    m_GamepadBindings[index] = 0;
  }

  auto input_state = m_GameContainer.GetWindow().GetInputState();

  m_PointerHandle = 
    input_state->BindPointerControl(CreateMousePointerBinding(), 0, ControlBindingMode::kIgnoreLowerPriority, [this](PointerState state) { HandleMouseMove(state); });

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

  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
  auto num_local_player = m_GameContainer.GetInstanceData()->GetNumLocalData();

  auto input_state = m_GameContainer.GetWindow().GetInputState();

  for (std::size_t client_index = 0; client_index < num_local_player; ++client_index)
  {
    uint8_t controls = 0;
    auto gamepad_index = m_GamepadBindings[client_index];

    float x = 0;
    float y = 0;

    if (client_index == 0)
    {
      if (input_state->GetKeyState(SDL_SCANCODE_W) || input_state->GetKeyState(SDL_SCANCODE_UP))
      {
        y = 1.0f;
      }

      if (input_state->GetKeyState(SDL_SCANCODE_S) || input_state->GetKeyState(SDL_SCANCODE_DOWN))
      {
        y = -1.0f;
      }

      if (input_state->GetKeyState(SDL_SCANCODE_D) || input_state->GetKeyState(SDL_SCANCODE_RIGHT))
      {
        x = 1.0f;
      }

      if (input_state->GetKeyState(SDL_SCANCODE_A) || input_state->GetKeyState(SDL_SCANCODE_LEFT))
      {
        x = -1.0f;
      }
    }

    if (x == 0 && y == 0)
    {
      x = input_state->GetGamepadAxis(gamepad_index, GamepadAxis::kLeftHorz);
      y = -input_state->GetGamepadAxis(gamepad_index, GamepadAxis::kLeftVert);
    }

    Vector2f input_vec = { x, y };
    InputState::ApplyDeadZone(input_vec);

    auto input_str = glm::length(input_vec);

    if (input_state->GetKeyPressedThisFrame(SDL_SCANCODE_SPACE) || input_state->GetGamepadButtonPressedThisFrame(gamepad_index, GamepadButton::kA))
    {
      SendEvent(client_index, JumpEvent{});
    }

    ClientInput input;
    input.m_JumpHeld = input_state->GetKeyState(SDL_SCANCODE_SPACE) || input_state->GetGamepadButtonState(gamepad_index, GamepadButton::kA);
    input.m_XInput = GameNetVal::CreateFromFloat(input_vec.x);
    SendInput(client_index, input);

    if (client_index == 0)
    {
      m_PrevControls = controls;
    }
  }
}

void GameClientInputManager::Render()
{

}

void GameClientInputManager::BindGamepad(int local_player_index, int gamepad_index)
{
  m_GamepadBindings[local_player_index] = gamepad_index;
}

void GameClientInputManager::HandleMouseMove(PointerState & pointer_state)
{
  if (m_GameContainer.GetInstanceData()->GetNumLocalData() == 0)
  {
    return;
  }

  auto & local_data = m_GameContainer.GetInstanceData()->GetClientLocalData(0);
  if (local_data.m_PlayerIndex == -1)
  {
    return;
  }

  auto & game_state = m_GameContainer.GetInstanceData()->GetGlobalInstanceData();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & stage = m_GameContainer.GetInstanceData()->GetStage();
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto world_space = camera.TransformFromScreenSpaceToWorldSpace(pointer_state.m_Pos);
  auto game_space = camera.TransformWorldSpaceToGameplaySpace(world_space);
}

void GameClientInputManager::HandleClick(bool state)
{
  if (m_GameContainer.GetInstanceData()->GetNumLocalData() == 0)
  {
    return;
  }

  auto & local_data = m_GameContainer.GetInstanceData()->GetClientLocalData(0);
  if (local_data.m_PlayerIndex == -1)
  {
    return;
  }

  auto & game_state = m_GameContainer.GetInstanceData()->GetGlobalInstanceData();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

}

void GameClientInputManager::HandleButtonPress(bool state, int button)
{
  
}

void GameClientInputManager::SendInput(std::size_t client_index, ClientInput & input)
{
  auto & game_state = m_GameContainer.GetInstanceData()->GetGlobalInstanceData();
  auto & local_data = m_GameContainer.GetInstanceData()->GetClientLocalData(client_index);
  if (local_data.m_PlayerIndex == -1)
  {
    return;
  }

  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

  if (m_GameContainer.HasClient())
  {
    m_GameContainer.GetClient().UpdateInput(std::move(input), false);
  }
  else
  {
    m_GameContainer.GetInstanceData()->PushLocalInput(client_index, input, 0);
  }
}

template <typename EventType>
void GameClientInputManager::SendEvent(std::size_t client_index, const EventType & event)
{
  m_GameContainer.GetInstanceData()->GetEventSender().SendClientEvent(event, client_index);
}
