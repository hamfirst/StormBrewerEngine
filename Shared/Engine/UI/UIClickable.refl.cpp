
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.refl.meta.h"
#include "Engine/UI/UIManager.h"

#include "sb/vector.h"

UIClickable::UIClickable(NotNullPtr<UIManager> manager) :
  m_Manager(manager),
  m_State(static_cast<int>(UIClickableState::kActive))
{

}

UIClickable::~UIClickable()
{
  Destroy();
}

int UIClickable::GetState()
{
  return m_State;
}

ScriptClassRef<UIClickable> UIClickable::GetParent()
{
  return m_Parent;
}

void UIClickable::SetParent(ScriptClassRef<UIClickable> & parent)
{
  if(parent == m_Parent)
  {
    return;
  }

  if(!m_Parent)
  {
    m_Manager->RemoveClickableFromRoot(GetClassRef());
  }
  else
  {
    for(std::size_t index = 0, end = m_Parent->m_Children.size(); index < end; ++index)
    {
      auto & child = m_Parent->m_Children[index];
      if(child.Get() == this)
      {
        m_Parent->m_Children.erase(m_Parent->m_Children.begin() + index);
        break;
      }
    }
  }

  if(parent.IsValid())
  {
    if(parent->m_Dead)
    {
      m_Manager->TrashClickable(this);
    }

    parent->m_Children.push_back(GetClassRef());
    m_Parent = parent;
  }
  else
  {
    m_Manager->AddClickableToRoot(GetClassRef());
  }
}

int UIClickable::GetNumChildren()
{
  return static_cast<int>(m_Children.size());
}

ScriptClassRef<UIClickable> UIClickable::GetChild(int index)
{
  return m_Children[index];
}

void UIClickable::Destroy()
{
  if(!m_Parent)
  {
    if(m_Manager->m_Destroying == false)
    {
      m_Manager->RemoveClickableFromRoot(GetClassRef());
    }
  }
  else
  {
    for(std::size_t index = 0, end = m_Parent->m_Children.size(); index < end; ++index)
    {
      if(m_Parent->m_Dead == false)
      {
        auto &child = m_Parent->m_Children[index];
        if (child.Get() == this)
        {
          m_Parent->m_Children.erase(m_Parent->m_Children.begin() + index);
          break;
        }
      }
    }

    m_Parent.Clear();
  }
}

Optional<Box> UIClickable::CalculateActiveArea()
{
  if(Width <= 0 || Height <= 0)
  {
    return {};
  }

  Box b = Box::FromStartAndWidthHeight(X, Y, Width, Height);

  if(m_Parent.IsValid())
  {
    auto parent_box = m_Parent->CalculateActiveArea();
    if(parent_box.IsValid() == false)
    {
      return {};
    }

    b = b.Offset(parent_box->m_Start);
    return ClipBox(b, parent_box.Value());
  }

  return b;
}
