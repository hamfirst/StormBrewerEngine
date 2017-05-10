#pragma once

#include "Engine/Input/BinaryControlBinding.h"
#include "Engine/Input/PointerControlBinding.h"

class ENGINE_EXPORT ControlBindingHandleList
{
public:
  ControlBindingHandleList(NotNullPtr<InputState> input_state);

  ControlBindingHandleList(const ControlBindingHandleList & rhs) = delete;
  ControlBindingHandleList(ControlBindingHandleList && rhs) = default;

  ~ControlBindingHandleList();

  ControlBindingHandleList & operator = (const ControlBindingHandleList & rhs) = delete;
  ControlBindingHandleList & operator = (ControlBindingHandleList && rhs);

  void BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback);
  void BindPointerControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback);

  void ReleaseAll();

private:
  NotNullPtr<InputState> m_InputState;

  std::vector<BinaryControlHandle> m_BinaryControls;
  std::vector<PointerControlHandle> m_PointerControls;
};

