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
  kR1,
  kR2,
  kR3,
  kL1,
  kL2,
  kL3,
  kDUp,
  kDDown,
  kDLeft,
  kDRight,
  kStart,
  kSelect,
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

ControlId CreateKeyboardBinding(int scan_code);
ControlId CreateMouseButtonBinding(int button);
ControlId CreateMousePointerBinding();
ControlId CreateGamepadConnectionBinding(int gamepad_idx);
ControlId CreateGamepadButtonBinding(int gamepad_idx, GamepadButton button);
ControlId CreateGamepadAxisBinding(int gamepad_idx, GamepadAxis axis);

