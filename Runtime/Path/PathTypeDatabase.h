#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Runtime/Path/PathDef.refl.h"

class PathDataBase;

struct PropertyField;
class PropertyFieldDatabase;

struct PathDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

class PathTypeDatabase : public StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>
{
public:
  template <typename Component, typename InitData, typename ... BaseTypes>
  static void RegisterType();
};

