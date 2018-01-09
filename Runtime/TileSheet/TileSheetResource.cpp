
#include "Runtime/RuntimeCommon.h"
#include "Runtime/TileSheet/TileSheetResource.h"
#include "Runtime/TileSheet/TileSheetDef.refl.meta.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

Any CreateSpriteEngineData(SpriteBaseDef & sprite);
void UpdateSpriteEngineData(Any & engine_data);

TileSheetResource::TileSheetResource(Any && load_data, uint32_t path_hash) :
  DocumentResourceBase(std::move(load_data), path_hash)
{

}

NotNullPtr<TileSheetDef> TileSheetResource::GetData()
{
  return &m_Data;
}

DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource> TileSheetResource::AddLoadCallback(Delegate<void, NotNullPtr<TileSheetResource>> && callback)
{
  if (m_Loaded)
  {
    callback(this);
  }

  return DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource>(
    DocumentResourceReference<TileSheetResource>(this), m_LoadCallbacks.AddDelegate(std::move(callback)));
}

void TileSheetResource::AddLoadCallback(Delegate<void, NotNullPtr<TileSheetResource>> && callback, 
  DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource> & load_link)
{
  load_link = DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource>(
    DocumentResourceReference<TileSheetResource>(this), m_LoadCallbacks.AddDelegate(callback));

  if (m_Loaded)
  {
    callback(this);
  }
}

TileSheetPtr TileSheetResource::Find(uint32_t file_path_hash)
{
  auto resource = FindDocumentResource(file_path_hash);
  if (resource)
  {
    auto p_this = static_cast<TileSheetResource *>(resource);
    return TileSheetPtr(DocumentResourceReference<TileSheetResource>(p_this));
  }

  return {};
}

TileSheetPtr TileSheetResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<TileSheetResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<TileSheetResource *>(resource);
  return TileSheetPtr(DocumentResourceReference<TileSheetResource>(p_this));
}

TileSheetLoadLink TileSheetResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<TileSheetResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<TileSheetResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

void TileSheetResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback, TileSheetLoadLink & load_link)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint32_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<TileSheetResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<TileSheetResource *>(resource);

  p_this->AddLoadCallback(std::move(callback), load_link);
}

bool TileSheetResource::InitAnimation(uint32_t animation_name_hash, uint32_t frame_offset, AnimationState & anim_state)
{
  auto anim_index = vfind_index(m_AnimNameHashes, animation_name_hash);
  if (anim_index == -1)
  {
    return false;
  }

  if (m_AnimTotalLengths[anim_index] == 0)
  {
    return false;
  }

  frame_offset %= m_AnimTotalLengths[anim_index];
 
  anim_state.m_AnimIndex = anim_index;
  anim_state.m_AnimFrame = 0;
  anim_state.m_AnimDelay = 0;
  
  for (auto & frame_duration : m_AnimFrameLengths[anim_index])
  {
    if (frame_duration > frame_offset)
    {
      anim_state.m_AnimDelay = frame_offset;
    }
    else
    {
      anim_state.m_AnimFrame++;
      frame_offset -= frame_duration;
    }
  }

  UpdateFrameInfo(anim_state);
  return true;
}

void TileSheetResource::UpdateFrameInfo(AnimationState & anim_state)
{
  auto & frame_size = m_AnimFrameSizes[anim_state.m_AnimIndex][anim_state.m_AnimFrame];
  anim_state.m_FrameWidth = frame_size.x;
  anim_state.m_FrameHeight = frame_size.y;
  anim_state.m_LowerEdge = m_AnimLowerEdges[anim_state.m_AnimIndex][anim_state.m_AnimFrame];
}

void TileSheetResource::FrameAdvance(AnimationState & anim_state)
{
  anim_state.m_AnimDelay++;
  if (anim_state.m_AnimDelay >= (int)m_AnimFrameLengths[anim_state.m_AnimIndex][anim_state.m_AnimFrame])
  {
    anim_state.m_AnimDelay = 0;
    anim_state.m_AnimFrame++;

    if (anim_state.m_AnimFrame >= (int)m_AnimLengths[anim_state.m_AnimIndex])
    {
      anim_state.m_AnimFrame = 0;
    }
  }

  UpdateFrameInfo(anim_state);
}

int TileSheetResource::GetLowerEdgeOffset(uint64_t tile_id)
{
  auto itr = m_LowerEdgeLookup.find(tile_id);
  if (itr == m_LowerEdgeLookup.end())
  {
    return m_StandardLowerEdge;
  }

  return itr->second;
}

Vector2 TileSheetResource::GetAnimationMaxSize(uint32_t animation_name_hash)
{
  for(std::size_t index = 0, end = m_AnimNameHashes.size(); index < end; ++index)
  {
    if (m_AnimNameHashes[index] == animation_name_hash)
    {
      return m_AnimMaxSizes[index];
    }
  }

  return Vector2(1, 1);
}

Vector2 TileSheetResource::GetAnimationMaxSize(AnimationState & state)
{
  if (state.m_AnimIndex < 0)
  {
    return Vector2(1, 1);
  }

  return m_AnimMaxSizes[state.m_AnimIndex];
}

void TileSheetResource::OnDataLoadComplete(const std::string & resource_data)
{
  StormReflParseJson(m_Data, resource_data.data());

  if (!m_EngineData)
  {
    m_EngineData = CreateSpriteEngineData(m_Data);
  }

  m_AnimNameHashes.clear();
  m_AnimLengths.clear();

  std::vector<std::pair<uint32_t, Vector2>> textures;
  for (auto tex : m_Data.m_Textures)
  {
    textures.emplace_back(std::make_pair(crc32(tex.second.m_Filename.data()), Vector2(tex.second.m_FrameWidth, tex.second.m_FrameHeight)));
  }

  m_StandardLowerEdge = 0;
  for (auto elem : m_Data.m_InstanceData.m_LowerEdgeData)
  {
    if (elem.second.m_FrameDataName == "LowerEdge")
    {
      m_StandardLowerEdge = elem.second.m_Data->m_OffsetPixels;
      break;
    }
  }

  for (auto elem : m_Data.m_Animations)
  {
    m_AnimNameHashes.push_back(crc32(elem.second.m_Name.data()));
    m_AnimFrameLengths.emplace_back();
    m_AnimFrameSizes.emplace_back();
    m_AnimLowerEdges.emplace_back();

    int num_frames = 0;
    int total_frames = 0;

    Vector2 max_size = Vector2(1, 1);

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

      max_size.x = std::max(max_size.x, frame_size.x);
      max_size.y = std::max(max_size.y, frame_size.y);

      auto frame_lower_edge = m_StandardLowerEdge;

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

      m_AnimFrameSizes.back().push_back(frame_size);
      m_AnimLowerEdges.back().push_back(frame_lower_edge);
      m_AnimFrameLengths.back().emplace_back(frame.second.m_FrameDuration);

      total_frames += frame.second.m_FrameDuration;
      num_frames++;
    }

    m_AnimLengths.push_back(num_frames);
    m_AnimTotalLengths.push_back(total_frames);
    m_AnimMaxSizes.push_back(max_size);
  }

  UpdateSpriteEngineData(m_EngineData);

  for (auto frame : m_Data.m_FrameData)
  {
    for (auto elem : frame.second.m_LowerEdgeData)
    {
      if (elem.second.m_FrameDataName == "LowerEdge")
      {
        m_LowerEdgeLookup.emplace(std::make_pair(frame.first, elem.second.m_Data->m_OffsetPixels));
        break;
      }
    }
  }

  m_Loaded = true;
}

void TileSheetResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

