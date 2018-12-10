#pragma once

#include "Foundation/Optional/NullOpt.h"

class ScriptClassBase;

struct ScriptClassRefData
{
  void * m_Instance;
  int m_RefCount;
  ScriptClassBase * m_Class;

  void IncRef();
  void DecRef();
  void DeleteInst();
};

template <typename T>
class ScriptClassRef
{
public:
  ScriptClassRef() = default;
  ScriptClassRef(const ScriptClassRef<T> & rhs)
  {
    m_RefData = rhs.m_RefData;
    if(m_RefData)
    {
      m_RefData->IncRef();
    }
  }

  ScriptClassRef(ScriptClassRef<T> && rhs) noexcept
  {
    m_RefData = rhs.m_RefData;
    rhs.m_RefData = nullptr;
  }

  ScriptClassRef & operator = (const ScriptClassRef<T> & rhs)
  {
    Clear();
    m_RefData = rhs.m_RefData;
    if(m_RefData)
    {
      m_RefData->IncRef();
    }

    return *this;
  }

  ScriptClassRef & operator = (ScriptClassRef<T> && rhs) noexcept
  {
    Clear();
    m_RefData = rhs.m_RefData;
    rhs.m_RefData = nullptr;

    return *this;
  }

  void Clear()
  {
    if(m_RefData)
    {
      m_RefData->DecRef();
      m_RefData = nullptr;
    }
  }

  NullOptPtr<T> Get()
  {
    return m_RefData ? static_cast<NullOptPtr<T>>(m_RefData->m_Instance) : nullptr;
  }

  NullOptPtr<const T> Get() const
  {
    return m_RefData ? static_cast<NullOptPtr<T>>(m_RefData->m_Instance) : nullptr;
  }

  operator NullOptPtr<T>()
  {
    return Get();
  }

  operator NullOptPtr<const T>()
  {
    return Get();
  }

  T & operator * ()
  {
    return *Get();
  }

  T & operator * () const
  {
    return *Get();
  }

  T * operator -> ()
  {
    return Get();
  }

  T * operator -> () const
  {
    return Get();
  }

  operator bool() const
  {
    return m_RefData != nullptr;
  }

private:
  template <typename ClassT>
  friend class ScriptClass;

  friend class ScriptFuncs;

  explicit ScriptClassRef(NullOptPtr<ScriptClassRefData> ref_data)
  {
    m_RefData = ref_data;
  }

private:
  ScriptClassRefData * m_RefData = nullptr;
};
