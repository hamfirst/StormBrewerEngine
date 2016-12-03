
#include "Engine/EngineCommon.h"
#include "Engine/Input/ControlBindingSet.h"
#include "Engine/Input/InputState.h"

ControlBindingSet::ControlBindingSet(InputState & input_state, int control_enum_count) :
  m_InputState(input_state),
  m_BinaryControls(std::make_unique<BinaryControlHandle[]>(control_enum_count)),
  m_NumBinaryControls(control_enum_count)
{

}

ControlBindingSet::~ControlBindingSet()
{
  for (int index = 0; index < m_NumBinaryControls; index++)
  {
    m_InputState.UnbindBinaryControl(m_BinaryControls[index]);
  }
}

void ControlBindingSet::BindControl(const ControlId & control_id, int control_enum, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  m_BinaryControls[control_enum] = m_InputState.BindBinaryControl(control_id, priority, mode, callback);
}

const BinaryControlHandle & ControlBindingSet::GetControl(int control_enum)
{
  return m_BinaryControls[control_enum];
}
