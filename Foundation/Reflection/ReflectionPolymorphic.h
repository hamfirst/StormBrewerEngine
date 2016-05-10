#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\TypeDatabaseThin.h"

template <class T, typename std::enable_if<
  std::is_class<T>::value && std::has_virtual_destructor<T>::value && T::is_reflectable
>::type * = nullptr>
class RPolymorphic
{
  REFLECTION_PARENT_INFO;
public:

  RPolymorphic()
  {
    m_T = std::make_unique<T>();
    m_TypeNameHash = m_T->GetTypeNameHash();
  }

  T * GetValue()
  {
    return m_T;
  }

  uint32_t GetTypeNameHash()
  {
    return m_TypeNameHash;
  }

  template <class NewType, typename std::enable_if<std::is_base_of<T, NewType>::value>::type = 0>
  void SetType()
  {
    NewType * new_val = new NewType();
    m_T = new_val;
    m_TypeNameHash = new_val->GetTypeNameHash();
    Modified();
  }

  void SetType(uint32_t type_name_hash)
  {
    Optional<void *> new_val = CreateTypeInstance(type_name_hash);
    if (new_val)
    {
      m_T = static_cast<T *>(new_val);
      m_TypeNameHash = type_name_hash;
      Modified();
    }
  }

private:

  void Modified()
  {
#ifdef REFLECTION_PARENT
    ReflectionNotifySet(m_ReflectionInfo, m_T.get(), m_TypeNameHash);
#endif
  }

  std::unique_ptr<T> m_T;
  uint32_t m_TypeNameHash;
};
