

#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/Anchor/AnchorTypeDatabase.h"

PreMainCallList g_AnchorRegisterCallList;

#ifdef _MSC_VER
std::unordered_map<uint32_t, AnchorDataTypeInfo> StormDataTypeDatabase<AnchorDataBase, AnchorDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<AnchorDataBase, AnchorDataTypeInfo>;
