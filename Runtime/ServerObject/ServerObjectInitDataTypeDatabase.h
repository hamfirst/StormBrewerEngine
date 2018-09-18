#pragma once

#include "StormData/StormDataTypeDatabase.h"

#include "Runtime/ServerObject/ServerObjectInitData.refl.h"

class ServerObjectInitData;

struct PropertyField;
class PropertyFieldDatabase;

struct ServerObjectInitDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

extern template
std::unordered_map<uint32_t, ServerObjectInitDataTypeInfo> StormDataTypeDatabase<ServerObjectInitData, ServerObjectInitDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<ServerObjectInitData, ServerObjectInitDataTypeInfo>;

class ServerObjectInitTypeDatabase : public StormDataTypeDatabase<ServerObjectInitData, ServerObjectInitDataTypeInfo>
{
public:
  template <typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

