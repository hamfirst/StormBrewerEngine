
#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameDataExtract.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

FrameDataExtract::FrameDataExtract(const FrameData & frame_data) :
  m_FrameData(frame_data)
{

}

Optional<Box> FrameDataExtract::GetSingleBoxDefault(uint32_t data_type_name_hash)
{
  for (auto elem : m_FrameData.m_SingleBoxData)
  {
    if (crc32(elem.second.m_FrameDataName.data()) == data_type_name_hash)
    {
      return elem.second.m_Data.Value();
    }
  }

  return {};
}

Optional<gsl::span<const Box>> FrameDataExtract::GetMultiBox(uint32_t data_type_name_hash)
{
  for (auto elem : m_FrameData.m_MultiBoxData)
  {
    if (crc32(elem.second.m_FrameDataName.data()) == data_type_name_hash)
    {
      return gsl::make_span(elem.second.m_Data.Value());
    }
  }

  return {};
}
