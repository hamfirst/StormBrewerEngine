
#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Runtime/Volume/VolumeTypeDatabase.h"

#ifdef _MSC_VER
std::unordered_map<uint32_t, VolumeDataTypeInfo> StormDataTypeDatabase<VolumeDataBase, VolumeDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<VolumeDataBase, VolumeDataTypeInfo>;
