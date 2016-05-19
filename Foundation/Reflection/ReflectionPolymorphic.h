#pragma once

#include "Foundation\Reflection\Reflection.h"
#include "Foundation\Reflection\TypeDatabaseThin.h"

template <class T, class DefaultType = T, typename std::enable_if<
  std::is_class<T>::value && std::has_virtual_destructor<T>::value && T::is_reflectable
>::type * = nullptr>
class RPolymorphic
{
public:
  REFLECTION_CHANGE_NOTIFIER_INFO;

#ifdef REFLECTION_CHANGE_NOTIFIER
  ReflectionParentInfo m_TypeReflectionInfo;
#endif

  RPolymorphic()
  {
    DefaultType * new_val = new DefaultType();
    m_T = new_val;
    m_TypeNameHash = new_val->GetTypeNameHash();

#ifdef REFLECTION_CHANGE_NOTIFIER
    m_TypeReflectionInfo.m_ParentType = 0xFFFFFFFF;
    m_TypeReflectionInfo.m_ParentIndex = 1;
    m_TypeReflectionInfo.m_ParentInfo = &m_ReflectionInfo;
#endif
  }

  T & GetValue()
  {
    return m_T;
  }

  const T & GetValue() const
  {
    return m_T;
  }

  T * operator -> ()
  {
    return m_T;
  }

  const T * operator -> () const
  {
    return m_T;
  }

  bool operator == (const RPolymorphic<T> & rhs) const
  {
    if (m_TypeNameHash != rhs.m_TypeNameHash)
    {
      return false;
    }

    return CompareTypeInstance(m_T.get(), rhs.m_T.get(), m_TypeNameHash);
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
#ifdef REFLECTION_CHANGE_NOTIFIER
    if (m_ReflectionInfo.m_ParentInfo)
    {
      ReflectionParentInfo new_info;
      new_info.m_ParentInfo = &m_ReflectionInfo;
      new_info.m_ParentIndex = 0;
      new_info.m_ParentType = 0xFFFFFFFF;

      SetParentInfo(GetValue(), GetTypeNameHash(), new_info);
    }

    ReflectionNotifySet(m_TypeReflectionInfo, m_TypeNameHash);
    ReflectionNotifySet(m_T->m_ReflectionInfo, m_T.get(), m_TypeNameHash);
#endif
  }

  std::unique_ptr<T> m_T;
  uint32_t m_TypeNameHash;
};
