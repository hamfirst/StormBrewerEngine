
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
void RenderSprite(Any & engine_data, EntityRenderState & render_state, Vector2 & position);

SpriteResource::SpriteResource(Any && load_data, uint64_t path_hash) :
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

SpritePtr SpriteResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path, 
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<SpriteResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<SpriteResource *>(resource);
  return SpritePtr(DocumentResourceReference<SpriteResource>(p_this));
}

SpriteLoadLink SpriteResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path, 
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<SpriteResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<SpriteResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

int SpriteResource::GetAnimationIndex(uint32_t animation_name_hash)
{
  return vfind_index(m_AnimNameHashes, animation_name_hash);
}

int SpriteResource::GetAnimationLength(uint32_t animation_name_hash)
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

bool SpriteResource::FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state, bool loop, int frames)
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
  }
  else
  {
    auto frame_start = m_AnimStart[anim_state.m_AnimIndex];
    if (anim_state.m_AnimFrame < (int)m_AnimLengths[animation_index])
    {
      auto & frame = m_AnimationFrameSizes[frame_start + anim_state.m_AnimFrame];
      anim_state.m_FrameWidth = frame.x;
      anim_state.m_FrameHeight = frame.y;
    }
    else
    {
      anim_state.m_FrameWidth = 0;
      anim_state.m_FrameHeight = 0;
    }
  }

  return would_loop;
}

void SpriteResource::Render(EntityRenderState & render_state, Vector2 position)
{
  RenderSprite(m_EngineData, render_state, position);
}

Box SpriteResource::GetDefaultSingleBox()
{
  return Box::FromFrameCenterAndSize(Vector2{}, Vector2(4, 4));
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

  int total_frames = 0;
  for (auto elem : m_Data.m_Animations)
  {
    m_AnimNameHashes.push_back(crc32(elem.second.m_Name.data()));
    m_AnimStart.push_back(total_frames);

    int num_frames = 0;
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

      m_AnimationFrameSizes.push_back(frame_size);
      m_AnimationFrameDurations.push_back(frame.second.m_FrameDuration);
      num_frames++;
    }

    m_AnimLengths.push_back(num_frames);
    total_frames += num_frames;
  }

  UpdateSpriteEngineData(m_EngineData);
  m_Loaded = true;
}

void SpriteResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

