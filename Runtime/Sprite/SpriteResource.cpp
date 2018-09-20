
#include "Runtime/RuntimeCommon.h"
#include "Runtime/Sprite/SpriteResource.h"
#include "Runtime/Sprite/SpriteDef.refl.meta.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormRefl/StormReflJson.h"
#include "StormData/StormDataJson.h"

#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"

#include <sb/vector.h>

Any CreateSpriteEngineData(SpriteBaseDef & sprite);
void UpdateSpriteEngineData(Any & engine_data);
void RenderSprite(Any & engine_data, RenderState & render_state, EntityRenderState & entity_render_state, const Vector2 & position);

SpriteResource::SpriteResource(Any && load_data, uint32_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<SpriteDef> SpriteResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource> SpriteResource::AddLoadCallback(Delegate<void, NotNullPtr<SpriteResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource>(
    DocumentResourceReference<SpriteResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void SpriteResource::AddLoadCallback(Delegate<void, NotNullPtr<SpriteResource>> && callback, DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource> & load_link)
{
  load_link = DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource>(
    DocumentResourceReference<SpriteResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

SpritePtr SpriteResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<SpriteResource *>(resource);
    return SpritePtr(DocumentResourceReference<SpriteResource>(p_this));
  }

  return {};
}

SpritePtr SpriteResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path, 
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<SpriteResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<SpriteResource *>(resource);
  return SpritePtr(DocumentResourceReference<SpriteResource>(p_this));
}

SpriteLoadLink SpriteResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path, 
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<SpriteResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<SpriteResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void SpriteResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback, SpriteLoadLink & load_link)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<SpriteResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<SpriteResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), load_link);
}

int SpriteResource::GetAnimationIndex(uint32_t animation_name_hash) const
{
  return vfind_index(m_AnimNameHashes, animation_name_hash);
}

int SpriteResource::GetAnimationLength(uint32_t animation_name_hash) const
{
  int animation_index = GetAnimationIndex(animation_name_hash);
  if (animation_index != -1)
  {
    int anim_start = m_AnimStart[animation_index];
    int anim_length = m_AnimLengths[animation_index];

    int frame_duration = 0;
    for (int index = anim_start; anim_length > 0; ++index, --anim_length)
    {
      frame_duration += m_AnimationFrameDurations[index];
    }

    return frame_duration;
  }

  return 0;
}

int SpriteResource::GetAnimationLengthByIndex(int animation_index) const
{
  int anim_start = m_AnimStart[animation_index];
  int anim_length = m_AnimLengths[animation_index];

  int frame_duration = 0;
  for (int index = anim_start; anim_length > 0; ++index, --anim_length)
  {
    frame_duration += m_AnimationFrameDurations[index];
  }

  return frame_duration;
}

void SpriteResource::GetDefaultFrame(AnimationState & anim_state) const
{
  if (m_AnimationFrameSizes.size() == 0)
  {
    anim_state.m_AnimIndex = -1;
    anim_state.m_AnimFrame = 0;
    anim_state.m_AnimDelay = 0;
    anim_state.m_FrameWidth = 0;
    anim_state.m_FrameHeight = 0;
    anim_state.m_LowerEdge = 0;
    return;
  }

  anim_state.m_AnimIndex = 0;
  anim_state.m_AnimFrame = 0;
  anim_state.m_AnimDelay = 0;
  anim_state.m_FrameWidth = m_AnimationFrameSizes[0].x;
  anim_state.m_FrameHeight = m_AnimationFrameSizes[0].y;
  anim_state.m_LowerEdge = m_AnimationLowerEdges[0];
}

bool SpriteResource::FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state, bool loop, int frames) const
{
  bool would_loop = false;
  int animation_index = GetAnimationIndex(animation_name_hash);
  if (animation_index != anim_state.m_AnimIndex)
  {
    anim_state.m_AnimIndex = animation_index;
    anim_state.m_AnimFrame = 0;
    anim_state.m_AnimDelay = 0;
  }
  else if (animation_index != -1)
  {
    if (anim_state.m_AnimFrame < (int)m_AnimLengths[animation_index])
    {
      auto frame_start = m_AnimStart[anim_state.m_AnimIndex];
      while (frames)
      {
        if (frames > 0)
        {
          if (anim_state.m_AnimDelay + 1 >= (int)m_AnimationFrameDurations[frame_start + anim_state.m_AnimFrame])
          {
            if (anim_state.m_AnimFrame + 1 >= (int)m_AnimLengths[animation_index])
            {
              would_loop = true;
              if (loop)
              {
                anim_state.m_AnimFrame = 0;
                anim_state.m_AnimDelay = 0;
              }
            }
            else
            {
              anim_state.m_AnimDelay = 0;
              anim_state.m_AnimFrame++;
            }
          }
          else
          {
            anim_state.m_AnimDelay++;
          }

          frames--;
        }
        else
        {
          if (anim_state.m_AnimDelay - 1 < 0)
          {
            if (anim_state.m_AnimFrame == 0)
            {
              would_loop = true;
              if (loop)
              {
                anim_state.m_AnimFrame = (int)m_AnimLengths[animation_index] - 1;
                anim_state.m_AnimDelay = (int)m_AnimationFrameDurations[frame_start + anim_state.m_AnimFrame] - 1;
              }
            }
            else
            {
              anim_state.m_AnimFrame--;
              anim_state.m_AnimDelay = (int)m_AnimationFrameDurations[frame_start + anim_state.m_AnimFrame] - 1;
            }
          }
          else
          {
            anim_state.m_AnimDelay--;
          }

          frames++;
        }
      }
    }
  }

  if (anim_state.m_AnimIndex == -1)
  {
    anim_state.m_FrameWidth = 0;
    anim_state.m_FrameHeight = 0;
    anim_state.m_LowerEdge = 0;
  }
  else
  {
    auto frame_start = m_AnimStart[anim_state.m_AnimIndex];
    if (anim_state.m_AnimFrame < (int)m_AnimLengths[animation_index])
    {
      auto & frame = m_AnimationFrameSizes[frame_start + anim_state.m_AnimFrame];
      auto & lower_edge = m_AnimationLowerEdges[frame_start + anim_state.m_AnimFrame];
      anim_state.m_FrameWidth = frame.x;
      anim_state.m_FrameHeight = frame.y;
      anim_state.m_LowerEdge = lower_edge;
    }
    else
    {
      anim_state.m_FrameWidth = 0;
      anim_state.m_FrameHeight = 0;
      anim_state.m_LowerEdge = 0;
    }
  }

  return would_loop;
}

bool SpriteResource::SyncToFrame(uint32_t animation_name_hash, AnimationState & anim_state, int frames) const
{
  int animation_index = GetAnimationIndex(animation_name_hash);

  anim_state.m_AnimIndex = animation_index;
  if (animation_index == -1 || m_AnimTotalLengths[animation_index] == 0)
  {
    anim_state.m_FrameWidth = 0;
    anim_state.m_FrameHeight = 0;
    anim_state.m_LowerEdge = 0;
    return false;
  }

  frames %= m_AnimTotalLengths[animation_index];

  int anim_frame_index = 0;
  auto frame_start = m_AnimStart[anim_state.m_AnimIndex];

  while (true)
  {
    auto duration = m_AnimationFrameDurations[frame_start + anim_frame_index];
    if (frames < (int)duration)
    {
      break;
    }

    frames -= duration;
    anim_frame_index++;
  }

  anim_state.m_AnimFrame = anim_frame_index;

  auto & frame = m_AnimationFrameSizes[frame_start + anim_state.m_AnimFrame];
  auto & lower_edge = m_AnimationLowerEdges[frame_start + anim_state.m_AnimFrame];

  anim_state.m_FrameWidth = frame.x;
  anim_state.m_FrameHeight = frame.y;
  anim_state.m_LowerEdge = lower_edge;
  return true;
}

void SpriteResource::SyncFrameData(int animation_index, int animation_frame, int animation_delay, AnimationState & anim_state) const
{
  if (animation_index < 0)
  {
    anim_state = {};
    return;
  }

  auto frame_start = m_AnimStart[animation_index];

  anim_state.m_AnimIndex = animation_index;
  anim_state.m_AnimFrame = animation_frame;
  anim_state.m_AnimDelay = animation_delay;

  auto & frame = m_AnimationFrameSizes[frame_start + anim_state.m_AnimFrame];
  auto & lower_edge = m_AnimationLowerEdges[frame_start + anim_state.m_AnimFrame];

  anim_state.m_FrameWidth = frame.x;
  anim_state.m_FrameHeight = frame.y;
  anim_state.m_LowerEdge = lower_edge;
}

void SpriteResource::Render(RenderState & render_state, EntityRenderState & entity_render_state, Vector2 position)
{
  RenderSprite(m_EngineData, render_state, entity_render_state, position);
}

Box SpriteResource::GetDefaultSingleBox()
{
  return Box::FromFrameCenterAndSize(Vector2{}, Vector2(4, 4));
}

int SpriteResource::GetAnimationFrameDuration(int animation_index, int animation_frame)
{
  if (animation_index >= 0 && animation_index < m_AnimStart.size())
  {
    int anim_start = m_AnimStart[animation_index];
    int anim_length = m_AnimLengths[animation_index];

    if (animation_frame <= 0 || animation_frame >= anim_length)
    {
      return 0;
    }

    return m_AnimationFrameDurations[anim_start + animation_frame];
  }

  return 0;
}

uint64_t SpriteResource::GetAnimationFrameId(int animation_index, int animation_frame)
{
  if (animation_index >= 0 && animation_index < m_AnimStart.size())
  {
    int anim_start = m_AnimStart[animation_index];
    int anim_length = m_AnimLengths[animation_index];

    if (animation_frame < 0 || animation_frame >= anim_length)
    {
      return 0;
    }

    return m_AnimationFrameIds[anim_start + animation_frame];
  }

  return 0;
}

Box SpriteResource::GetSingleBox(uint32_t data_type_name_hash)
{
  FrameDataExtract extractor(m_Data.m_InstanceData);
  auto result = extractor.GetSingleBox(data_type_name_hash);

  if (result)
  {
    return result.Value();
  }

  return GetDefaultSingleBox();
}

Box SpriteResource::GetSingleBox(uint32_t data_type_name_hash, uint64_t frame_id)
{
  auto frame_data = m_Data.m_FrameData.TryGet(frame_id);
  if (frame_data)
  {
    FrameDataExtract extractor(*frame_data);
    auto result = extractor.GetSingleBox(data_type_name_hash);

    if (result)
    {
      return result.Value();
    }
  }

  return GetSingleBox(data_type_name_hash);
}

Vector2 SpriteResource::GetAnchor(uint32_t data_type_name_hash)
{
  for (auto elem : m_Data.m_Anchors)
  {
    if (crc32(elem.second.m_AnchorName.data()) == data_type_name_hash)
    {
      return elem.second.m_DefaultPosition.Value();
    }
  }

  return {};
}

Vector2 SpriteResource::GetAnchor(uint32_t data_type_name_hash, uint64_t frame_id)
{
  auto frame_data = m_Data.m_FrameData.TryGet(frame_id);
  if (frame_data)
  {
    for (auto elem : frame_data->m_Anchors)
    {
      if (crc32(elem.second.m_AnchorName.data()) == data_type_name_hash)
      {
        return elem.second.m_Position.Value();
      }
    }
  }

  return GetAnchor(data_type_name_hash);
}

gsl::span<const Box> SpriteResource::GetMultiBox(uint32_t data_type_name_hash)
{
  FrameDataExtract extractor(m_Data.m_InstanceData);
  auto result = extractor.GetMultiBox(data_type_name_hash);

  if (result)
  {
    return result.Value();
  }

  return {};
}

gsl::span<const Box> SpriteResource::GetMultiBox(uint32_t data_type_name_hash, uint64_t frame_id)
{
  auto frame_data = m_Data.m_FrameData.TryGet(frame_id);
  if (frame_data)
  {
    FrameDataExtract extractor(*frame_data);
    auto result = extractor.GetMultiBox(data_type_name_hash);

    if (result)
    {
      return result.Value();
    }
  }

  return GetMultiBox(data_type_name_hash);
}

FrameDataSingleLineInfo SpriteResource::GetDefaultSingleLine()
{
  return FrameDataSingleLineInfo{ {0, -2}, {0, 2} };
}

void SpriteResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  if (!m_EngineData)
  {
    m_EngineData = CreateSpriteEngineData(m_Data);
  }

  std::vector<std::pair<uint32_t, Vector2>> textures;
  for (auto tex : m_Data.m_Textures)
  {
    textures.emplace_back(std::make_pair(crc32(tex.second.m_Filename.data()), Vector2(tex.second.m_FrameWidth, tex.second.m_FrameHeight)));
  }

  m_AnimNameHashes.clear();
  m_AnimLengths.clear();
  m_AnimTotalLengths.clear();
  m_AnimEventInfo.clear();
  m_AnimEvents.clear();
  m_AnimEventBoxes.clear();

  auto lower_edge = 0;
  for (auto elem : m_Data.m_InstanceData.m_LowerEdgeData)
  {
    if (elem.second.m_FrameDataName == "LowerEdge")
    {
      lower_edge = elem.second.m_Data->m_OffsetPixels;
      break;
    }
  }

  int total_frames = 0;
  for (auto elem : m_Data.m_Animations)
  {
    m_AnimNameHashes.push_back(crc32(elem.second.m_Name.data()));
    m_AnimStart.push_back(total_frames);

    int num_frames = 0;
    int total_length = 0;
    int start_events = (int)m_AnimEvents.size();

    for (auto frame : elem.second.m_Frames)
    {
      uint32_t tex_hash = (uint32_t)((uint64_t)frame.second.m_FrameId >> 32);

      Vector2 frame_size = {};
      for (auto & tex : textures)
      {
        if (tex.first == tex_hash)
        {
          frame_size = tex.second;
          break;
        }
      }

      auto frame_lower_edge = lower_edge;

      auto frame_data = m_Data.m_FrameData.TryGet(frame.second.m_FrameId);
      if (frame_data)
      {
        for (auto elem : frame_data->m_LowerEdgeData)
        {
          if (elem.second.m_FrameDataName == "LowerEdge")
          {
            frame_lower_edge = elem.second.m_Data->m_OffsetPixels;
            break;
          }
        }
      }

      m_AnimationFrameSizes.push_back(frame_size);
      m_AnimationFrameDurations.push_back(frame.second.m_FrameDuration);
      m_AnimationFrameIds.push_back(frame.second.m_FrameId);
      m_AnimationLowerEdges.push_back(frame_lower_edge);
      num_frames++;
      total_length += frame.second.m_FrameDuration;
    }

    for (auto ev : elem.second.m_Events)
    {
      AnimEventInfo event_info;
      event_info.m_EventData = ev.second.m_EventData;
      event_info.m_FrameIndex = ev.second.m_Frame;
      event_info.m_FrameDelay = ev.second.m_FrameDelay;
      event_info.m_EventBoxStart = (int)m_AnimEventBoxes.size();

      for (auto elem : ev.second.m_EventArea.Value())
      {
        m_AnimEventBoxes.push_back(elem);
      }

      event_info.m_EventBoxEnd = (int)m_AnimEventBoxes.size();
      m_AnimEvents.emplace_back(std::move(event_info));
    }

    m_AnimLengths.push_back(num_frames);
    m_AnimTotalLengths.push_back(total_length);
    m_AnimEventInfo.push_back(std::make_pair(start_events, (int)m_AnimEvents.size()));
    total_frames += num_frames;
  }

  UpdateSpriteEngineData(m_EngineData);
  m_Loaded = true;
}

void SpriteResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

