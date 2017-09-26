#pragma once

#include <memory>

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class ENGINE_EXPORT AudioAsset : public Asset
{
protected:

  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;

protected:

  int DecodeVorbisFile(Buffer & buffer);
  int DecodeWavFile(Buffer & buffer);

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
