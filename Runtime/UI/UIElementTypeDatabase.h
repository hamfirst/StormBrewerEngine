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

extern template
std::unordered_map<uint32_t, UIElementDataTypeInfo> StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>::m_TypeList;
extern template class StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>;

class UIElementTypeDatabase : public StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>
{
public:
  template <typename RuntimeClass, typename InitDataType, typename RuntimeDataType>
  static void RegisterType();

  void RegisterTypes(PropertyFieldDatabase & property_db);
};

extern UIElementTypeDatabase g_UIElementTypeDatabase;
