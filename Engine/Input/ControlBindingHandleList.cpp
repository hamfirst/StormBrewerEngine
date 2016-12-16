
#include "Engine/EngineCommon.h"
#include "Engine/Input/ControlBindingHandleList.h"
#include "Engine/Input/InputState.h"


ControlBindingHandleList::ControlBindingHandleList(NotNullPtr<InputState> input_state)
  : m_InputState(input_state)
{

}

ControlBindingHandleList::~ControlBindingHandleList()
{
  ReleaseAll();
}

ControlBindingHandleList & ControlBindingHandleList::operator = (ControlBindingHandleList && rhs)
{
  ReleaseAll();

  m_BinaryControls = std::move(rhs.m_BinaryControls);
  m_PointerControls = std::move(rhs.m_PointerControls);
  return *this;
}

void ControlBindingHandleList::BindBinaryControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  auto handle = m_InputState->BindBinaryControl(control, priority, mode, callback);
  m_BinaryControls.push_back(handle);
}

void ControlBindingHandleList::BindPointerControl(const ControlId & control, int priority, ControlBindingMode mode, const Delegate<void, PointerState> & callback)
{
  auto handle = m_InputState->BindPointerControl(control, priority, mode, callback);
  m_PointerControls.push_back(handle);
}

void ControlBindingHandleList::ReleaseAll()
{
  for (auto & handle : m_BinaryControls)
  {
    m_InputState->UnbindBinaryControl(handle);
  }

  for (auto & handle : m_PointerControls)
  {
    m_InputState->UnbindPointerControl(handle);
  }
}
