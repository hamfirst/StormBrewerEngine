
#include "Engine/EngineCommon.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"

MusicManager g_MusicManager;


void MusicManager::Init()
{
  m_StopWatch.Start();
}

void MusicManager::CutTo(const AssetReference<MusicAsset> & music_asset, float volume)
{
  if (m_CurrentMusic)
  {
    if (m_CurrentMusic->m_Asset == music_asset)
    {
      return;
    }

    g_AudioManager.StopMusic(m_CurrentMusic->m_Handle);
  }

  m_Fader = 1.0;
  m_PendingMusic.Clear();

  m_CurrentMusic = MusicInfo{ g_AudioManager.PlayMusic(music_asset, VolumeCategory::kMusic, volume, 0.0f, true), music_asset, volume };
}

void MusicManager::FadeTo(const AssetReference<MusicAsset> & music_asset, float volume, float fade_out_time, float fade_in_time)
{
  m_PendingMusic = PendingMusicInfo{ music_asset, volume };
  m_FadeOutTime = fade_out_time;
  m_FadeInTime = fade_in_time;
}

void MusicManager::FadeOut(float fade_out_time)
{
  m_PendingMusic.Emplace();
  m_FadeOutTime = fade_out_time;
}

void MusicManager::StopAll()
{
  if (m_CurrentMusic)
  {
    g_AudioManager.StopMusic(m_CurrentMusic->m_Handle);
  }

  for (auto & clip : m_Clips)
  {
    g_AudioManager.StopMusic(clip.first);
  }
}

void MusicManager::PlayClip(const AssetReference<MusicAsset> & music_asset, float volume, bool duck_music)
{
  m_Clips.emplace_back(std::make_pair(g_AudioManager.PlayMusic(music_asset, VolumeCategory::kMusic, volume), duck_music));
}

void MusicManager::Update()
{
  auto itr = std::remove_if(m_Clips.begin(), m_Clips.end(), [](const std::pair<MusicHandle, bool> & elem) { return g_AudioManager.IsMusicPlaying(elem.first) == false; });
  m_Clips.erase(itr, m_Clips.end());

  bool duck_music = false;
  for (auto & clip : m_Clips)
  {
    duck_music |= clip.second;
  }

  if (m_CurrentMusic)
  {
    if (m_PendingMusic)
    {
      m_Fader -= (float)m_StopWatch.GetTimeSinceLastCheck() / m_FadeOutTime;
      if (m_Fader < 0)
      {
        g_AudioManager.StopMusic(m_CurrentMusic->m_Handle);

        if (m_PendingMusic->m_Asset.Resolve())
        {
          m_CurrentMusic = MusicInfo{ g_AudioManager.PlayMusic(m_PendingMusic->m_Asset, VolumeCategory::kMusic, 0.0f, 0.0f, true), m_PendingMusic->m_Asset, m_PendingMusic->m_Volume };
        }
        else
        {
          m_CurrentMusic.Clear();
        }

        m_PendingMusic.Clear();

        m_Fader = 0;
      }
    }
    else
    {
      m_Fader += (float)m_StopWatch.GetTimeSinceLastCheck() / m_FadeInTime;
      if (m_Fader >= 1.0f)
      {
        m_Fader = 1.0f;
      }


      auto vol = m_Fader * m_CurrentMusic->m_Volume;
      if (duck_music)
      {
        vol *= 0.25f;
      }

      g_AudioManager.SetMusicVolume(m_CurrentMusic->m_Handle, vol);
    }
  }
  else if (m_PendingMusic)
  {
    if (m_PendingMusic->m_Asset.Resolve())
    {
      m_CurrentMusic = MusicInfo{ g_AudioManager.PlayMusic(m_PendingMusic->m_Asset, VolumeCategory::kMusic, 0.0f, 0.0f, true), m_PendingMusic->m_Asset, m_PendingMusic->m_Volume };
    }

    m_PendingMusic.Clear();
    m_Fader = 0;
  }
}
