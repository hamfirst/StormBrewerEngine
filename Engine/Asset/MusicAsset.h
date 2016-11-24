#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class MusicAsset : public Asset
{
protected:

  virtual void PreProcessLoadedData(Buffer & buffer) override;
  virtual bool OnDataLoadComplete(Buffer & buffer) override;

protected:
  friend class AudioManager;
  friend class MusicSpec;

  Buffer m_AudioBuffer;

public:
  ASSET_HEADER_FUNCS(MusicAsset);
};
