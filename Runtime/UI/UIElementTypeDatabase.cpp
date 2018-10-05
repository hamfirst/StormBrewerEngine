

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/UI/UIElementTypeDatabase.h"

PreMainCallList g_UIElementRegisterCallList;
UIElementTypeDatabase g_UIElementTypeDatabase;

void UIElementTypeDatabase::RegisterTypes(PropertyFieldDatabase & property_db)
{
  for (auto & elem : m_TypeList)
  {
    elem.second.RegisterPropertyFields(property_db);
  }
}
