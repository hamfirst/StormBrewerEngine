#pragma once

#include "StormData/StormDataTypeDatabase.h"

#include "Runtime/Path/PathDef.refl.h"

class PathDataBase;

struct PropertyField;
class PropertyFieldDatabase;

struct PathDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

extern template
std::unordered_map<uint32_t, PathDataTypeInfo> StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>;

class PathTypeDatabase : public StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>
{
public:
  template <typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

