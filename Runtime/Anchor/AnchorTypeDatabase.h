#pragma once

#include "StormData/StormDataTypeDatabase.h"

#include "Runtime/Anchor/AnchorDef.refl.h"

class AnchorDataBase;

struct PropertyField;
class PropertyFieldDatabase;

struct AnchorDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

extern template
std::unordered_map<uint32_t, AnchorDataTypeInfo> StormDataTypeDatabase<AnchorDataBase, AnchorDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<AnchorDataBase, AnchorDataTypeInfo>;

class AnchorTypeDatabase : public StormDataTypeDatabase<AnchorDataBase, AnchorDataTypeInfo>
{
public:
  template <typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

