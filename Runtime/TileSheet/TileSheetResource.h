#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/TileSheet/TileSheetDef.refl.h"

class TileSheetResource;
class AnimationState;


using TileSheet = DocumentResourcePtr<TileSheetDef, TileSheetResource>;
using TileSheetLoadLink = DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource>;

class TileSheetResource : public DocumentResourceBase
{
public:
  TileSheetResource(Any && load_data, uint64_t path_hash);

  NotNullPtr<TileSheetDef> GetData();
  DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource> AddLoadCallback(Delegate<void, NotNullPtr<TileSheetResource>> && callback);

  static TileSheet Load(czstr file_path);
  static TileSheetLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback);

  int GetAnimationIndex(uint32_t animation_name_hash);
  void FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state);

  int GetLowerEdgeOffset(uint64_t tile_id);

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class SpriteEngineData;

  TileSheetDef m_Data;
  DelegateList<void, NotNullPtr<TileSheetResource>> m_LoadCallbacks;

  Any m_EngineData;

  std::vector<uint32_t> m_AnimNameHashes;
  std::vector<uint32_t> m_AnimLengths;

  std::unordered_map<uint64_t, int> m_LowerEdgeLookup;
  int m_StandardLowerEdge;
};
