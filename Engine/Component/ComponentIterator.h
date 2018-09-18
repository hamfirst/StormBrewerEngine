#pragma once

#include "Foundation/Optional/NullOpt.h"
#include "Foundation/SkipField/SkipFieldIterator.h"

class ComponentIteratorBase
{
protected:
  SkipFieldIterator m_Iterator;

  void * (*m_Deref)(const SkipFieldIterator & itr);
  void(*m_AdvanceIterator)(SkipFieldIterator & itr);
  bool(*m_CompareIterator)(const SkipFieldIterator & itr1, const SkipFieldIterator & itr2);
};

template <typename ComponentType>
class ComponentIterator : public ComponentIteratorBase
{
public:

  NullOptPtr<ComponentType> operator *()
  {
    return static_cast<ComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<const ComponentType> operator *() const
  {
    return static_cast<ComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<ComponentType> operator ->()
  {
    return static_cast<ComponentType>(m_Deref(m_Iterator));
  }

  NullOptPtr<const ComponentType> operator ->() const
  {
    return static_cast<ComponentType>(m_Deref(m_Iterator));
  }

  ComponentIterator<ComponentType> & operator++()
  {
    m_AdvanceIterator(m_Iterator);
  }

  bool operator == (const SkipFieldIterator & itr1, const SkipFieldIterator & itr2)
  {
    return m_CompareIterator(itr1, itr2);
  }

private:
  friend class ComponentType;

};

