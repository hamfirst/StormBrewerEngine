
#include "Game/GameCommon.h"

#include "StormData/StormData.h"
#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataParent.h"

#include "Runtime/Volume/VolumeTypeDatabase.h"
#include "Runtime/Volume/VolumeTypeRegister.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Game/Data/KillVolume.refl.h"
#include "Game/Data/KillVolume.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(KillVolume);
REGISTER_TYPE(KillVolume, VolumeDataBase);
