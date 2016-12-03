#pragma once

#include "Engine/Window/Window.h"

class WindowManager
{
public:

  Window CreateNewWindow(czstr title, int width, int height);

private:

  friend void EngineUpdate();
  friend class Window;

  void UpdateInput();
  void HandleKeypressMessage(uint32_t window_id, int scan_code, bool pressed);

  void AddWindowRef(uint32_t window_id);
  void DecWindowRef(uint32_t window_id);

  void Swap(uint32_t window_id);
  void CloseWindow(uint32_t window_id);

  NullOptPtr<InputState> GetInputState(uint32_t window_id);

  void SetWindowFocused(uint32_t window_id, bool focused);

  struct WindowState;
  std::unordered_map<uint32_t, WindowState> m_Windows;

};

extern WindowManager g_WindowManager;