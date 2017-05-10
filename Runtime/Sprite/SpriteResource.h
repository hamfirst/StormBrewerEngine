#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/Sprite/SpriteDef.refl.h"

class SpriteResource;
class AnimationState;

struct EntityRenderState;

using Sprite = DocumentResourcePtr<SpriteDef, SpriteResource>;
using SpriteLoadLink = DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource>;

class SpriteResource : public DocumentResourceBase
{
public:
  SpriteResource(Any && load_data, uint64_t path_hash);

  NotNullPtr<SpriteDef> GetData();
  DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource> AddLoadCallback(Delegate<void, NotNullPtr<SpriteResource>> && callback);

  static Sprite Load(czstr file_path);
  static SpriteLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback);

  int GetAnimationIndex(uint32_t animation_name_hash);
  int GetAnimationLength(uint32_t animation_name_hash);
  bool FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state, bool loop = true);

  void Render(EntityRenderState & render_state, Vector2 position);

  static Box GetDefaultSingleBox();
  static FrameDataSingleLineInfo GetDefaultSingleLine();

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class SpriteEngineData;

  SpriteDef m_Data;
  DelegateList<void, NotNullPtr<SpriteResource>> m_LoadCallbacks;

  Any m_EngineData;

  std::vector<uint32_t> m_AnimNameHashes;
  std::vector<uint32_t> m_AnimStart;
  std::vector<uint32_t> m_AnimLengths;
  std::vector<Vector2> m_AnimationFrameSizes;
  std::vector<uint32_t> m_AnimationFrameDurations;
};
