

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Runtime/Path/PathTypeDatabase.h"

#ifdef _MSC_VER
std::unordered_map<uint32_t, PathDataTypeInfo> StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<PathDataBase, PathDataTypeInfo>;
