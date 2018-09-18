
#include "Runtime/RuntimeCommon.h"

#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataTypeDatabaseRegister.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/SpriteBase/SpriteAnimationEventTypeDatabase.h"

#ifdef _MSC_VER
std::unordered_map<uint32_t, SpriteAnimationEventDataTypeInfo> StormDataTypeDatabase<SpriteAnimationEventDataBase, SpriteAnimationEventDataTypeInfo>::m_TypeList;
#endif

template class StormDataTypeDatabase<SpriteAnimationEventDataBase, SpriteAnimationEventDataTypeInfo>;

PreMainCallList g_SpriteAnimationEventRegisterCallList;
