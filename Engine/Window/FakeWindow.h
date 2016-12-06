#pragma once

#include "Engine/Window/Window.h"

class FakeWindow
{
public:

  FakeWindow(const Box & window_geo, const Delegate<void> & make_current_cb, const Delegate<void> & swap_cb, const Delegate<void> & close_cb,
    const Delegate<void, NullOptPtr<Box>> & start_ime, const Delegate<void> stop_ime);

  FakeWindow(const FakeWindow & rhs) = delete;
  FakeWindow(FakeWindow && rhs) = delete;

  FakeWindow & operator = (const FakeWindow & rhs) = delete;
  FakeWindow & operator = (FakeWindow && rhs) = delete;

  void HandleKeyPressMessage(int sdl_key, int scan_code, bool pressed);
  void HandleMouseButtonPressMessage(int button, bool pressed);
  void HandleTextInputCommit(czstr character);
  void HandleTextInputComposition(czstr composition);

  void SetWindowKeyboardFocused(bool focused);
  void SetWindowMouseFocused(bool focused);
  void SetWindowPos(const Vector2 & pos);
  void SetWindowSize(const Vector2 & size);

  const Window & GetWindow() { return m_Window; }

private:
  friend class WindowManager;

  Delegate<void> m_MakeCurrentDelegate;
  Delegate<void> m_SwapDelegate;
  Delegate<void> m_CloseDelegate;
  Delegate<void, NullOptPtr<Box>> m_StartImeDelegate;
  Delegate<void> m_StopImeDelegate;

  Window m_Window;
};
