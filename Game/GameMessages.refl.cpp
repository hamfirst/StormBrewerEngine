#include "Game/GameCommon.h"

#include "StormNet/NetReflectionTypeDatabaseRegister.h"

#include "GameMessages.refl.meta.h"

NET_BASE_TYPE(FromServerMessage);
NET_BASE_TYPE(ToServerMessage);
NET_REGISTER_ALL_TYPES_FOR_FILE(GameMessages);
