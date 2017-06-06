#pragma once


template <typename ReturnType, typename ... Args>
class DelegateList;

template <typename ReturnType, typename ... Args>
class DelegateLink
{
public:
  DelegateLink() :
    m_DelegateIndex(-1),
    m_List(nullptr)
  {

  }

  DelegateLink(const DelegateLink & rhs) = delete;
  DelegateLink(DelegateLink && rhs) noexcept
  {
    m_DelegateIndex = rhs.m_DelegateIndex;
    m_List = rhs.m_List;

    rhs.m_DelegateIndex = -1;
    rhs.m_List = nullptr;
  }

  ~DelegateLink()
  {
    Unlink();
  }

  void Clear()
  {
    Unlink();
  }

  DelegateLink & operator = (const DelegateLink & rhs) = delete;
  DelegateLink & operator = (DelegateLink && rhs) noexcept
  {
    Unlink();

    m_DelegateIndex = rhs.m_DelegateIndex;
    m_List = rhs.m_List;

    rhs.m_DelegateIndex = -1;
    rhs.m_List = nullptr;
    return *this;
  }

private:
  DelegateLink(int delegate_index, DelegateList<ReturnType, Args...> * list) :
    m_DelegateIndex(delegate_index),
    m_List(list)
  {
    
  }

  void Unlink()
  {
    if (m_List != nullptr)
    {
      m_List->RemoveDelegateInternal(m_DelegateIndex);
      m_List = nullptr;
      m_DelegateIndex = -1;
    }
  }

  template <typename, typename ...>
  friend class DelegateList;

  int m_DelegateIndex = -1;
  DelegateList<ReturnType, Args...> * m_List = nullptr;
};
