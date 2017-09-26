
#include "Foundation/Common.h"
#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "StormData/StormData.h"
#include "StormData/StormDataJson.h"

#include "Runtime/Map/MapEffectLayerTypeDatabase.h"
#include "Runtime/Map/MapEffectLayerTypeRegister.h"

#include "GameClient/EffectLayers/CollisionDrawer.refl.h"
#include "GameClient/EffectLayers/CollisionDrawer.refl.meta.h"

REGISTER_EFFECT_LAYER_DATA(CollisionDrawer, CollisionDrawerInitData);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(CollisionDrawerInitData);
