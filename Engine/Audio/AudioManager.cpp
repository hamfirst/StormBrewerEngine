
#include "Engine/EngineCommon.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/AudioFormat.h"
#include "Engine/Audio/MusicSpec.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Any/Any.h"

#include <thread>

#include <sb/vector.h>

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_log.h>

AudioManager g_AudioManager;

AudioManager::AudioManager() :
  m_PlayingAudio(128)
{
}

AudioManager::~AudioManager()
{

}

void AudioManager::Init()
{
  m_AudioShutdown = false;

  SDL_AudioSpec want = {};
  want.freq = 44100;
  want.format = AUDIO_F32;
  want.channels = 2;
#ifdef _WEB
  want.samples = 8192;
#else
  want.samples = 512;
#endif
  want.callback = &AudioManager::AudioCallback;
  want.userdata = this;

  SDL_AudioSpec obtained;
  m_DeviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &obtained, 0);

  if (m_DeviceId == 0)
  {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
  }
  else
  {
    SDL_PauseAudioDevice(m_DeviceId, 0);
  }

  printf("Audio freq: %d\n", obtained.freq);
  printf("Audio format: %d\n", obtained.format);
  printf("Audio channels: %d\n", obtained.channels);
  printf("Audio samples: %d\n", obtained.samples);
}

void AudioManager::ShutDown()
{
  std::lock_guard<std::mutex> l(m_AudioMutex);
  m_AudioShutdown = true;

  m_PlayingAudio.ReleaseAll();
  m_PlayingMusic.ReleaseAll();

  if (m_DeviceId != 0)
  {
    SDL_CloseAudioDevice(m_DeviceId);
    m_DeviceId = 0;
  }
}

AudioHandle AudioManager::PlayAudio(const AssetReference<AudioAsset> & asset_ref, float volume, float pan, bool looping)
{
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }

  std::lock_guard<std::mutex> l(m_AudioMutex);
  return m_PlayingAudio.AllocateElem(asset_ref, volume, pan, looping);
}

void AudioManager::StopAudio(AudioHandle handle)
{
  std::lock_guard<std::mutex> l(m_AudioMutex);
  m_PlayingAudio.FreeElem(handle);
}

void AudioManager::SetAudioVolume(AudioHandle handle, float volume)
{
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Volume = volume;
}

void AudioManager::SetAudioPan(AudioHandle handle, float pan)
{
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Pan = pan;
}

void AudioManager::SetAudioPaused(AudioHandle handle, bool pause)
{
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Paused = pause;
}

MusicHandle AudioManager::PlayMusic(const AssetReference<MusicAsset> & asset_ref, float volume, float pan, bool looping)
{
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }

  std::lock_guard<std::mutex> l(m_AudioMutex);
  return m_PlayingMusic.AllocateElem(std::make_unique<MusicSpec>(asset_ref, volume, pan, looping));
}

void AudioManager::StopMusic(MusicHandle handle)
{
  std::lock_guard<std::mutex> l(m_AudioMutex);
  m_PlayingMusic.FreeElem(handle);
}

void AudioManager::SetMusicVolume(MusicHandle handle, float volume)
{
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Volume = volume;
}

void AudioManager::SetMusicPan(MusicHandle handle, float pan)
{
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Pan = pan;
}

void AudioManager::SetMusicPaused(MusicHandle handle, bool pause)
{
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Paused = pause;
}

void AudioManager::AudioCallback(void * userdata, uint8_t * stream, int len)
{
  AudioManager * p_this = (AudioManager *)userdata;
  memset(stream, 0, len);

#ifndef _WEB
  std::lock_guard<std::mutex> l(p_this->m_AudioMutex);

  if (p_this->m_AudioShutdown)
  {
    return;
  }
#endif

  auto audio_callback = [=](Handle audio_handle, AudioSpec & audio_spec)
  {
    int write_len = len;
    float * write_stream = (float *)stream;

    std::size_t write_samples = len / (sizeof(float) * 2);

    do
    {
      if (audio_spec.m_Paused)
      {
        return true;
      }

      std::size_t available_data = audio_spec.m_AudioBufferSize - audio_spec.m_AudioPos;
      if (available_data == 0)
      {
        if (audio_spec.m_Looping == false || audio_spec.m_AudioBufferSize == 0)
        {
          return false;
        }

        audio_spec.m_AudioPos = 0;
        available_data = audio_spec.m_AudioBufferSize;
      }

      uint8_t * audio_start = audio_spec.m_AudioBuffer.get() + audio_spec.m_AudioPos;
      float * output_ptr = write_stream;

      float volume = audio_spec.m_Volume;
      float l_pan = audio_spec.m_Pan > 0 ? 1.0f - audio_spec.m_Pan : 1.0f;
      float r_pan = audio_spec.m_Pan < 0 ? 1.0f + audio_spec.m_Pan : 1.0f;

      if (audio_spec.m_AudioChannels == 2)
      {
        if (audio_spec.m_AudioFormat == AudioFormat::k32BitFloat)
        {
          std::size_t available_samples = available_data / (sizeof(float) * 2);
          std::size_t output_samples = std::min(available_samples, write_samples);

          float * sample_ptr = (float *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += *sample_ptr * volume * l_pan;
            sample_ptr++; output_ptr++;
            *output_ptr += *sample_ptr * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(float) * 2);
          write_samples -= output_samples;
          write_stream += output_samples;
        }
        else if (audio_spec.m_AudioFormat == AudioFormat::k16BitInt)
        {
          std::size_t available_samples = available_data / (sizeof(int16_t) * 2);
          std::size_t output_samples = std::min(available_samples, write_samples);

          int16_t * sample_ptr = (int16_t *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * l_pan;
            sample_ptr++; output_ptr++;
            *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(int16_t) * 2);
          write_samples -= output_samples;
          write_stream += output_samples;
        }
        else if (audio_spec.m_AudioFormat == AudioFormat::k8BitInt)
        {
          std::size_t available_samples = available_data / (sizeof(int8_t) * 2);
          std::size_t output_samples = std::min(available_samples, write_samples);

          int8_t * sample_ptr = (int8_t *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * l_pan;
            sample_ptr++; output_ptr++;
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(int8_t) * 2);
          write_samples -= output_samples;
          write_stream += output_samples;
        }
      }
      else
      {
        if (audio_spec.m_AudioFormat == AudioFormat::k32BitFloat)
        {
          std::size_t available_samples = available_data / (sizeof(float));
          std::size_t output_samples = std::min(available_samples, write_samples);

          float * sample_ptr = (float *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += *sample_ptr * volume * l_pan;
            output_ptr++;
            *output_ptr += *sample_ptr * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(float));
          write_samples -= output_samples;
          write_stream += output_samples;
        }
        else if (audio_spec.m_AudioFormat == AudioFormat::k16BitInt)
        {
          std::size_t available_samples = available_data / (sizeof(int16_t));
          std::size_t output_samples = std::min(available_samples, write_samples);

          int16_t * sample_ptr = (int16_t *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * l_pan;
            output_ptr++;
            *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(int16_t));
          write_samples -= output_samples;
          write_stream += output_samples;
        }
        else if (audio_spec.m_AudioFormat == AudioFormat::k8BitInt)
        {
          std::size_t available_samples = available_data / (sizeof(int8_t));
          std::size_t output_samples = std::min(available_samples, write_samples);

          int8_t * sample_ptr = (int8_t *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * l_pan;
            output_ptr++;
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * r_pan;
            sample_ptr++; output_ptr++;
          }

          audio_spec.m_AudioPos += output_samples * (sizeof(int8_t));
          write_samples -= output_samples;
          write_stream += output_samples;
        }
      }
    }
    while (audio_spec.m_Looping && write_samples > 0);

    return true;
  };

  auto music_callback = [&](Handle audio_handle, std::unique_ptr<MusicSpec> & music_spec)
  {
    return music_spec->FillBuffer(stream, len) == false;
  };

  p_this->m_PlayingAudio.Filter(audio_callback);
  p_this->m_PlayingMusic.Filter(music_callback);
}

void PlayAssetBundleSound(Any & load_data, float volume, float pan)
{
  auto load_link = load_data.Get<AudioAsset::LoadCallbackLink>();
  if (load_link == nullptr)
  {
    return;
  }

  auto audio = load_link->Get();
  if (audio == nullptr || audio->IsLoaded() == false)
  {
    return;
  }

  g_AudioManager.PlayAudio(audio, volume, pan, false);
}
