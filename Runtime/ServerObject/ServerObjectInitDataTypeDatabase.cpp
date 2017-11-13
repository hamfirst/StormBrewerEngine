
#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/ServerObject/ServerObjectInitDataTypeDatabase.h"

#ifdef _MSC_VER
std::unordered_map<uint32_t, ServerObjectInitDataTypeInfo> StormDataTypeDatabase<ServerObjectInitData, ServerObjectInitDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<ServerObjectInitData, ServerObjectInitDataTypeInfo>;

PreMainCallList g_ServerObjectInitRegisterCallList;
