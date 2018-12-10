
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

void UIClickable::SetParent(ScriptClassRef<UIClickable> & self, const ScriptClassRef<UIClickable> & parent)
{
  if(parent == Parent)
  {
    return;
  }

  if(!Parent)
  {
    m_Manager->RemoveClickableFromRoot(this);
  }
  else
  {
    for(std::size_t index = 0, end = Parent->m_Children.size(); index < end; ++index)
    {
      auto & child = Parent->m_Children[index];
      if(child.Get() == this)
      {
        Parent->m_Children.erase(Parent->m_Children.begin() + index);
        break;
      }
    }
  }

  if(parent)
  {
    Parent->m_Children.push_back(self);
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
  if(!Parent)
  {
    m_Manager->RemoveClickableFromRoot(this);
  }
  else
  {
    for(std::size_t index = 0, end = Parent->m_Children.size(); index < end; ++index)
    {
      auto & child = Parent->m_Children[index];
      if(child.Get() == this)
      {
        Parent->m_Children.erase(Parent->m_Children.begin() + index);
        break;
      }
    }
  }
}
