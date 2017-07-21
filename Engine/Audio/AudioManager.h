#pragma once

#include "Foundation/Optional/Optional.h"
#include "Foundation/Handle/HandleList.h"

#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AudioAsset.h"

#include "Engine/Audio/AudioSpec.h"
#include "Engine/Audio/VolumeCategory.h"

#include <mutex>

class AudioSpec;
class MusicSpec;

using AudioHandle = SpecificHandle<AudioSpec>;
using MusicHandle = SpecificHandle<MusicSpec>;

class ENGINE_EXPORT AudioManager
{
public:
  AudioManager();
  ~AudioManager();

  void Init();
  void ShutDown();

  AudioHandle PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kSoundEffects, float volume = 1.0f, float pan = 0.0f, bool looping = false);
  void StopAudio(AudioHandle handle);
  void SetAudioVolume(AudioHandle handle, float volume);
  void SetAudioPan(AudioHandle handle, float pan);
  void SetAudioPaused(AudioHandle handle, bool pause);

  MusicHandle PlayMusic(const AssetReference<MusicAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kMusic, float volume = 1.0f, float pan = 0.0f, bool looping = false);
  void StopMusic(MusicHandle handle);
  void SetMusicVolume(MusicHandle handle, float volume);
  void SetMusicPan(MusicHandle handle, float pan);
  void SetMusicPaused(MusicHandle handle, bool pause);

  float GetVolumeForCategory(VolumeCategory cat);
  void SetVolumeCategory(VolumeCategory cat, float val);

private:

  static void AudioCallback(void * userdata, uint8_t * stream, int len);

  int m_DeviceId;
  HandleList<AudioSpec> m_PlayingAudio;
  HandleList<std::unique_ptr<MusicSpec>> m_PlayingMusic;

  std::mutex m_AudioMutex;
  std::atomic_bool m_AudioShutdown;

  float m_VolumeCategories[(int)VolumeCategory::kCount];
};

extern AudioManager g_AudioManager;
