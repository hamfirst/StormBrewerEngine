#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameData.refl.h"

struct SpriteBaseDef;

class FrameDataExtract
{
public:
  FrameDataExtract(FrameData & frame_data);

  Optional<Box> GetSingleBox(uint32_t data_type_name_hash);
  Optional<gsl::span<const Box>> GetMultiBox(uint32_t data_type_name_hash);

private:
  FrameData & m_FrameData;
};

