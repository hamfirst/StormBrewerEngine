

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Path/PathTypeDatabase.h"

PreMainCallList g_PathRegisterCallList;

#ifdef _MSC_VER
std::unordered_map<uint32_t, PathDataTypeInfo> StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>;
