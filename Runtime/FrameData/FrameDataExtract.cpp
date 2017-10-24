
#include "Runtime/RuntimeCommon.h"
#include "Runtime/FrameData/FrameDataExtract.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"
#include "Runtime/Sprite/SpriteResource.h"

FrameDataExtract::FrameDataExtract(SpriteBaseDef & frame_data) :
  m_FrameData(frame_data)
{

}

Box FrameDataExtract::GetSingleBox(uint32_t data_type_name_hash)
{
  for (auto elem : m_FrameData.m_InstanceData.m_SingleBoxData)
  {
    if (crc32(elem.second.m_FrameDataName.data()) == data_type_name_hash)
    {
      return elem.second.m_Data.Value();
    }
  }

  return SpriteResource::GetDefaultSingleBox();
}
