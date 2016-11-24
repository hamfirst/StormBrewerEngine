#pragma once

#include <memory>

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class AudioAsset : public Asset
{
protected:

  virtual void PreProcessLoadedData(Buffer & buffer) override;
  virtual bool OnDataLoadComplete(Buffer & buffer) override;

protected:
  friend class AudioManager;
  friend class AudioSpec;

  std::shared_ptr<uint8_t> m_AudioBuffer;
  std::size_t m_AudioBufferSize;

  AudioFormat m_AudioFormat;
  int m_AudioChannels;

public:
  ASSET_HEADER_FUNCS(AudioAsset);
};
