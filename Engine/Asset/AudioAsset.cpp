

#include "Engine/EngineCommon.h"

#include "Foundation/Buffer/BufferUtil.h"

#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/AssetManager.h"

#include <vorbis/codec.h>

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
  std::shared_ptr<uint8_t[]> m_AudioBuffer;
  std::size_t m_AudioSize;
  AudioFormat m_Format;
  int m_Channels;
};

class VorbisDecoder
{
public:

  struct VorbisDecodeInfo
  {
    std::shared_ptr<uint8_t[]> m_Data;
    std::size_t m_Size;
    int m_NumChannels;
  };

  VorbisDecoder()
  {

  }

  ~VorbisDecoder()
  {
    if (m_VorbisBlock)
    {
      vorbis_block_clear(&m_VorbisBlock.Value());
      m_VorbisBlock.Clear();
    }

    if (m_VorbisDSP)
    {
      vorbis_dsp_clear(&m_VorbisDSP.Value());
      m_VorbisDSP.Clear();
    }

    if (m_VorbisComment)
    {
      vorbis_comment_clear(&m_VorbisComment.Value());
      m_VorbisComment.Clear();
    }

    if (m_VorbisInfo)
    {
      vorbis_info_clear(&m_VorbisInfo.Value());
      m_VorbisInfo.Clear();
    }

    if (m_StreamState)
    {
      ogg_stream_clear(&m_StreamState.Value());
      m_StreamState.Clear();
    }

    if (m_SyncState)
    {
      ogg_sync_clear(&m_SyncState.Value());
      m_SyncState.Clear();
    }
  }

  bool Load(Buffer & buffer)
  {
    m_SyncState = ogg_sync_state{};

    ogg_sync_init(&m_SyncState.Value());

    // TODO: Don't copy the entire file into the ogg buffer
    char * ogg_buffer = ogg_sync_buffer(&m_SyncState.Value(), (long)buffer.GetSize());
    memcpy(ogg_buffer, buffer.Get(), buffer.GetSize());
    ogg_sync_wrote(&m_SyncState.Value(), (long)buffer.GetSize());

    if (ogg_sync_pageout(&m_SyncState.Value(), &m_Page) != 1)
    {
      fprintf(stderr, "Couldn't read initial ogg page\n");
      return false;
    }

    m_StreamState = ogg_stream_state{};
    ogg_stream_init(&m_StreamState.Value(), ogg_page_serialno(&m_Page));

    if (ogg_stream_pagein(&m_StreamState.Value(), &m_Page) == -1)
    {
      fprintf(stderr, "Couldn't submit initial ogg page\n");
      return false;
    }

    if (ogg_stream_packetout(&m_StreamState.Value(), &m_Packet) != 1)
    {
      fprintf(stderr, "Couldn't read initial packet\n");
      return false;
    }

    if (!vorbis_synthesis_idheader(&m_Packet))
    {
      fprintf(stderr, "Input ogg file is not vorbis\n");
      return false;
    }

    m_VorbisInfo = vorbis_info{};
    m_VorbisComment = vorbis_comment{};

    vorbis_info_init(&m_VorbisInfo.Value());
    vorbis_comment_init(&m_VorbisComment.Value());

    vorbis_synthesis_headerin(&m_VorbisInfo.Value(), &m_VorbisComment.Value(), &m_Packet);

    for (int index = 0; index < 2; index++)
    {
      int return_val = ogg_stream_packetout(&m_StreamState.Value(), &m_Packet);
      if (return_val == 0)
      {
        // Grab some more data from the ogg stream
        if (ogg_sync_pageout(&m_SyncState.Value(), &m_Page) != 1)
        {
          fprintf(stderr, "Couldn't read header ogg page\n");
          return false;
        }

        if (ogg_stream_pagein(&m_StreamState.Value(), &m_Page) == -1)
        {
          fprintf(stderr, "Couldn't submit header ogg page\n");
          return false;
        }

        return_val = ogg_stream_packetout(&m_StreamState.Value(), &m_Packet);
        if (return_val != 1)
        {
          fprintf(stderr, "Error reading header\n");
          return false;
        }
      }
      else if (return_val == -1)
      {
        fprintf(stderr, "Fatal error reading header\n");
        return false;
      }

      vorbis_synthesis_headerin(&m_VorbisInfo.Value(), &m_VorbisComment.Value(), &m_Packet);
    }

    m_VorbisDSP = vorbis_dsp_state{};
    if (vorbis_synthesis_init(&m_VorbisDSP.Value(), &m_VorbisInfo.Value()) == 1)
    {
      fprintf(stderr, "Error initializing vorbis decoder\n");
      return false;
    }

    m_VorbisBlock = vorbis_block{};
    vorbis_block_init(&m_VorbisDSP.Value(), &m_VorbisBlock.Value());
    return true;
  }

  bool DecodeChunk()
  {
    if (m_Samples)
    {
      vorbis_synthesis_read(&m_VorbisDSP.Value(), (int)m_NumSamples);
    }

    m_NumSamples = 0;

    int return_val = ogg_stream_packetout(&m_StreamState.Value(), &m_Packet);
    if (return_val == 0)
    {
      // Grab some more data from the ogg stream
      if (ogg_sync_pageout(&m_SyncState.Value(), &m_Page) != 1)
      {
        return true;
      }

      if (ogg_stream_pagein(&m_StreamState.Value(), &m_Page) == -1)
      {
        fprintf(stderr, "Couldn't submit ogg page\n");
        return true;
      }

      return_val = ogg_stream_packetout(&m_StreamState.Value(), &m_Packet);
      if (return_val != 1)
      {
        fprintf(stderr, "Error reading packet\n");
        return true;
      }
    }
    else if (return_val == -1)
    {
      fprintf(stderr, "Fatal error reading header\n");
      return true;
    }

    return_val = vorbis_synthesis(&m_VorbisBlock.Value(), &m_Packet);
    if (return_val != 0)
    {
      fprintf(stderr, "Error decoding vorbis data\n");
      return true;
    }

    return_val = vorbis_synthesis_blockin(&m_VorbisDSP.Value(), &m_VorbisBlock.Value());
    if (return_val != 0)
    {
      fprintf(stderr, "Error decoding vorbis block\n");
      return true;
    }

    m_NumSamples = vorbis_synthesis_pcmout(&m_VorbisDSP.Value(), &m_Samples);
    return false;
  }

  VorbisDecodeInfo Decode()
  {
    std::vector<std::pair<std::unique_ptr<float[]>, std::size_t>> blocks;

    std::size_t total_samples = 0;
    while (true)
    {
      bool completed = false;
      if (DecodeChunk())
      {
        completed = true;
      }

      if (m_NumSamples > 0)
      {
        if (m_VorbisInfo->channels == 1)
        {
          auto buffer = std::make_unique<float[]>(m_NumSamples);
          memcpy(buffer.get(), m_Samples[0], sizeof(float) * m_NumSamples);

          blocks.emplace_back(std::make_pair(std::move(buffer), m_NumSamples));
          total_samples += m_NumSamples;
        }
        else
        {
          auto buffer = std::make_unique<float[]>(m_NumSamples * 2);

          for (auto l = m_Samples[0], r = m_Samples[1], dst = buffer.get(), end = dst + m_NumSamples * 2; dst != end; ++l, ++r)
          {
            *dst = *l;
            ++dst;
            *dst = *r;
            ++dst;
          }

          blocks.emplace_back(std::make_pair(std::move(buffer), m_NumSamples * 2));
          total_samples += m_NumSamples * 2;
        }
      }

      if (completed)
      {
        break;
      }
    }

    auto final_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[total_samples * sizeof(float)]);
    auto dst = reinterpret_cast<float *>(final_buffer.get());

    for (auto & elem : blocks)
    {
      memcpy(dst, elem.first.get(), sizeof(float) * elem.second);
      dst += elem.second;
    }

    return VorbisDecodeInfo{ std::move(final_buffer), total_samples, m_VorbisInfo->channels };
  }

private:

  Optional<ogg_sync_state> m_SyncState;
  ogg_page m_Page;

  Optional<ogg_stream_state> m_StreamState;
  ogg_packet m_Packet;

  Optional<vorbis_info> m_VorbisInfo;
  Optional<vorbis_comment> m_VorbisComment;
  Optional<vorbis_block> m_VorbisBlock;
  Optional<vorbis_dsp_state> m_VorbisDSP;

  float ** m_Samples = nullptr;
  std::size_t m_NumSamples = 0;
};



int AudioAsset::PreProcessLoadedData(Buffer & buffer, bool load_deps)
{
  std::size_t file_size = buffer.GetSize();
  if (file_size < 4)
  {
    return 1;
  }

  auto file_type = reinterpret_cast<uint32_t *>(buffer.Get());
  if (*file_type == 0x5367674F)
  {
    return DecodeVorbisFile(buffer);
  }
  else
  {
    return DecodeWavFile(buffer);
  }
}

void AudioAsset::OnDataLoadComplete(Buffer & buffer, bool load_deps)
{
  AudioInfo info = MoveFromBuffer<AudioInfo>(buffer);

  m_AudioBuffer = std::move(info.m_AudioBuffer);
  m_AudioBufferSize = info.m_AudioSize;
  m_AudioFormat = info.m_Format;
  m_AudioChannels = info.m_Channels;

  FinalizeAssetLoad();
}


int AudioAsset::DecodeVorbisFile(Buffer & buffer)
{
  VorbisDecoder decoder;
  if (decoder.Load(buffer) == false)
  {
    return 1;
  }

  auto data = decoder.Decode();
  buffer = MoveToBuffer(AudioInfo{ std::move(data.m_Data), data.m_Size * sizeof(float), AudioFormat::k32BitFloat, data.m_NumChannels });
  return 0;
}

int AudioAsset::DecodeWavFile(Buffer & buffer)
{
  std::size_t file_size = buffer.GetSize();
  if (file_size < sizeof(WAVE_HEADER))
  {
    printf("%s: Invalid wave file header\n", GetFileName().data());
    return 1;
  }

  WAVE_HEADER * header = reinterpret_cast<WAVE_HEADER *>(buffer.Get());
  if (header->riff != 0x46464952)
  {
    printf("%s: Invalid wave file type\n", GetFileName().data());
    return 2;
  }

  if (header->sample_rate != 44100)
  {
    printf("%s: Invalid wave sample rate: %d\n", GetFileName().data(), header->sample_rate);
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
      printf("%s: Invalid wave format: %d\n", GetFileName().data(), header->format_type);
      return 4;
    }
  }
  else
  {
    printf("%s: Invalid wave format: %d\n", GetFileName().data(), header->format_type);
    return 4;
  }

  auto audio_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[header->data_size]);
  memcpy(audio_buffer.get(), header + 1, header->data_size);

  buffer = MoveToBuffer(AudioInfo{ std::move(audio_buffer), header->data_size, format, header->channels });
  return 0;
}

ASSET_SOURCE_FUNCS(AudioAsset)
