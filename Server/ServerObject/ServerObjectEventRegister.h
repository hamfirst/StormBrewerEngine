#pragma once

#include "StormRefl/StormReflMetaCall.h"
#include "Server/ServerObject/ServerObject.h"

template <typename ServerObjectType>
void RegisterServerObjectEvents()
{
  auto & event_dispatch = ServerObjectType::EventDispatch;
  StormReflFuncVisitor<ServerObjectType>::VisitFuncs([&](auto f)
  {
    auto func_ptr = f.GetFunctionPtr();
    event_dispatch.RegisterEventHandler(func_ptr);
  });
}




