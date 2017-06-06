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

  void MakeCurrent() const;
  void Swap() const;
  void Close() const;

  void SetMousePos(int x, int y) const;
  void SetVsyncEnabled(bool enabled) const;

  Vector2 GetSize() const;
  Box GetGeometry() const;

  NullOptPtr<InputState> GetInputState() const;
  std::shared_ptr<TextInputContext> CreateTextInputContext(bool allow_first_input = false);

private:

  friend class WindowManager;
  friend class FakeWindow;

  void AddRef();
  void DecRef();

  Window(uint32_t window_id);

  uint32_t m_WindowId;
};

