

#include "Engine/EngineCommon.h"

#include "Foundation/Buffer/BufferUtil.h"

#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/AssetManager.h"

struct WAVE_HEADER {
  unsigned int riff;					     	// RIFF string
  unsigned int overall_size;				// overall size of file in bytes
  unsigned char wave[4];						// WAVE string
  unsigned char fmt_chunk_marker[4];			// fmt string with trailing null char
  unsigned int length_of_fmt;					// length of the format data
  unsigned short format_type;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
  unsigned short channels;						// no.of channels
  unsigned int sample_rate;					// sampling rate (blocks per second)
  unsigned int byterate;						// SampleRate * NumChannels * BitsPerSample/8
  unsigned short block_align;					// NumChannels * BitsPerSample/8
  unsigned short bits_per_sample;				// bits per sample, 8- 8bits, 16- 16 bits etc
  unsigned char data_chunk_header[4];		// DATA string or FLLR string
  unsigned int data_size;						// NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};

struct AudioInfo
{
  std::shared_ptr<uint8_t> m_AudioBuffer;
  std::size_t m_AudioSize;
  AudioFormat m_Format;
  int m_Channels;
};

int AudioAsset::PreProcessLoadedData(Buffer & buffer)
{
  std::size_t file_size = buffer.GetSize();
  if (file_size < sizeof(WAVE_HEADER))
  {
    return 1;
  }

  WAVE_HEADER * header = reinterpret_cast<WAVE_HEADER *>(buffer.Get());
  if (header->riff != 0x46464952)
  {
    return 2;
  }

  if (header->sample_rate != 44100)
  {
    return 3;
  }

  AudioFormat format;
  if (header->format_type == 3 && header->bits_per_sample == 32)
  {
    format = AudioFormat::k32BitFloat;
  }
  else if (header->format_type == 1)
  {
    if (header->bits_per_sample == 8)
    {
      format = AudioFormat::k8BitInt;
    }
    else if (header->bits_per_sample == 16)
    {
      format = AudioFormat::k16BitInt;
    }
    else
    {
      return 4;
    }
  }
  else
  {
    return 4;
  }

  auto audio_buffer = std::shared_ptr<uint8_t>(new uint8_t[header->data_size]);
  memcpy(audio_buffer.get(), header + 1, header->data_size);

  buffer = MoveToBuffer(AudioInfo{ std::move(audio_buffer), header->data_size, format, header->channels });
  return 0;
}

void AudioAsset::OnDataLoadComplete(Buffer & buffer)
{
  AudioInfo info = MoveFromBuffer<AudioInfo>(buffer);

  m_AudioBuffer = std::move(info.m_AudioBuffer);
  m_AudioBufferSize = info.m_AudioSize;
  m_AudioFormat = info.m_Format;
  m_AudioChannels = info.m_Channels;

  FinalizeAssetLoad();
}

ASSET_SOURCE_FUNCS(AudioAsset)
