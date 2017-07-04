#pragma once

#include "Foundation/Update/UpdateBucketList.h"

template <typename T>
struct HasUpdateFirst
{
public:
  template <typename C>
  static char test(decltype(&C::UpdateFirst));

  template <typename C> static long test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T>
struct HasUpdateMiddle
{
public:
  template <typename C>
  static char test(decltype(&C::UpdateMiddle));

  template <typename C> static long test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};

template <typename T>
struct HasUpdateLast
{
public:
  template <typename C>
  static char test(decltype(&C::UpdateLast));

  template <typename C> static long test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};


template <typename T, typename BaseClass, typename UpdateFunc, bool HasUpdateFirst>
struct RegisterUpdateFirst
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {

  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {

  }
};

template <typename T, typename BaseClass, typename UpdateFunc>
struct RegisterUpdateFirst<T, BaseClass, UpdateFunc, true>
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {
    update_list.AddFirst(&t, (UpdateFunc)&T::UpdateFirst);
  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {
    bucket_list.AddFirst(&t, (UpdateFunc)&T::UpdateFirst, bucket);
  }
};

template <typename T, typename BaseClass, typename UpdateFunc, bool HasUpdateFirst>
struct RegisterUpdateMiddle
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {

  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {

  }
};

template <typename T, typename BaseClass, typename UpdateFunc>
struct RegisterUpdateMiddle<T, BaseClass, UpdateFunc, true>
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {
    update_list.AddMiddle(&t, (UpdateFunc)&T::UpdateFirst);
  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {
    bucket_list.AddMiddle(&t, (UpdateFunc)&T::UpdateFirst, bucket);
  }
};

template <typename T, typename BaseClass, typename UpdateFunc, bool HasUpdateFirst>
struct RegisterUpdateLast
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {

  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {

  }
};

template <typename T, typename BaseClass, typename UpdateFunc>
struct RegisterUpdateLast<T, BaseClass, UpdateFunc, true>
{
  static void Process(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
  {
    update_list.AddLast(&t, (UpdateFunc)&T::UpdateFirst);
  }

  static void Process(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
  {
    bucket_list.AddLast(&t, (UpdateFunc)&T::UpdateFirst, bucket);
  }
};

template <typename T, typename BaseClass, typename UpdateFunc>
static void RegisterUpdate(T & t, UpdateList<BaseClass, UpdateFunc> & update_list)
{
  RegisterUpdateFirst<T, BaseClass, UpdateFunc, HasUpdateFirst<T>::value>::Process(t, update_list);
  RegisterUpdateMiddle<T, BaseClass, UpdateFunc, HasUpdateMiddle<T>::value>::Process(t, update_list);
  RegisterUpdateLast<T, BaseClass, UpdateFunc, HasUpdateLast<T>::value>::Process(t, update_list);
}


template <typename T, typename BaseClass, typename UpdateFunc>
static void RegisterUpdate(T & t, UpdateBucketList<BaseClass, UpdateFunc> & bucket_list, int bucket)
{
  RegisterUpdateFirst<T, BaseClass, UpdateFunc, HasUpdateFirst<T>::value>::Process(t, bucket_list, bucket);
  RegisterUpdateMiddle<T, BaseClass, UpdateFunc, HasUpdateMiddle<T>::value>::Process(t, bucket_list, bucket);
  RegisterUpdateLast<T, BaseClass, UpdateFunc, HasUpdateLast<T>::value>::Process(t, bucket_list, bucket);
}
