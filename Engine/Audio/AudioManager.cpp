
#include "Engine/EngineCommon.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/AudioFormat.h"
#include "Engine/Audio/MusicSpec.h"

#include <thread>

#include <sb/vector.h>

#include <SDL/SDL_audio.h>
#include <SDL/SDL_log.h>

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
  SDL_AudioSpec want = {};
  want.freq = 44100;
  want.format = AUDIO_F32;
  want.channels = 2;
  want.samples = 512;
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
}

void AudioManager::ShutDown()
{
  if (m_DeviceId != 0)
  {
    SDL_CloseAudioDevice(m_DeviceId);
    m_DeviceId = 0;
  }
}

AudioHandle AudioManager::PlayAudio(const AssetReference<AudioAsset> & asset_ref, float volume, float pan)
{
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }

  std::lock_guard<std::mutex> l(m_AudioMutex);
  return m_PlayingAudio.AllocateElem(asset_ref, volume, pan);
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

MusicHandle AudioManager::PlayMusic(const AssetReference<MusicAsset> & asset_ref, float volume, float pan)
{
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }

  std::lock_guard<std::mutex> l(m_AudioMutex);
  return m_PlayingMusic.AllocateElem(std::make_unique<MusicSpec>(asset_ref, volume, pan));
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
  memset(stream, 0, len);

  std::size_t write_samples = len / (sizeof(float) * 2);

  AudioManager * p_this = (AudioManager *)userdata;
  std::lock_guard<std::mutex> l(p_this->m_AudioMutex);

  auto audio_callback = [&](Handle audio_handle, AudioSpec & audio_spec)
  {
    if (audio_spec.m_Paused)
    {
      return true;
    }

    std::size_t available_data = audio_spec.m_AudioBufferSize - audio_spec.m_AudioPos;
    if (available_data  == 0)
    {
      return false;
    }

    uint8_t * audio_start = audio_spec.m_AudioBuffer.get() + audio_spec.m_AudioPos;
    float * output_ptr = (float *)stream;

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
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += *sample_ptr * volume * l_pan;
          sample_ptr++; output_ptr++;
          *output_ptr += *sample_ptr * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(float) * 2);
      }
      else if (audio_spec.m_AudioFormat == AudioFormat::k16BitInt)
      {
        std::size_t available_samples = available_data / (sizeof(int16_t) * 2);
        std::size_t output_samples = std::min(available_samples, write_samples);

        int16_t * sample_ptr = (int16_t *)audio_start;
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * l_pan;
          sample_ptr++; output_ptr++;
          *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(int16_t) * 2);
      }
      else if (audio_spec.m_AudioFormat == AudioFormat::k8BitInt)
      {
        std::size_t available_samples = available_data / (sizeof(int8_t) * 2);
        std::size_t output_samples = std::min(available_samples, write_samples);

        int8_t * sample_ptr = (int8_t *)audio_start;
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * l_pan;
          sample_ptr++; output_ptr++;
          *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(int8_t) * 2);
      }
    }
    else
    {
      if (audio_spec.m_AudioFormat == AudioFormat::k32BitFloat)
      {
        std::size_t available_samples = available_data / (sizeof(float));
        std::size_t output_samples = std::min(available_samples, write_samples);

        float * sample_ptr = (float *)audio_start;
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += *sample_ptr * volume * l_pan;
          output_ptr++;
          *output_ptr += *sample_ptr * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(float));
      }
      else if (audio_spec.m_AudioFormat == AudioFormat::k16BitInt)
      {
        std::size_t available_samples = available_data / (sizeof(int16_t));
        std::size_t output_samples = std::min(available_samples, write_samples);

        int16_t * sample_ptr = (int16_t *)audio_start;
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * l_pan;
          output_ptr++;
          *output_ptr += ((float)*sample_ptr) / 32768.0f * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(int16_t));
      }
      else if (audio_spec.m_AudioFormat == AudioFormat::k8BitInt)
      {
        std::size_t available_samples = available_data / (sizeof(int8_t));
        std::size_t output_samples = std::min(available_samples, write_samples);

        int8_t * sample_ptr = (int8_t *)audio_start;
        for (int sample = 0; sample < output_samples; sample++)
        {
          *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * l_pan;
          output_ptr++;
          *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * volume * r_pan;
          sample_ptr++; output_ptr++;
        }

        audio_spec.m_AudioPos += output_samples * (sizeof(int8_t));
      }
    }

    return true;
  };

  auto music_callback = [&](Handle audio_handle, std::unique_ptr<MusicSpec> & music_spec)
  {
    return music_spec->FillBuffer(stream, len) == false;
  };

  p_this->m_PlayingAudio.Filter(audio_callback);
  p_this->m_PlayingMusic.Filter(music_callback);
}
