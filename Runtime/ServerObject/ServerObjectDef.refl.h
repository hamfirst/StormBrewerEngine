#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/ServerObject/ServerObjectInitData.refl.h"
#include "Runtime/ServerObject/ServerObjectInitDataTypeDatabase.h"

using ServerObjectInitDataPolyType = RPolymorphic<ServerObjectInitData, ServerObjectInitTypeDatabase, ServerObjectInitDataTypeInfo>;

struct RUNTIME_EXPORT ServerObjectDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(ServerObjectDef);
  RBool m_IsStatic;
  RPolymorphic<ServerObjectInitData, ServerObjectInitTypeDatabase, ServerObjectInitDataTypeInfo> m_InitData;
};

