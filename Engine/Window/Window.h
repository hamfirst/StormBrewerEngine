#pragma once

class InputState;

class Window
{
public:

  Window();
  Window(const Window & rhs);
  Window(Window && rhs);

  ~Window();

  Window & operator = (const Window & rhs);
  Window & operator = (Window && rhs);

  void Swap() const;

  NullOptPtr<InputState> GetInputState() const;

private:

  friend class WindowManager;

  void AddRef();
  void DecRef();

  Window(uint32_t window_id);

  uint32_t m_WindowId;
};

