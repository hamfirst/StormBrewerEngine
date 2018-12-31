#pragma once

#include "Foundation/Delegate/DelegateLink.h"

#include "Engine/EngineCommon.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Input/GamepadState.h"

#include <SDL2/SDL_keycode.h>

class Window;

using KeyboardPassthroughCallbackLink = DelegateLink<void, bool, ControlId>;

class ENGINE_EXPORT InputState
{
public:
  InputState();

  void Update(bool in_keyboard_focus, bool in_mouse_focus, bool text_input_active, const Box & window_geo, bool query_state);

  BinaryControlHandle BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void UnbindBinaryControl(const BinaryControlHandle & handle);

  ScalarControlHandle BindScalarControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, float> & callback);
  void UnbindScalarControl(const ScalarControlHandle & handle);
  
  PointerControlHandle BindPointerControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback);
  void UnbindPointerControl(const PointerControlHandle & handle);

  void SetBinaryControlInputCallback(const Delegate<void, const ControlId &> & callback);
  void ClearBinaryControlInputCallback();

  bool GetKeyState(int scan_code);
  bool GetKeyPressedThisFrame(int scan_code);
  bool GetMouseButtonState(int button);
  bool GetMousePressedThisFrame(int button);
  PointerState GetPointerState();
  bool GetGamepadConnected(int gamepad_idx);
  bool GetGamepadButtonState(int gamepad_idx, GamepadButton button);
  bool GetGamepadButtonPressedThisFrame(int gamepad_idx, GamepadButton button);
  float GetGamepadAxis(int gamepad_idx, GamepadAxis axis);
  Vector2f GetGamepadJoystick(int gamepad_idx, GamepadJoystick joystick);

  KeyboardPassthroughCallbackLink RegisterKeyboardPassThroughCallback(const Delegate<void, bool, ControlId> & del);

  static void ApplyDeadZone(Vector2f & input, float dead_zone = 0.30f);
private:

  friend class ControlHandle;
  friend class KeyboardState;
  friend class MouseState;
  friend class WindowManager;

  void HandleKeyPressMessage(int scan_code, bool pressed, bool text_input_active);
  void HandleMouseButtonPressMessage(int button, bool pressed, bool in_focus);
  void HandleMouseMoveMessage(int x, int y, const Box & window_geo, bool in_focus);
  void HandleMouseWheelMessage(int dv);

private:

  KeyboardState m_KeyboardState;
  MouseState m_MouseState;
  GamepadState m_GamepadState;

  Delegate<void, const ControlId &> m_BinaryControlCallback;
};
