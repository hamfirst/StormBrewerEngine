
#include "Engine/EngineCommon.h"
#include "Engine/Input/ControlId.h"

ControlId CreateKeyboardBinding(int scan_code)
{
  return ControlId{ ControlType::kKeyboard, scan_code, 0 };
}
