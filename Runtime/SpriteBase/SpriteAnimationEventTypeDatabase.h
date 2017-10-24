#pragma once

#include <StormData/StormDataTypeDatabase.h>

#include "Runtime/SpriteBase/SpriteAnimationEventDef.refl.h"

class SpriteAnimationEventDataBase;

struct PropertyField;
class PropertyFieldDatabase;

struct SpriteAnimationEventDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
};

extern template
std::unordered_map<uint32_t, SpriteAnimationEventDataTypeInfo> StormDataTypeDatabase<SpriteAnimationEventDataBase, SpriteAnimationEventDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<SpriteAnimationEventDataBase, SpriteAnimationEventDataTypeInfo>;

class SpriteAnimationEventTypeDatabase : public StormDataTypeDatabase<SpriteAnimationEventDataBase, SpriteAnimationEventDataTypeInfo>
{
public:
  template <typename DataType, typename ... BaseTypes>
  static void RegisterType();
};

