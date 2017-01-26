#pragma once

class InputState;
class TextInputContext;

class Window
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

  NullOptPtr<InputState> GetInputState() const;
  std::shared_ptr<TextInputContext> CreateTextInputContext();

private:

  friend class WindowManager;
  friend class FakeWindow;

  void AddRef();
  void DecRef();

  Window(uint32_t window_id);

  uint32_t m_WindowId;
};

