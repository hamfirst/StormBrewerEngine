#pragma once

#include "Engine/Window/Window.h"

class FakeWindow;
class TextInputContext;

struct WindowState;

class ENGINE_EXPORT WindowManager
{
public:

  Window CreateNewWindow(czstr title, int width, int height, bool fullscreen = false);

  void HandleFullscreenChanged(uint32_t window_id, bool enabled);

private:

  Window CreateFakeWindow(FakeWindow * window, const Box & window_geo);

  friend void EngineUpdate();
  friend class Window;
  friend class FakeWindow;
  friend class TextInputContext;

  void HandleKeyPressMessage(uint32_t window_id, int key_code, int scan_code, bool pressed);
  void HandleMouseButtonPressMessage(uint32_t window_id, int button, bool pressed);
  void HandleMouseMotionMessage(uint32_t window_id, int x, int y);
  void HandleMouseWheelMessage(uint32_t window_id, int dv);
  void HandleControllerConnectedMessage(uint32_t window_id, int x, int y);
  void HandleTextInputCommit(uint32_t window_id, czstr character);
  void HandleTextInputComposition(uint32_t window_id, czstr composition);

  void SetWindowKeyboardFocused(uint32_t window_id, bool focused);
  void SetWindowMouseFocused(uint32_t window_id, bool focused);
  void SetWindowPos(uint32_t window_id, const Vector2 & pos);
  void SetWindowSize(uint32_t window_id, const Vector2 & size);

  void AddWindowRef(uint32_t window_id);
  void DecWindowRef(uint32_t window_id);

  void UpdateWindow(uint32_t window_id);
  void MakeCurrent(uint32_t window_id);
  void BindDefaultRenderTarget(uint32_t window_id);
  void Swap(uint32_t window_id);
  void SetMousePos(uint32_t window_id, int x, int y);
  void SetVsyncEnabled(uint32_t window_id, bool enabled);
  void SetFullscreen(uint32_t window_id, bool enabled);
  bool IsFullScreen(uint32_t window_id);
  void CloseWindow(uint32_t window_id);
  void GrabMouse(uint32_t window_id);
  void ReleaseMouse(uint32_t window_id);

  Vector2 GetWindowSize(uint32_t window_id);
  Box GetWindowGeometry(uint32_t window_id);

  void SetTextInputContext(uint32_t window_id, const std::shared_ptr<TextInputContext> & context, NullOptPtr<Box> input_box);
  void ClearTextInputContext(uint32_t window_id, NotNullPtr<TextInputContext> context);
  void ClearAllTextInputContext(uint32_t window_id);
  bool IsTextInputContextActive(uint32_t window_id, NotNullPtr<TextInputContext> context);

  NullOptPtr<InputState> GetInputState(uint32_t window_id);

  uint32_t m_NextFakeWindowId = 1000000;

};

extern WindowManager g_WindowManager;