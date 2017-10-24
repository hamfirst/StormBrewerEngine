#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameData.refl.h"

struct SpriteBaseDef;

class FrameDataExtract
{
public:
  FrameDataExtract(SpriteBaseDef & frame_data);

  Box GetSingleBox(uint32_t data_type_name_hash);

private:
  SpriteBaseDef & m_FrameData;
};

