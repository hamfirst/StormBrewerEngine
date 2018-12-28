
#include "Engine/EngineCommon.h"
#include "Engine/Window/FakeWindow.h"
#include "Engine/Window/WindowManager.h"

FakeWindow::FakeWindow(const Box & window_geo, const Delegate<void> & make_current_cb, const Delegate<void> & swap_cb, const Delegate<void> & bind_default_rt,
                       const Delegate<void, int, int> & set_mouse_cb, const Delegate<void> & close_cb,
                       const Delegate<void, NullOptPtr<Box>> & start_ime_cb, const Delegate<void> stop_ime_cb,
                       const Delegate<void> & grab_mouse, const Delegate<void> release_mouse) :
  m_Window(g_WindowManager.CreateFakeWindow(this, window_geo)),
  m_MakeCurrentDelegate(make_current_cb),
  m_SwapDelegate(swap_cb),
  m_BindDefaultRenderTargetDelegate(bind_default_rt),
  m_SetMousePosDelegate(set_mouse_cb),
  m_CloseDelegate(close_cb),
  m_StartImeDelegate(start_ime_cb),
  m_StopImeDelegate(stop_ime_cb),
  m_GrabWindowDelegate(grab_mouse),
  m_ReleaseWindowDelegate(release_mouse)
{

}

void FakeWindow::HandleMouseMoveMessage(int x, int y)
{
  g_WindowManager.HandleMouseMotionMessage(m_Window.m_WindowId, x, y);
}

void FakeWindow::HandleKeyPressMessage(int sdl_key, int scan_code, bool pressed)
{
  g_WindowManager.HandleKeyPressMessage(m_Window.m_WindowId, sdl_key, scan_code, pressed);
}

void FakeWindow::HandleMouseButtonPressMessage(int button, bool pressed)
{
  g_WindowManager.HandleMouseButtonPressMessage(m_Window.m_WindowId, button, pressed);
}

void FakeWindow::HandleTextInputCommit(czstr character)
{
  g_WindowManager.HandleTextInputCommit(m_Window.m_WindowId, character);
}

void FakeWindow::HandleTextInputComposition(czstr composition)
{
  g_WindowManager.HandleTextInputCommit(m_Window.m_WindowId, composition);
}

void FakeWindow::SetWindowKeyboardFocused(bool focused)
{
  g_WindowManager.SetWindowKeyboardFocused(m_Window.m_WindowId, focused);
}

void FakeWindow::SetWindowMouseFocused(bool focused)
{
  g_WindowManager.SetWindowMouseFocused(m_Window.m_WindowId, focused);
}

void FakeWindow::SetWindowPos(const Vector2 & pos)
{
  g_WindowManager.SetWindowPos(m_Window.m_WindowId, pos);
}

void FakeWindow::SetWindowSize(const Vector2 & size)
{
  g_WindowManager.SetWindowSize(m_Window.m_WindowId, size);
}
