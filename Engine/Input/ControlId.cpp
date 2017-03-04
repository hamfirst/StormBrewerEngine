
#include "Engine/EngineCommon.h"
#include "Engine/Input/ControlId.h"

ControlId CreateKeyboardBinding(int scan_code)
{
  return ControlId{ ControlType::kKeyboard, scan_code, 0 };
}

ControlId CreateMouseButtonBinding(int button)
{
  return ControlId{ ControlType::kMouse, button, 0 };
}

ControlId CreateMousePointerBinding()
{
  return ControlId{ ControlType::kMouse, -1, 0 };
}

ControlId CreateGamepadConnectionBinding(int gamepad_idx)
{
  return ControlId{ ControlType::kGamePadConnection, gamepad_idx, 0 };
}

ControlId CreateGamepadButtonBinding(int gamepad_idx)
{
  return ControlId{ ControlType::kGamePadConnection, gamepad_idx, 0 };
}

ControlId CreateGamepadButtonBinding(int gamepad_idx, GamepadButton button)
{
  return ControlId{ ControlType::kGamePadConnection, gamepad_idx, (int)button };
}

ControlId CreateGamepadAxisBinding(int gamepad_idx, GamepadAxis axis)
{
  return ControlId{ ControlType::kGamePadConnection, gamepad_idx, (int)axis };
}
