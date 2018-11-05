#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameData.refl.h"

struct SpriteBaseDef;

class FrameDataExtract
{
public:
  FrameDataExtract(const FrameData & frame_data);

  Optional<Box> GetSingleBoxDefault(uint32_t data_type_name_hash);
  Optional<gsl::span<const Box>> GetMultiBox(uint32_t data_type_name_hash);

private:
  const FrameData & m_FrameData;
};

