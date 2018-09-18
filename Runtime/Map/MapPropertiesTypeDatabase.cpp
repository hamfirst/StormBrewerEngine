

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Map/MapPropertiesTypeDatabase.h"

PreMainCallList g_MapPropertiesRegisterCallList;

#ifdef _MSC_VER
std::unordered_map<uint32_t, MapPropertiesDataTypeInfo> StormDataTypeDatabase<MapPropertiesInitData, MapPropertiesDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<MapPropertiesInitData, MapPropertiesDataTypeInfo>;
