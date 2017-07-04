#pragma once

#include "StormRefl/StormReflMetaFuncs.h"
#include "Server/ServerObject/ServerObjectHandle.h"


template <typename T, bool IsReflectable>
struct ServerObjectResetHandleClass
{
  static void Process(T & t, const ServerObjectManager & object_manager)
  {

  }
};

template <typename T>
struct ServerObjectResetHandleClass<T, true>
{
  static void Process(T & t, const ServerObjectManager & object_manager)
  {
    auto visitor = [&](auto f)
    {
      using MemberType = typename decltype(f)::MemberType;
      ServerObjectResetHandle<MemberType>::Process(f.Get(), object_manager);
    };

    StormReflVisitEach(t, visitor);
  }
};

template <typename T>
struct ServerObjectResetHandle
{
  static void Process(T & t, const ServerObjectManager & object_manager)
  {
    ServerObjectResetHandleClass<T, StormReflCheckReflectable<T>::value>::Process(t, object_manager);
  }
};

template <>
struct ServerObjectResetHandle<ServerObjectHandle>
{
  static void Process(ServerObjectHandle & handle, const ServerObjectManager & object_manager)
  {
    handle.ResetGen(object_manager);
  }
};

