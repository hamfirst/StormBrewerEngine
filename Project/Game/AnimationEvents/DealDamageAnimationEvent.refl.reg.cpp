

#include "Game/GameCommon.h"

#include "StormData/StormData.h"
#include "StormData/StormDataTypeDatabase.h"
#include "StormData/StormDataParent.h"

#include "Runtime/SpriteBase/SpriteAnimationEventTypeDatabase.h"
#include "Runtime/SpriteBase/SpriteAnimationEventRegister.h"

#include "Foundation/PropertyMeta/PropertyFieldMetaFuncs.h"

#include "Game/AnimationEvents/DealDamageAnimationEvent.refl.h"
#include "Game/AnimationEvents/DealDamageAnimationEvent.refl.meta.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(DealDamageAnimationEvent);
REGISTER_TYPE(DealDamageAnimationEvent, SpriteAnimationEventDataBase);

uint32_t DealDamageAnimationEvent::TypeNameHash = StormReflTypeInfo<DealDamageAnimationEvent>::GetNameHash();
