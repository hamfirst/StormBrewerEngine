#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/FrameData/FrameDataExtract.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/Sprite/SpriteDef.refl.h"

class SpriteResource;
class AnimationState;

struct EntityRenderState;

using SpritePtr = DocumentResourcePtr<SpriteDef, SpriteResource>;
using SpriteLoadLink = DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource>;

class SpriteResource : public DocumentResourceBase, public FrameDataExtract
{
public:
  SpriteResource(Any && load_data, uint64_t path_hash);

  NotNullPtr<SpriteDef> GetData();
  DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource> AddLoadCallback(Delegate<void, NotNullPtr<SpriteResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<SpriteResource>> && callback, DocumentResourceLoadCallbackLink<SpriteDef, SpriteResource> & load_link);

  static SpritePtr Load(czstr file_path);
  static SpriteLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<SpriteResource>> && callback, SpriteLoadLink & load_link);

  int GetAnimationIndex(uint32_t animation_name_hash) const;
  int GetAnimationLength(uint32_t animation_name_hash) const;
  void GetDefaultFrame(AnimationState & anim_state) const;
  bool FrameAdvance(uint32_t animation_name_hash, AnimationState & anim_state, bool loop = true, int frames = 1) const;
  bool SyncToFrame(uint32_t animation_name_hash, AnimationState & anim_state, int frames) const;

  void Render(EntityRenderState & render_state, Vector2 position);

  template <typename Visitor>
  void VisitEvents(Visitor && visitor, int animation_index, int animation_frame, int animation_frame_delay)
  {
    if (animation_index >= m_AnimEventInfo.size())
    {
      return;
    }

    auto ev_range = m_AnimEventInfo[animation_index];
    auto ev_start = m_AnimEvents.data();
    auto box_start = m_AnimEventBoxes.data();

    auto ev_ptr = ev_start + ev_range.first;
    auto ev_end = ev_start + ev_range.second;

    while (ev_ptr != ev_end)
    {
      if (ev_ptr->m_FrameIndex == animation_frame && ev_ptr->m_FrameDelay == animation_frame_delay)
      {
        visitor(ev_ptr->m_EventData, box_start + ev_ptr->m_EventBoxStart, box_start + ev_ptr->m_EventBoxEnd);
      }

      ++ev_ptr; 
    }
  }

  template <typename Target, typename AnimState, typename ... Args>
  void SendEventsTo(Target & target, AnimState & state, Args && ... args)
  {
    auto visitor = [&](const RPolymorphic<SpriteAnimationEventDataBase, SpriteAnimationEventTypeDatabase, SpriteAnimationEventDataTypeInfo> & ev, const Box * start, const Box * end)
    {
      target.TriggerEventHandler(ev.GetTypeNameHash(), ev.GetValue(), std::forward<Args>(args)..., start, end);
    };

    VisitEvents(visitor, state.m_AnimIndex, state.m_AnimFrame, state.m_AnimDelay);
  }

  static Box GetDefaultSingleBox();
  static FrameDataSingleLineInfo GetDefaultSingleLine();

protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  friend class SpriteEngineData;
  struct AnimEventInfo
  {
    RPolymorphic<SpriteAnimationEventDataBase, SpriteAnimationEventTypeDatabase, SpriteAnimationEventDataTypeInfo> m_EventData;
    int m_FrameIndex;
    int m_FrameDelay;
    int m_EventBoxStart;
    int m_EventBoxEnd;
  };

  SpriteDef m_Data;
  DelegateList<void, NotNullPtr<SpriteResource>> m_LoadCallbacks;

  Any m_EngineData;

  std::vector<uint32_t> m_AnimNameHashes;
  std::vector<uint32_t> m_AnimStart;
  std::vector<uint32_t> m_AnimLengths;
  std::vector<std::pair<uint32_t, uint32_t>> m_AnimEventInfo;
  std::vector<uint32_t> m_AnimTotalLengths;
  std::vector<Vector2> m_AnimationFrameSizes;
  std::vector<uint32_t> m_AnimationFrameDurations;
  std::vector<int> m_AnimationLowerEdges;

  std::vector<AnimEventInfo> m_AnimEvents;
  std::vector<Box> m_AnimEventBoxes;
};
