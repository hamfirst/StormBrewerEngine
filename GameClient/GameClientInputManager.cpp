
#include "GameClient/GameClientInputManager.h"
#include "GameClient/GameContainer.h"
#include "GameClient/GameClientEventSender.h"

#include "Game/ServerObjects/PlayerServerObject.refl.h"

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

  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();
  auto num_local_player = m_GameContainer.GetInstanceData()->GetLocalDataCount();

  auto input_state = m_GameContainer.GetWindow().GetInputState();

  for (std::size_t client_index = 0; client_index < num_local_player; ++client_index)
  {
    auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData(client_index);
    if (local_data.m_PlayerIndex == -1)
    {
      continue;
    }

    auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];

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

    ClientInput input;
    input.m_Controls = controls;
    input.m_Angle = GameNetVal::CreateFromFloat(atan2f(input_vec.y, input_vec.x));
    input.m_Strength = GameNetVal::CreateFromFloat(input_str);

    if (m_GameContainer.HasClient())
    {
      m_GameContainer.GetClient().UpdateInput(std::move(input), false);
    }
    else
    {
      auto & obj_manager = m_GameContainer.GetInstanceData()->GetServerObjectManager();
      auto player = obj_manager.GetReservedSlotObjectAs<PlayerServerObject>((int)local_data.m_PlayerIndex);

      if (player)
      {
        player->m_Controls = controls;
        player->m_InputAngle = input.m_Angle;
        player->m_InputStrength = input.m_Strength;
      }
    }

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
  if (m_GameContainer.GetInstanceData()->GetLocalDataCount() == 0)
  {
    return;
  }

  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData(0);
  if (local_data.m_PlayerIndex == -1)
  {
    return;
  }

  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & stage = m_GameContainer.GetInstanceData()->GetStage();
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

  auto world_space = camera.TransformFromScreenSpaceToWorldSpace(pointer_state.m_Pos);
  auto game_space = camera.TransformWorldSpaceToGameplaySpace(world_space);
}

void GameClientInputManager::HandleClick(bool state)
{
  if (m_GameContainer.GetInstanceData()->GetLocalDataCount() == 0)
  {
    return;
  }

  auto & local_data = m_GameContainer.GetInstanceData()->GetLocalData(0);
  if (local_data.m_PlayerIndex == -1)
  {
    return;
  }

  auto & game_state = m_GameContainer.GetInstanceData()->GetGameState();
  auto & local_player = game_state.m_Players[(int)local_data.m_PlayerIndex];
  auto & camera = m_GameContainer.GetClientSystems()->GetCamera();

}

void GameClientInputManager::HandleButtonPress(bool state, int button)
{
  
}
