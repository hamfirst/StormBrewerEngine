#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/TileSheet/TileSheetDef.refl.h"

class TileSheetResource;
class AnimationState;


using TileSheetPtr = DocumentResourcePtr<TileSheetDef, TileSheetResource>;
using TileSheetLoadLink = DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource>;

class TileSheetResource : public DocumentResourceBase
{
public:
  TileSheetResource(Any && load_data, uint64_t path_hash);

  NotNullPtr<TileSheetDef> GetData();
  DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource> AddLoadCallback(Delegate<void, NotNullPtr<TileSheetResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<TileSheetResource>> && callback, DocumentResourceLoadCallbackLink<TileSheetDef, TileSheetResource> & load_link);

  static TileSheetPtr Load(czstr file_path);
  static TileSheetLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<TileSheetResource>> && callback, TileSheetLoadLink & load_link);

  bool InitAnimation(uint32_t animation_name_hash, uint32_t frame_offset, AnimationState & anim_state);
  void UpdateFrameInfo(AnimationState & anim_state);
  void FrameAdvance(AnimationState & anim_state);

  Vector2 GetAnimationMaxSize(uint32_t animation_name_hash);
  Vector2 GetAnimationMaxSize(AnimationState & state);
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
  std::vector<Vector2> m_AnimMaxSizes;
  std::vector<std::vector<Vector2>> m_AnimFrameSizes;
  std::vector<std::vector<uint32_t>> m_AnimFrameLengths;
  std::vector<std::vector<int>> m_AnimLowerEdges;
  std::vector<uint32_t> m_AnimTotalLengths;

  std::unordered_map<uint64_t, int> m_LowerEdgeLookup;
  int m_StandardLowerEdge;
};
