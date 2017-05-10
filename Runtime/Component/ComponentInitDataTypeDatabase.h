#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Foundation/PropertyMeta/PropertyFieldDatabase.h"
#include "Runtime/Component/ComponentInitData.refl.h"

struct ComponentInitDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

class ComponentInitDataTypeDatabase : public StormDataTypeDatabase<ComponentInitData, ComponentInitDataTypeInfo>
{
public:
  template <typename Component, typename InitData, typename ... BaseTypes>
  static void RegisterType();
};


