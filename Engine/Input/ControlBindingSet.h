#pragma once

#include <memory>

#include "BinaryControlBinding.h"

class InputState;

class ControlBindingSet
{
public:
  ControlBindingSet(InputState & input_state, int control_enum_count);
  ~ControlBindingSet();

  void BindControl(const ControlId & control_id, int control_enum, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  const BinaryControlHandle & GetControl(int control_enum);

  void Cleanup();

private:
  InputState & m_InputState;
  std::unique_ptr<BinaryControlHandle[]> m_BinaryControls;
  int m_NumBinaryControls;
};
