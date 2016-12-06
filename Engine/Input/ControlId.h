#pragma once


enum class ControlType
{
  kInvalid,
  kKeyboard,
  kMouse,
};

static const int kMouseLeftButton = 1;
static const int kMouseMiddleButton = 2;
static const int kMouseRightButton = 3;


struct ControlId
{
  ControlType m_Type;
  int m_Index;
  int m_SubIndex;
};

ControlId CreateKeyboardBinding(int scan_code);
ControlId CreateMouseButtonBinding(int button);
ControlId CreateMousePointerBinding();
