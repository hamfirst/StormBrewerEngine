#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/Component/ComponentInitData.refl.h"
#include "Runtime/Component/ComponentInitDataTypeDatabase.h"

struct RUNTIME_EXPORT EntityDef
{
  STORM_DATA_DEFAULT_CONSTRUCTION(EntityDef);

  RString STORM_REFL_ATTR_VAL(file, sprite) m_Sprite;

  RMergeList<RPolymorphic<ComponentInitData, ComponentInitDataTypeDatabase, ComponentInitDataTypeInfo>> m_Components;
};

