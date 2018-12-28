#pragma once

#include "Engine/EngineCommon.h"

class InputState;
class TextInputContext;

class ENGINE_EXPORT Window
{
public:

  Window();
  Window(const Window & rhs);
  Window(Window && rhs);

  ~Window();

  Window & operator = (const Window & rhs);
  Window & operator = (Window && rhs);

  void Update() const;

  void MakeCurrent() const;
  void Swap() const;
  void Close() const;

  void GrabMouse();
  void ReleaseMouse();

  void SetMousePos(int x, int y) const;
  void SetVsyncEnabled(bool enabled) const;
  void SetFullscreen(bool fullscreen) const;
  bool IsFullScreen() const;

  Vector2 GetSize() const;
  Box GetGeometry() const;

  NullOptPtr<InputState> GetInputState() const;
  std::shared_ptr<TextInputContext> CreateTextInputContext(bool allow_first_input = false);

  uint32_t GetWindowId() const;
private:

  friend class WindowManager;
  friend class FakeWindow;
  friend class RenderState;

  void BindDefaultRenderTarget() const;

  void AddRef();
  void DecRef();

  Window(uint32_t window_id);

  uint32_t m_WindowId;
};

