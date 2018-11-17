#pragma once

#include "Foundation/Time/StopWatch.h"

#include "Engine/Asset/MusicAsset.h"
#include "Engine/Audio/AudioHandle.h"

class MusicManager
{
public:

  void CutTo(const AssetReference<MusicAsset> & music_asset, float volume);
  void FadeTo(const AssetReference<MusicAsset> & music_asset, float volume, float fade_out_time, float fade_in_time);
  void FadeOut(float fade_out_time);
  void StopAll();

  void PlayClip(const AssetReference<MusicAsset> & music_asset, float volume, bool duck_music);

protected:

  friend bool EngineInit(bool, bool);
  friend void EngineUpdate();
  friend void EngineCleanup();

  void Init();
  void Update();
  void ShutDown();

private:

  StopWatch m_StopWatch;
  float m_Fader = 0.0f;
  float m_FadeOutTime = 1.0f;
  float m_FadeInTime = 1.0f;


  struct MusicInfo
  {
    MusicHandle m_Handle;
    AssetReference<MusicAsset> m_Asset;
    float m_Volume;
  };

  struct PendingMusicInfo
  {
    AssetReference<MusicAsset> m_Asset;
    float m_Volume;
  };

  Optional<MusicInfo> m_CurrentMusic;
  Optional<PendingMusicInfo> m_PendingMusic;

  std::vector<std::pair<MusicHandle, bool>> m_Clips;
};

extern MusicManager g_MusicManager;