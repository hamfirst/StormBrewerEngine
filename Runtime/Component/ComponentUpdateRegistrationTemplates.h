#pragma once

#include "Runtime/Component/ComponentUpdateBucketList.h"

template <typename T> 
struct ComponentHasUpdateFirst
{ 
public:
  template <typename C> 
  static char test(decltype(&C::UpdateFirst)); 
  
  template <typename C> static long test(...);  
  
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T> 
struct ComponentHasUpdateMiddle
{
public:
  template <typename C>
  static char test(decltype(&C::UpdateMiddle));

  template <typename C> static long test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T>
struct ComponentHasUpdateLast
{
public:
  template <typename C>
  static char test(decltype(&C::UpdateLast));

  template <typename C> static long test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};


template <typename T, bool HasUpdateFirst>
struct ComponentRegisterUpdateFirst
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {

  }
};

template <typename T>
struct ComponentRegisterUpdateFirst<T, true>
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {
    bucket_list.AddFirst(&t, (ComponentUpdateFunc)&T::UpdateFirst, t.GetBucket());
  }
};

template <typename T, bool HasUpdateFirst>
struct ComponentRegisterUpdateMiddle
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {

  }
};

template <typename T>
struct ComponentRegisterUpdateMiddle<T, true>
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {
    bucket_list.AddMiddle(&t, (ComponentUpdateFunc)&T::UpdateMiddle, t.GetBucket());
  }
};

template <typename T, bool HasUpdateFirst>
struct ComponentRegisterUpdateLast
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {

  }
};

template <typename T>
struct ComponentRegisterUpdateLast<T, true>
{
  static void Process(T & t, ComponentUpdateBucketList & bucket_list)
  {
    bucket_list.AddLast(&t, (ComponentUpdateFunc)&T::UpdateLast, t.GetBucket());
  }
};

template <typename T>
static void ComponentRegisterUpdate(T & t, ComponentUpdateBucketList & bucket_list)
{
  ComponentRegisterUpdateFirst<T, ComponentHasUpdateFirst<T>::value>::Process(t, bucket_list);
  ComponentRegisterUpdateMiddle<T, ComponentHasUpdateMiddle<T>::value>::Process(t, bucket_list);
  ComponentRegisterUpdateLast<T, ComponentHasUpdateLast<T>::value>::Process(t, bucket_list);
}
