#pragma once

#include "StormData/StormDataTypeDatabase.h"

#include "Runtime/UI/UITypes.refl.h"

struct UIElementInitDataBase;
struct UIRuntimeFieldDesc;

struct PropertyField;
class PropertyFieldDatabase;

struct UIElementDataTypeInfo : public StormDataTypeInfo
{
  PropertyField * (*RegisterPropertyFields)(PropertyFieldDatabase & property_db);
  std::vector<UIRuntimeFieldDesc> m_RuntimeDesc;
};

class UIElementTypeDatabase :
        public StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>,
        public StormDataTypeDatabaseSingleton<UIElementTypeDatabase>
{
public:
  template <typename RuntimeClass, typename InitDataType, typename RuntimeDataType>
  void RegisterType();

  void RegisterTypes(PropertyFieldDatabase & property_db);
};

extern UIElementTypeDatabase g_UIElementTypeDatabase;
