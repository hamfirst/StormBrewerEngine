
#include "Engine/EngineCommon.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/AudioFormat.h"
#include "Engine/Audio/MusicSpec.h"
#include "Engine/Asset/AudioAsset.h"

#include "Foundation/Any/Any.h"
#include "Foundation/CircularBuffer/CircularQueue.h"

#include <thread>

#include <sb/vector.h>

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_log.h>

#include <resample/smarc.h>


#ifdef _WEB

#include "Foundation/Allocator/IdAllocator.h"
#include "Foundation/SparseList/SparseList.h"

#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

SparseList<MusicHandle> s_MusicPlaybackLookup;
IdAllocator s_MusicPlaybackIdAllocator;

extern "C"
{
  void HandleMusicFinished(std::size_t playback_id)
  {
    auto handle = s_MusicPlaybackLookup.TryGet(playback_id);
    if (handle == nullptr)
    {
      return;
    }

    g_AudioManager.StopMusic(*handle);
  }
}

#endif

AudioManager g_AudioManager;

static const int kWaveSize = 512;
static float s_Wave[kWaveSize * 2];
static int s_WaveIndex = 0;

static int s_AudioDeviceFreq = 0;
static PFilter * s_AudioResamplerFilter;
static PState * s_AudioResampler[2];

CircularQueue<float, 8192> s_ResampleInputBuffer;
CircularQueue<float, 8192> s_ResampleOutputBuffer[2];

AudioManager::AudioManager() :
  m_PlayingAudio(128)
{
  m_GlobalVolume = 1.0f;
  for (int index = 0; index < (int)VolumeCategory::kCount; ++index)
  {
    m_VolumeCategories[index] = 0.85f;
  }

  m_VolumeCategories[(int)VolumeCategory::kMusic] = 0.5f;
}

AudioManager::~AudioManager()
{

}

void AudioManager::Init()
{
  for (int index = 0; index < kWaveSize * 2; ++index)
  {
    auto val = sinf(((float)index / (float)kWaveSize) * k2Pi) * 0.5f;
    s_Wave[index] = val;
    index++;
    s_Wave[index] = val;
  }

  m_AudioShutdown = false;

  SDL_AudioSpec want = {};

  want.freq = 44100;
  want.format = AUDIO_F32;
  want.channels = 2;
  want.samples = 512;

  want.callback = &AudioManager::AudioCallback;
  want.userdata = this;

  int flags = 0;
#ifdef _WEB
  flags = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE;
#endif

  SDL_AudioSpec obtained;
  m_DeviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &obtained, flags);

  if (m_DeviceId == 0)
  {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
  }
  else
  {
    s_AudioDeviceFreq = obtained.freq;
    if (s_AudioDeviceFreq != 44100)
    {
      s_AudioResamplerFilter = smarc_init_pfilter(44100, s_AudioDeviceFreq, 0.9f, 0.1f, 140, 0.00001f, nullptr, 0);

      for (int channel = 0; channel < 2; ++channel)
      {
        s_AudioResampler[channel] = smarc_init_pstate(s_AudioResamplerFilter);
      }
    }

    SDL_PauseAudioDevice(m_DeviceId, 0);
  }
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

AudioHandle AudioManager::PlayAudio(const AssetReference<AudioAsset> & asset_ref, VolumeCategory cat, float volume, float pan, bool looping)
{
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }

  if (asset_ref.Resolve() == nullptr)
  {
    return kInvalidHandle;
  }

#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);
#endif
  return m_PlayingAudio.AllocateElem(asset_ref, cat, volume, pan, looping);
}

bool AudioManager::IsAudioPlaying(AudioHandle handle)
{
#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);
#endif
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  return (audio_spec != nullptr);
}

void AudioManager::StopAudio(AudioHandle handle)
{
#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);
#endif
  m_PlayingAudio.FreeElem(handle);
}

void AudioManager::SetAudioVolume(AudioHandle handle, float volume)
{
#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);
#endif
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Volume = volume;
}

void AudioManager::SetAudioPan(AudioHandle handle, float pan)
{
#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);
#endif
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Pan = pan;
}

void AudioManager::SetAudioPaused(AudioHandle handle, bool pause)
{
#ifdef _WEB

#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  auto audio_spec = m_PlayingAudio.Resolve(handle);
  if (audio_spec == nullptr) return;
  audio_spec->m_Paused = pause;
#endif
}

MusicHandle AudioManager::PlayMusic(const AssetReference<MusicAsset> & asset_ref, VolumeCategory cat, float volume, float pan, bool looping)
{
#ifdef _WEB
  auto asset = asset_ref.Resolve();
  if (asset == nullptr)
  {
    return kInvalidHandle;
  }

  auto playback_id = s_MusicPlaybackIdAllocator.Allocate();
  auto handle = m_PlayingMusic.AllocateElem(MusicInfo{ playback_id, asset_ref, cat, volume, pan, looping});

  s_MusicPlaybackLookup.EmplaceAt(playback_id, handle);

  EM_ASM_ARGS({ PlayMusic($0, $1, $2, $3, $4); }, asset->m_MusicId, playback_id, looping, volume * m_VolumeCategories[(int)cat] * m_GlobalVolume, pan);
  return handle;
#else
  if (m_DeviceId == 0)
  {
    return kInvalidHandle;
  }


  std::lock_guard<std::mutex> l(m_AudioMutex);
  return m_PlayingMusic.AllocateElem(std::make_unique<MusicSpec>(asset_ref, cat, volume, pan, looping));
#endif
}

bool AudioManager::IsMusicPlaying(MusicHandle handle)
{
#ifdef _WEB
  auto music_info = m_PlayingMusic.Resolve(handle);
  return (music_info != nullptr);
#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  auto music_spec = m_PlayingMusic.Resolve(handle);
  return (music_spec != nullptr);
#endif
}

void AudioManager::StopMusic(MusicHandle handle)
{
#ifdef _WEB
  auto music_info = m_PlayingMusic.Resolve(handle);
  if (music_info != nullptr)
  {
    s_MusicPlaybackLookup.RemoveAt(music_info->m_PlaybackId);
    s_MusicPlaybackIdAllocator.Release(music_info->m_PlaybackId);

    EM_ASM_ARGS({ StopMusic($0); }, music_info->m_PlaybackId);

    m_PlayingMusic.FreeElem(handle);
  }
#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  m_PlayingMusic.FreeElem(handle);
#endif
}

void AudioManager::SetMusicVolume(MusicHandle handle, float volume)
{
#ifdef _WEB
  auto music_info = m_PlayingMusic.Resolve(handle);
  if (music_info != nullptr)
  {
    music_info->m_Volume = volume;
    EM_ASM_ARGS({ SetMusicVolume($0, $1); }, music_info->m_PlaybackId, volume * m_VolumeCategories[(int)music_info->m_Category] * m_GlobalVolume);
  }
#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Volume = volume;
#endif
}

void AudioManager::SetMusicPan(MusicHandle handle, float pan)
{
#ifdef _WEB
  auto music_info = m_PlayingMusic.Resolve(handle);
  if (music_info != nullptr)
  {
    music_info->m_Pan = pan;
    EM_ASM_ARGS({ SetMusicPan($0, $1); }, music_info->m_PlaybackId, pan);
  }
#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Pan = pan;
#endif
}

void AudioManager::SetMusicPaused(MusicHandle handle, bool pause)
{
#ifdef _WEB

#else
  std::lock_guard<std::mutex> l(m_AudioMutex);
  auto music_spec = m_PlayingMusic.Resolve(handle);
  if (music_spec == nullptr) return;
  (*music_spec)->m_Paused = pause;
#endif
}

float AudioManager::GetGlobalVolume()
{
  return m_GlobalVolume;
}

float AudioManager::GetVolumeForCategory(VolumeCategory cat)
{
  return m_VolumeCategories[(int)cat];
}

void AudioManager::SetGlobalVolume(float val)
{
  m_GlobalVolume = val;

#ifdef _WEB

  m_PlayingMusic.VisitEach([this](Handle & handle, MusicInfo & music_info) {
    EM_ASM_ARGS({ SetMusicVolume($0, $1); }, music_info.m_PlaybackId, music_info.m_Volume * m_VolumeCategories[(int)music_info.m_Category] * m_GlobalVolume);
  });

#endif
}

void AudioManager::SetVolumeCategory(VolumeCategory cat, float val)
{
  m_VolumeCategories[(int)cat] = val;

#ifdef _WEB

  m_PlayingMusic.VisitEach([this](Handle & handle, MusicInfo & music_info) {
    EM_ASM_ARGS({ SetMusicVolume($0, $1); }, music_info.m_PlaybackId, music_info.m_Volume * m_VolumeCategories[(int)music_info.m_Category] * m_GlobalVolume);
  });

#endif
}

void AudioManager::AudioCallback(void * userdata, uint8_t * stream, int len)
{
  AudioManager * p_this = (AudioManager *)userdata;
  if (s_AudioDeviceFreq == 44100)
  {
    p_this->GenerateAudio(stream, len);
  }
  else
  {
    float * dst_data = (float *)stream;
    int write_samples = len / (sizeof(float) * 2);

    float * out_buffer[2] = { &dst_data[0], &dst_data[1] };
    int to_write[2] = { write_samples, write_samples };

    while (true)
    {
      for (int channel = 0; channel < 2; ++channel)
      {
        auto wrote = s_ResampleOutputBuffer[channel].BlockReadStride(out_buffer[channel], to_write[channel], 2);
        out_buffer[channel] += (wrote * 2);
        to_write[channel] -= wrote;
      }

      if (to_write[0] == 0 && to_write[1] == 0)
      {
        break;
      }

      static const int kResampleInputSize = 1024;
      static float resample_input_buffer[kResampleInputSize * 2];

      p_this->GenerateAudio((uint8_t *)resample_input_buffer, sizeof(resample_input_buffer));

      for (int channel = 0; channel < 2; ++channel)
      {
        static double input_buffer[kResampleInputSize];
        float * src = &resample_input_buffer[channel];
        auto dst = &input_buffer[0];
        
        auto end = dst + (kResampleInputSize);
        while (dst != end)
        {
          *dst = *src;
          src += 2;
          dst++;
        }

        static double output_buffer[kResampleInputSize * 2];
        int out = smarc_resample(s_AudioResamplerFilter, s_AudioResampler[channel], input_buffer, kResampleInputSize, output_buffer, kResampleInputSize * 2);

        s_ResampleOutputBuffer[channel].BlockWrite(output_buffer, out);

        //s_ResampleOutputBuffer[channel].BlockWrite(input_buffer, kResampleInputSize);
      }
    }
  }
}

void AudioManager::GenerateAudio(uint8_t * stream, int len)
{
  //int write_samples = len / (sizeof(float) * 2);
  //printf("Processing %d audio samples (buffer size %d)\n", write_samples, len);

  ////printf("Processing %d audio samples (buffer size %d)\n", write_samples, len);
  //auto wave_ptr = (float *)stream;
  //while (write_samples > 0)
  //{
  //  auto data_avail = (int)(kWaveSize - s_WaveIndex);
  //  auto data_to_write = std::min(data_avail, write_samples);

  //  memcpy(wave_ptr, &s_Wave[s_WaveIndex * 2], write_samples * sizeof(float) * 2);
  //  s_WaveIndex += data_to_write;
  //  wave_ptr += (data_to_write * 2);

  //  if (s_WaveIndex >= kWaveSize)
  //  {
  //    s_WaveIndex = 0;
  //  }

  //  write_samples -= data_to_write;
  //}

  //return;

  memset(stream, 0, len);

#ifndef _WEB
  std::lock_guard<std::mutex> l(m_AudioMutex);

  if (m_AudioShutdown)
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

      float volume = audio_spec.m_Volume * m_VolumeCategories[(int)audio_spec.m_Category] * m_GlobalVolume;
      float l_vol = (audio_spec.m_Pan > 0 ? 1.0f - audio_spec.m_Pan : 1.0f) * volume;
      float r_vol = (audio_spec.m_Pan < 0 ? 1.0f + audio_spec.m_Pan : 1.0f) * volume;

      if (audio_spec.m_AudioChannels == 2)
      {
        if (audio_spec.m_AudioFormat == AudioFormat::k32BitFloat)
        {
          std::size_t available_samples = available_data / (sizeof(float) * 2);
          std::size_t output_samples = std::min(available_samples, write_samples);

          float * sample_ptr = (float *)audio_start;
          for (int sample = 0; sample < (int)output_samples; sample++)
          {
            *output_ptr += *sample_ptr * l_vol;
            sample_ptr++; output_ptr++;
            *output_ptr += *sample_ptr * r_vol;
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
            *output_ptr += ((float)*sample_ptr) / 32768.0f * l_vol;
            sample_ptr++; output_ptr++;
            *output_ptr += ((float)*sample_ptr) / 32768.0f * r_vol;
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
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * l_vol;
            sample_ptr++; output_ptr++;
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * r_vol;
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
            *output_ptr += *sample_ptr * l_vol;
            output_ptr++;
            *output_ptr += *sample_ptr * r_vol;
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
            *output_ptr += ((float)*sample_ptr) / 32768.0f * l_vol;
            output_ptr++;
            *output_ptr += ((float)*sample_ptr) / 32768.0f * r_vol;
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
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * l_vol;
            output_ptr++;
            *output_ptr += (((float)*sample_ptr) / 127.0f - 1.0f) * r_vol;
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

  m_PlayingAudio.Filter(audio_callback);

#ifndef _WEB
  auto music_callback = [&](Handle audio_handle, std::unique_ptr<MusicSpec> & music_spec)
  {
    return music_spec->FillBuffer(stream, len, m_VolumeCategories, m_GlobalVolume) == false;
  };

  m_PlayingMusic.Filter(music_callback);
#endif
}

void PlayAssetBundleSound(Any & load_data, VolumeCategory cat, float volume, float pan)
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

  g_AudioManager.PlayAudio(audio, cat, volume, pan, false);
}
