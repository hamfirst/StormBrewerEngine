
#include "Runtime/RuntimeCommon.h"
#include "Runtime/TileSheet/TileSheetResource.h"
#include "Runtime/TileSheet/TileSheetDef.refl.meta.h"
#include "Runtime/Animation/AnimationState.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

Any CreateSpriteEngineData(SpriteBaseDef & sprite);
void UpdateSpriteEngineData(Any & engine_data);

TileSheetResource::TileSheetResource(Any && load_data, uint64_t path_hash) :
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

TileSheet TileSheetResource::Load(czstr file_path)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<TileSheetResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<TileSheetResource *>(resource);
  return TileSheet(DocumentResourceReference<TileSheetResource>(p_this));
}

TileSheetLoadLink TileSheetResource::LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback)
{
  auto resource = LoadDocumentResource(file_path,
    [](Any && load_data, uint64_t path_hash) -> std::unique_ptr<DocumentResourceBase> { return std::make_unique<TileSheetResource>(std::move(load_data), path_hash); });
  auto p_this = static_cast<TileSheetResource *>(resource);

  return p_this->AddLoadCallback(std::move(callback));
}

int TileSheetResource::GetAnimationIndex(uint32_t animation_name_hash)
{
  return vfind_index(m_AnimNameHashes, animation_name_hash);
}

void TileSheetResource::FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state)
{
  int animation_index = GetAnimationIndex(animation_name_hash);
  if (animation_index != anim_state.m_AnimIndex)
  {
    anim_state.m_AnimIndex = animation_index;
    anim_state.m_AnimFrame = 0;
  }
  else if (animation_index != -1)
  {
    anim_state.m_AnimFrame++;
    if (anim_state.m_AnimFrame >= (int)m_AnimLengths[animation_index])
    {
      anim_state.m_AnimFrame = 0;
    }
  }
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
  for (auto elem : m_Data.m_Animations)
  {
    m_AnimNameHashes.push_back(crc32(elem.second.m_Name.data()));

    int num_frames = 0;
    for (auto frame : elem.second.m_Frames)
    {
      num_frames++;
    }

    m_AnimLengths.push_back(num_frames);
  }

  UpdateSpriteEngineData(m_EngineData);
  m_Loaded = true;
}

void TileSheetResource::CallAssetLoadCallbacks()
{
  m_LoadCallbacks.Call(this);
}

