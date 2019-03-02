

#include <StormRefl/StormReflJsonStd.h>
#include <StormData/StormDataParent.h>
#include <StormData/StormDataChangePacket.h>

#include "GameData.refl.meta.h"

#ifdef ENABLE_REWARDS
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserXPGain);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserRewards);
#endif
