#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>

#include "Runtime/Anchor/AnchorDef.refl.h"
#include "Runtime/Anchor/AnchorTypeDatabase.h"

struct MapEditorAnchorInitData
{
  STORM_DATA_DEFAULT_CONSTRUCTION(MapEditorAnchorInitData);
  RPolymorphic<AnchorDataBase> m_InitData;

  RString STORM_REFL_ATTR_VAL(file, sprite) m_Sprite;
};
