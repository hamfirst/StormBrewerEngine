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

  bool operator == (const ScriptClassRef<T> & rhs) const
  {
    return m_RefData == rhs.m_RefData;
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

  const T * operator -> () const
  {
    return Get();
  }

  bool IsValid() const
  {
    return Get() != nullptr;
  }

  explicit operator bool() const
  {
    return m_RefData != nullptr;
  }

  bool operator !() const
  {
    return m_RefData == nullptr;
  }

private:
  template <typename ClassT>
  friend class ScriptClass;

  template <typename ClassT>
  friend class ScriptClassInstanceBase;

  friend class ScriptFuncs;

  explicit ScriptClassRef(NullOptPtr<ScriptClassRefData> ref_data)
  {
    m_RefData = ref_data;
    m_RefData->IncRef();
  }

private:
  ScriptClassRefData * m_RefData = nullptr;
};

template <typename T>
class ScriptClassInstanceBase
{
public:

  ScriptClassRef<T> GetClassRef()
  {
    return ScriptClassRef<T>(m_RefData);
  }

protected:

  template <typename ClassT>
  friend class ScriptClass;

  NotNullPtr<ScriptClassRefData> m_RefData;
};

