
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.refl.meta.h"
#include "Engine/UI/UIManager.h"

#include "sb/vector.h"

UIClickable::UIClickable(NotNullPtr<UIManager> manager)
{

}

UIClickable::~UIClickable()
{
  Destroy();
}


ScriptClassRef<UIClickable> UIClickable::GetParent()
{
  return m_Parent;
}

void UIClickable::SetParent(ScriptClassRef<UIClickable> & self, const ScriptClassRef<UIClickable> & parent)
{
  if(parent == m_Parent)
  {
    return;
  }

  if(!m_Parent)
  {
    m_Manager->RemoveClickableFromRoot(this);
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

  if(parent)
  {
    if(m_Parent->m_Dead)
    {
      m_Manager->TrashClickable(this);
    }

    m_Parent->m_Children.push_back(self);
  }
  else
  {
    m_Manager->AddClickableToRoot(self);
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
    m_Manager->RemoveClickableFromRoot(this);
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
}
