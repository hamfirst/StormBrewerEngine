
#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Config/ConfigRegistrationMacros.h"

#include "Game/ServerObjects/Player/Config/PlayerConfig.refl.h"
#include "Game/ServerObjects/Player/Config/PlayerConfig.refl.meta.h"

REGISTER_CONFIG_TYPE(PlayerConfig, "Player Config", "playerconfig", "Configs");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(PlayerConfig);
