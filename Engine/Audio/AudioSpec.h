#pragma once

#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/AssetReference.h"

class AudioSpec
{
public:

  AudioSpec(const AssetReference<AudioAsset> & audio_ref, float volume, float pan) :
    m_AudioAsset(audio_ref),
    m_AudioBuffer(audio_ref.Resolve()->m_AudioBuffer),
    m_AudioBufferSize(audio_ref.Resolve()->m_AudioBufferSize),
    m_AudioFormat(audio_ref.Resolve()->m_AudioFormat),
    m_AudioChannels(audio_ref.Resolve()->m_AudioChannels),
    m_Volume(volume),
    m_Pan(pan)
  {
    m_Volume = volume;
    m_Pan = pan;
  }

  AudioSpec(const AudioSpec & rhs) = default;
  AudioSpec(AudioSpec && rhs) = default;

  AudioSpec & operator = (const AudioSpec & rhs) = default;
  AudioSpec & operator = (AudioSpec && rhs) = default;

private:

  friend class AudioManager;

  AssetReference<AudioAsset> m_AudioAsset;

  std::shared_ptr<uint8_t> m_AudioBuffer;
  std::size_t m_AudioBufferSize;

  AudioFormat m_AudioFormat;
  int m_AudioChannels;

  float m_Volume;
  float m_Pan;

  std::size_t m_AudioPos = 0;
  bool m_Paused = false;
};

