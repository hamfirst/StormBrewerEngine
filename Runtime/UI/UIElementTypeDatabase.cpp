

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/UI/UIElementTypeDatabase.h"

PreMainCallList g_UIElementRegisterCallList;
UIElementTypeDatabase g_UIElementTypeDatabase;

#ifdef _MSC_VER
std::unordered_map<uint32_t, UIElementDataTypeInfo> StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<UIElementInitDataBase, UIElementDataTypeInfo>;

void UIElementTypeDatabase::RegisterTypes(PropertyFieldDatabase & property_db)
{
  for (auto & elem : m_TypeList)
  {
    elem.second.RegisterPropertyFields(property_db);
  }
}
