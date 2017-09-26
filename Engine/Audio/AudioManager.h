#pragma once

#include "Foundation/Optional/Optional.h"
#include "Foundation/Handle/HandleList.h"
#include "Foundation/SparseList/SparseList.h"

#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AudioAsset.h"

#include "Engine/Audio/AudioSpec.h"
#include "Engine/Audio/VolumeCategory.h"
#include "Engine/Audio/AudioHandle.h"

#include <mutex>

class ENGINE_EXPORT AudioManager
{
public:
  AudioManager();
  ~AudioManager();

  void Init();
  void ShutDown();

  AudioHandle PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kSoundEffects, float volume = 1.0f, float pan = 0.0f, bool looping = false);
  bool IsAudioPlaying(AudioHandle handle);
  void StopAudio(AudioHandle handle);
  void SetAudioVolume(AudioHandle handle, float volume);
  void SetAudioPan(AudioHandle handle, float pan);
  void SetAudioPaused(AudioHandle handle, bool pause);

  MusicHandle PlayMusic(const AssetReference<MusicAsset> & asset_ref, VolumeCategory cat = VolumeCategory::kMusic, float volume = 1.0f, float pan = 0.0f, bool looping = false);
  bool IsMusicPlaying(MusicHandle handle);
  void StopMusic(MusicHandle handle);
  void SetMusicVolume(MusicHandle handle, float volume);
  void SetMusicPan(MusicHandle handle, float pan);
  void SetMusicPaused(MusicHandle handle, bool pause);

  float GetGlobalVolume();
  float GetVolumeForCategory(VolumeCategory cat);

  void SetGlobalVolume(float val);
  void SetVolumeCategory(VolumeCategory cat, float val);

private:

  static void AudioCallback(void * userdata, uint8_t * stream, int len);

  void GenerateAudio(uint8_t * stream, int len);

  int m_DeviceId;
  HandleList<AudioSpec> m_PlayingAudio;

#ifdef _WEB
  struct MusicInfo
  {
    std::size_t m_PlaybackId;
    AssetReference<MusicAsset> m_Asset;
    VolumeCategory m_Category;
    float m_Volume;
    float m_Pan;
    bool m_Looping;
  };

  HandleList<MusicInfo> m_PlayingMusic;
#else
  HandleList<std::unique_ptr<MusicSpec>> m_PlayingMusic;
#endif


  std::mutex m_AudioMutex;
  std::atomic_bool m_AudioShutdown;

  float m_GlobalVolume;
  float m_VolumeCategories[(int)VolumeCategory::kCount];
};

extern AudioManager g_AudioManager;
