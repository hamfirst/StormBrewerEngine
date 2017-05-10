#pragma once


enum class ControlType
{
  kInvalid,
  kKeyboard,
  kMouse,
  kGamePadConnection,
  kGamePad,
}; 

static const int kMouseLeftButton = 1;
static const int kMouseMiddleButton = 2;
static const int kMouseRightButton = 3;

enum class GamepadButton
{
  kA,
  kB,
  kX,
  kY,
  kSelect,
  kGuide,
  kStart,
  kL3,
  kR3,
  kL2,
  kR2,
  kDUp,
  kDDown,
  kDLeft,
  kDRight,
  kL1,
  kR1,
  kCount,
};

enum class GamepadAxis
{
  kLeftHorz,
  kLeftVert,
  kRightHorz,
  kRightVert,
  kCount,
};


struct ControlId
{
  ControlType m_Type;
  int m_Index;
  int m_SubIndex;
};

ControlId ENGINE_EXPORT CreateKeyboardBinding(int scan_code);
ControlId ENGINE_EXPORT CreateMouseButtonBinding(int button);
ControlId ENGINE_EXPORT CreateMousePointerBinding();
ControlId ENGINE_EXPORT CreateGamepadConnectionBinding(int gamepad_idx);
ControlId ENGINE_EXPORT CreateGamepadButtonBinding(int gamepad_idx, GamepadButton button);
ControlId ENGINE_EXPORT CreateGamepadAxisBinding(int gamepad_idx, GamepadAxis axis);

