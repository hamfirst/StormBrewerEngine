#pragma once

#include "Engine/Window/Window.h"

class ENGINE_EXPORT FakeWindow
{
public:

  FakeWindow(const Box & window_geo, const Delegate<void> & make_current_cb, const Delegate<void> & swap_cb, const Delegate<void> & bind_default_rt,
    const Delegate<void, int, int> & set_mouse_cb, const Delegate<void> & close_cb,
    const Delegate<void, NullOptPtr<Box>> & start_ime, const Delegate<void> stop_ime,
    const Delegate<void> & grab_mouse, const Delegate<void> release_mouse);

  FakeWindow(const FakeWindow & rhs) = delete;
  FakeWindow(FakeWindow && rhs) = delete;

  FakeWindow & operator = (const FakeWindow & rhs) = delete;
  FakeWindow & operator = (FakeWindow && rhs) = delete;

  void HandleKeyPressMessage(int sdl_key, int scan_code, bool pressed);
  void HandleMouseMoveMessage(int x, int y);
  void HandleMouseWheelMessage(int dv);
  void HandleMouseButtonPressMessage(int button, bool pressed);
  void HandleTextInputCommit(czstr character);
  void HandleTextInputComposition(czstr composition);

  void SetWindowKeyboardFocused(bool focused);
  void SetWindowMouseFocused(bool focused);
  void SetWindowPos(const Vector2 & pos);
  void SetWindowSize(const Vector2 & size);

  Window & GetWindow() { return m_Window; }
  const Window & GetWindow() const { return m_Window; }

private:
  friend class WindowManager;

  Delegate<void> m_MakeCurrentDelegate;
  Delegate<void> m_SwapDelegate;
  Delegate<void> m_BindDefaultRenderTargetDelegate;
  Delegate<void, int, int> m_SetMousePosDelegate;
  Delegate<void> m_CloseDelegate;
  Delegate<void, NullOptPtr<Box>> m_StartImeDelegate;
  Delegate<void> m_StopImeDelegate;
  Delegate<void> m_GrabWindowDelegate;
  Delegate<void> m_ReleaseWindowDelegate;

  Window m_Window;
};
