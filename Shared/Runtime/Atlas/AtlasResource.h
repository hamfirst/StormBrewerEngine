#pragma once

#include "Foundation/Delegate/DelegateList.h"

#include "Runtime/FrameData/FrameData.refl.h"
#include "Runtime/FrameData/FrameDataExtract.h"
#include "Runtime/Event/Event.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourcePtr.h"
#include "Runtime/Atlas/AtlasDef.refl.h"

class AtlasResource;
class RenderState;

using AtlasPtr = DocumentResourcePtr<AtlasDef, AtlasResource>;
using AtlasLoadLink = DocumentResourceLoadCallbackLink<AtlasDef, AtlasResource>;

class AtlasResource : public DocumentResourceBase
{
public:
  AtlasResource(Any && load_data, uint32_t path_hash, czstr path);

  NotNullPtr<AtlasDef> GetData();
  AtlasLoadLink AddLoadCallback(Delegate<void, NotNullPtr<AtlasResource>> && callback);
  void AddLoadCallback(Delegate<void, NotNullPtr<AtlasResource>> && callback, DocumentResourceLoadCallbackLink<AtlasDef, AtlasResource> & load_link);

  static AtlasPtr Find(uint32_t file_path_hash);
  static AtlasPtr Load(czstr file_path);
  static AtlasLoadLink LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<AtlasResource>> && callback);
  static void LoadWithCallback(czstr file_path, Delegate<void, NotNullPtr<AtlasResource>> && callback, AtlasLoadLink & load_link);

  void Render(RenderState & render_state, czstr name, const Box & pos, const Color & color = Color(255, 255, 255, 255));
  void Render(RenderState & render_state, czstr name, const Vector2 & pos, const Color & color = Color(255, 255, 255, 255));

  template <typename T>
  NullOptPtr<T> GetEngineData()
  {
    return m_EngineData.Get<T>();
  }
protected:
  virtual void OnDataLoadComplete(const std::string & resource_data) override;
  virtual void CallAssetLoadCallbacks() override;

private:

  AtlasDef m_Data;
  DelegateList<void, NotNullPtr<AtlasResource>> m_LoadCallbacks;

  Any m_EngineData;
};
