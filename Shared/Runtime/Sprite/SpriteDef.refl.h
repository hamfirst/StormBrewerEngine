#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>


struct RUNTIME_EXPORT SpriteDef : public SpriteBaseDef
{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION(SpriteDef);
};

