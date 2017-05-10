
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Component/ComponentUpdateBucketList.h"


void ComponentUpdateList::Reset()
{
  m_UpdateFirst.clear();
  m_UpdateMiddle.clear();
  m_UpdateLast.clear();
}

bool ComponentUpdateList::HasUpdates()
{
  return m_UpdateFirst.size() > 0 || m_UpdateMiddle.size() > 0 || m_UpdateLast.size() > 0;
}

void ComponentUpdateList::AddFirst(NotNullPtr<Component> comp, ComponentUpdateFunc func)
{
  m_UpdateFirst.emplace_back(std::make_pair(comp, func));
}

void ComponentUpdateList::AddMiddle(NotNullPtr<Component> comp, ComponentUpdateFunc func)
{
  m_UpdateMiddle.emplace_back(std::make_pair(comp, func));
}

void ComponentUpdateList::AddLast(NotNullPtr<Component> comp, ComponentUpdateFunc func)
{
  m_UpdateLast.emplace_back(std::make_pair(comp, func));
}

void ComponentUpdateList::CallFirst()
{
  for (auto & elem : m_UpdateFirst)
  {
    if (elem.first->IsDestroyed() == false)
    {
      (elem.first->*elem.second)();
    }
  }
}

void ComponentUpdateList::CallMiddle()
{
  for (auto & elem : m_UpdateMiddle)
  {
    if (elem.first->IsDestroyed() == false)
    {
      (elem.first->*elem.second)();
    }
  }
}

void ComponentUpdateList::CallLast()
{
  for (auto & elem : m_UpdateLast)
  {
    if (elem.first->IsDestroyed() == false)
    {
      (elem.first->*elem.second)();
    }
  }
}

void ComponentUpdateBucketList::Reset()
{
  for (auto & elem : m_Buckets)
  {
    elem.Reset();
  }
}

void ComponentUpdateBucketList::AddFirst(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket)
{
  while (bucket >= m_Buckets.size())
  {
    m_Buckets.emplace_back();
  }

  m_Buckets[bucket].AddFirst(comp, func);
}

void ComponentUpdateBucketList::AddMiddle(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket)
{
  while (bucket >= m_Buckets.size())
  {
    m_Buckets.emplace_back();
  }

  m_Buckets[bucket].AddMiddle(comp, func);
}

void ComponentUpdateBucketList::AddLast(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket)
{
  while (bucket >= m_Buckets.size())
  {
    m_Buckets.emplace_back();
  }

  m_Buckets[bucket].AddLast(comp, func);
}

int ComponentUpdateBucketList::GetNumBuckets()
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

void ComponentUpdateBucketList::CallFirst(int bucket)
{
  m_Buckets[bucket].CallFirst();
}

void ComponentUpdateBucketList::CallMiddle(int bucket)
{
  m_Buckets[bucket].CallMiddle();
}

void ComponentUpdateBucketList::CallLast(int bucket)
{
  m_Buckets[bucket].CallLast();
}
