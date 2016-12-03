#pragma once

#include <algorithm>

#include "Foundation/Handle/HandleList.h"

#include "Engine/Input/ControlBinding.h"

template <typename ControlBindingType>
class ControlBindingList
{
public:
  ControlBindingList() :
    m_HandleList(0)
  {
    
  }

  Handle CreateControlBinding(int priority, ControlBindingMode mode, const typename ControlBindingType::CallbackType & callback)
  {
    return m_HandleList.AllocateElem(priority, mode, callback);
  }

  NotNullPtr<void> GetControlBinding(Handle handle)
  {
    return m_HandleList.Resolve(handle);
  }

  void RemoveControlBinding(Handle handle)
  {
    return m_HandleList.FreeElem(handle);
  }

  template <typename ControlValueType>
  void SetControlValue(ControlValueType value)
  {
    auto list_size = m_HandleList.GetNumHandles();
    if (list_size == 0)
    {
      return;
    }

    ControlBindingType ** list = (ControlBindingType **)alloca(sizeof(ControlBindingType *) * list_size);
    ControlBindingType ** list_ptr = list;

    auto list_grabber = [&](const Handle & handle, ControlBindingType & control)
    {
      *list_ptr = &control;
      list_ptr++;
    };

    m_HandleList.VisitEach(list_grabber);

    auto sort_func = [](const ControlBindingType * p1, const ControlBindingType * p2)
    {
      return p1->GetPriority() - p2->GetPriority();
    };

    std::sort(&list[0], &list[list_size], sort_func);

    bool valid = true;
    for (std::size_t index = 0; index < list_size; index++)
    {
      if (valid)
      {
        list[index]->UpdateState(value);

        if (list[index]->GetMode() == ControlBindingMode::kIgnoreLowerPriority)
        {
          valid = false;
        }
      }
      else
      {
        list[index]->UpdateState(ControlValueType{});
      }
    }
  }

private:
  HandleList<ControlBindingType> m_HandleList;
};


