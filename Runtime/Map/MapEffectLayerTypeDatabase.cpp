

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Map/MapEffectLayerTypeDatabase.h"

PreMainCallList g_MapEffectLayerRegisterCallList;

#ifdef _MSC_VER
std::unordered_map<uint32_t, MapEffectLayerDataTypeInfo> StormDataTypeDatabase<MapEffectLayerInitData, MapEffectLayerDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<MapEffectLayerInitData, MapEffectLayerDataTypeInfo>;
