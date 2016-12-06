
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
