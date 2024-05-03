
#include "Game/GameCommon.h"
#include "Foundation/SkipField/SkipField.h"

#include "StormRefl/StormReflMetaFuncs.h"
#include "StormRefl/StormReflJsonStd.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Config/ConfigRegistrationMacros.h"

#include "Game/GameController/Config/GameConfig.refl.h"
#include "Game/GameController/Config/GameConfig.refl.meta.h"

REGISTER_CONFIG_TYPE(GameConfig, "Game Config", "gameconfig", "Configs");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(GameConfig);
