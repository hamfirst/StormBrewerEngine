#pragma once


template <typename BaseClass, typename UpdateFunc>
class UpdateList
{
public:

  void Reset()
  {
    m_UpdateFirst.clear();
    m_UpdateMiddle.clear();
    m_UpdateLast.clear();
  }

  bool HasUpdates()
  {
    return m_UpdateFirst.size() > 0 || m_UpdateMiddle.size() > 0 || m_UpdateLast.size() > 0;
  }

  void AddFirst(NotNullPtr<BaseClass> comp, UpdateFunc func)
  {
    m_UpdateFirst.emplace_back(std::make_pair(comp, func));
  }

  void AddMiddle(NotNullPtr<BaseClass> comp, UpdateFunc func)
  {
    m_UpdateMiddle.emplace_back(std::make_pair(comp, func));
  }

  void AddLast(NotNullPtr<BaseClass> comp, UpdateFunc func)
  {
    m_UpdateLast.emplace_back(std::make_pair(comp, func));
  }


  template <typename ... Args>
  void CallFirst(Args && ... args)
  {
    for (auto & elem : m_UpdateFirst)
    {
      if (elem.first->IsDestroyed() == false)
      {
        (elem.first->*elem.second)(std::forward<Args>(args)...);
      }
    }
  }

  template <typename ... Args>
  void CallMiddle(Args && ... args)
  {
    for (auto & elem : m_UpdateMiddle)
    {
      if (elem.first->IsDestroyed() == false)
      {
        (elem.first->*elem.second)(std::forward<Args>(args)...);
      }
    }
  }

  template <typename ... Args>
  void CallLast(Args && ... args)
  {
    for (auto & elem : m_UpdateLast)
    {
      if (elem.first->IsDestroyed() == false)
      {
        (elem.first->*elem.second)(std::forward<Args>(args)...);
      }
    }
  }

private:
  std::vector<std::pair<NotNullPtr<BaseClass>, UpdateFunc>> m_UpdateFirst;
  std::vector<std::pair<NotNullPtr<BaseClass>, UpdateFunc>> m_UpdateMiddle;
  std::vector<std::pair<NotNullPtr<BaseClass>, UpdateFunc>> m_UpdateLast;
};


template <typename BaseClass, typename UpdateFunc>
class UpdateBucketList
{
public:
  void Reset()
  {
    for (auto & elem : m_Buckets)
    {
      elem.Reset();
    }
  }

  void AddFirst(NotNullPtr<BaseClass> comp, UpdateFunc func, int bucket)
  {
    while (bucket >= m_Buckets.size())
    {
      m_Buckets.emplace_back();
    }

    m_Buckets[bucket].AddFirst(comp, func);
  }

  void AddMiddle(NotNullPtr<BaseClass> comp, UpdateFunc func, int bucket)
  {
    while (bucket >= m_Buckets.size())
    {
      m_Buckets.emplace_back();
    }

    m_Buckets[bucket].AddMiddle(comp, func);
  }

  void AddLast(NotNullPtr<BaseClass> comp, UpdateFunc func, int bucket)
  {
    while (bucket >= m_Buckets.size())
    {
      m_Buckets.emplace_back();
    }

    m_Buckets[bucket].AddLast(comp, func);
  }

  int GetNumBuckets()
  {
    int num_buckets = 0;
    for (auto & elem : m_Buckets)
    {
      if (elem.HasUpdates())
      {
        num_buckets++;
      }
      else
      {
        break;
      }
    }

    return num_buckets;
  }

  template <typename ... Args>
  void CallFirst(int bucket, Args && ... args)
  {
    m_Buckets[bucket].CallFirst(std::forward<Args>(args)...);
  }

  template <typename ... Args>
  void CallMiddle(int bucket, Args && ... args)
  {
    m_Buckets[bucket].CallMiddle(std::forward<Args>(args)...);
  }

  template <typename ... Args>
  void CallLast(int bucket, Args && ... args)
  {
    m_Buckets[bucket].CallLast(std::forward<Args>(args)...);
  }

private:
  std::vector<UpdateList<BaseClass, UpdateFunc>> m_Buckets;
};

