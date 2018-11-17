#pragma once

#include "Foundation/Allocator/IdAllocator.h"

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"

class ENGINE_EXPORT MusicAsset : public Asset
{
protected:


  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;
  virtual void CleanupAsset() override;


protected:
  friend class AudioManager;
  friend class MusicSpec;

  Buffer m_AudioBuffer;

#ifdef _WEB
  std::size_t m_MusicId = IdAllocator::kInvalidId;

public:

  void HandleLoadComplete(bool success);
#endif

public:

  ASSET_HEADER_FUNCS(MusicAsset);
};
