#pragma once

enum class ControlBindingMode
{
  kPassThrough,
  kIgnoreLowerPriority,
};

class ENGINE_EXPORT ControlBinding
{
public:
  ControlBinding(int priority, ControlBindingMode mode) : 
    m_Priority(priority),
    m_Mode(mode)
  {

  }

  int GetPriority() const { return m_Priority; }
  ControlBindingMode GetMode() const { return m_Mode; }

private:
  int m_Priority;
  ControlBindingMode m_Mode;
};
