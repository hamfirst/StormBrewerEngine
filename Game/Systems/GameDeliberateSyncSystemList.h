#pragma once

#include "Game/GameCommon.h"

// Put deliberate sync systems in this list
//#define DELIBERATE_SYNC_SYSTEM_LIST \

#ifdef DELIBERATE_SYNC_SYSTEM_LIST

template <typename ... InitData>
using GameDeliberateSyncSystemListDataTypes = std::tuple<InitData...>;

using GameDeliberateSyncSystemListType = GameDeliberateSyncSystemListDataTypes<
  DELIBERATE_SYNC_SYSTEM_LIST
>;

#endif
