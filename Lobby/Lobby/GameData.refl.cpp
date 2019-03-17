

#include <StormRefl/StormReflJsonStd.h>
#include <StormData/StormDataParent.h>
#include <StormData/StormDataChangePacket.h>

#include "GameData.refl.meta.h"

<<<<<<< HEAD
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserXPGain);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserRewards);
=======
#ifdef ENABLE_REWARDS
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserXPGain);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UserRewards);
#endif
>>>>>>> a49d5fa0cf25199154acded458b9a5829dad762c
