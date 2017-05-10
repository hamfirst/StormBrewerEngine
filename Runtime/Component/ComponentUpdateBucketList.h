#pragma once

#include "Runtime/Component/Component.h"

using ComponentUpdateFunc = void (Component::*)();

class RUNTIME_EXPORT ComponentUpdateList
{
public:

  void Reset();
  bool HasUpdates();

  void AddFirst(NotNullPtr<Component> comp, ComponentUpdateFunc func);
  void AddMiddle(NotNullPtr<Component> comp, ComponentUpdateFunc func);
  void AddLast(NotNullPtr<Component> comp, ComponentUpdateFunc func);

  void CallFirst();
  void CallMiddle();
  void CallLast();

private:
  std::vector<std::pair<NotNullPtr<Component>, ComponentUpdateFunc>> m_UpdateFirst;
  std::vector<std::pair<NotNullPtr<Component>, ComponentUpdateFunc>> m_UpdateMiddle;
  std::vector<std::pair<NotNullPtr<Component>, ComponentUpdateFunc>> m_UpdateLast;
};


class RUNTIME_EXPORT ComponentUpdateBucketList
{
public:
  void Reset();

  void AddFirst(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket);
  void AddMiddle(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket);
  void AddLast(NotNullPtr<Component> comp, ComponentUpdateFunc func, int bucket);

  int GetNumBuckets();
  void CallFirst(int bucket);
  void CallMiddle(int bucket);
  void CallLast(int bucket);

private:
  std::vector<ComponentUpdateList> m_Buckets;
};