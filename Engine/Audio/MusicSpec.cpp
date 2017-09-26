
#include "Engine/EngineCommon.h"
#include "Engine/Audio/MusicSpec.h"


MusicSpec::MusicSpec(const AssetReference<MusicAsset> & audio_ref, VolumeCategory cat, float volume, float pan, bool looping)
{
  m_AudioAsset = audio_ref;
  m_Category = cat;
  m_Volume = volume;
  m_Pan = pan;
  m_Looping = looping;
}

MusicSpec::~MusicSpec()
{
  FreeResources();
}

bool MusicSpec::LoadFile()
{
  m_SyncState = ogg_sync_state{};

  ogg_sync_init(&m_SyncState.Value());
  const MusicAsset * asset = m_AudioAsset.Resolve();

  // TODO: Don't copy the entire file into the ogg buffer
  char * ogg_buffer = ogg_sync_buffer(&m_SyncState.Value(), (long)asset->m_AudioBuffer.GetSize());
  memcpy(ogg_buffer, asset->m_AudioBuffer.Get(), asset->m_AudioBuffer.GetSize());
  ogg_sync_wrote(&m_SyncState.Value(), (long)asset->m_AudioBuffer.GetSize());

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

void MusicSpec::Restart()
{
  FreeResources();
  LoadFile();
}

void MusicSpec::FreeResources()
{
  if (m_VorbisBlock)
  {
    vorbis_block_clear(&m_VorbisBlock.Value());
    m_VorbisBlock = {};
  }

  if (m_VorbisDSP)
  {
    vorbis_dsp_clear(&m_VorbisDSP.Value());
    m_VorbisDSP = {};
  }

  if (m_VorbisComment)
  {
    vorbis_comment_clear(&m_VorbisComment.Value());
    m_VorbisComment = {};
  }

  if (m_VorbisInfo)
  {
    vorbis_info_clear(&m_VorbisInfo.Value());
    m_VorbisInfo = {};
  }

  if (m_StreamState)
  {
    ogg_stream_clear(&m_StreamState.Value());
    m_StreamState = {};
  }

  if (m_SyncState)
  {
    ogg_sync_clear(&m_SyncState.Value());
    m_SyncState = {};
  }
}

bool MusicSpec::FillBuffer(void * data, std::size_t length, float * volume_categories, float global_volume)
{
  if (!m_SyncState)
  {
    if (LoadFile() == false)
    {
      return true;
    }
  }

  if (m_Paused)
  {
    return false;
  }

  std::size_t write_samples = length / (sizeof(float) * 2);
  float * output_ptr = (float *)data;

  float volume = m_Volume * volume_categories[(int)m_Category] * global_volume;
  float l_vol = (m_Pan > 0 ? 1.0f - m_Pan : 1.0f) * volume;
  float r_vol = (m_Pan < 0 ? 1.0f + m_Pan : 1.0f) * volume;

  while (write_samples)
  {
    if (m_SamplePos == m_NumSamples)
    {
      if (Decode())
      {
        return true;
      }
    }

    std::size_t avail_samples = m_NumSamples - m_SamplePos;
    std::size_t output_samples = std::min(write_samples, avail_samples);
    std::size_t sample_end = m_SamplePos + output_samples;

    if (m_VorbisInfo->channels == 1)
    {
      for (std::size_t index = m_SamplePos; index < sample_end; index++)
      {
        *output_ptr += m_Samples[0][index] * l_vol;
        output_ptr++;
        *output_ptr += m_Samples[0][index] * r_vol;
        output_ptr++;
      }

      write_samples -= output_samples;
      m_SamplePos += output_samples;
    }
    else
    {
      for (std::size_t index = m_SamplePos; index < sample_end; index++)
      {
        *output_ptr += m_Samples[0][index] * l_vol;
        output_ptr++;
        *output_ptr += m_Samples[1][index] * r_vol;
        output_ptr++;
      }

      write_samples -= output_samples;
      m_SamplePos += output_samples;
    }
  }

  return false;
}

bool MusicSpec::Decode()
{
  if (m_Samples)
  {
    vorbis_synthesis_read(&m_VorbisDSP.Value(), (int)m_NumSamples);
  }

  int return_val = ogg_stream_packetout(&m_StreamState.Value(), &m_Packet);
  if (return_val == 0)
  {
    // Grab some more data from the ogg stream
    if (ogg_sync_pageout(&m_SyncState.Value(), &m_Page) != 1)
    {
      return true;
    }

    if (ogg_page_eos(&m_Page))
    {
      if (m_Looping)
      {
        m_NumSamples = 0;
        m_SamplePos = 0;
        Restart();
        return false;
      }

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
  m_SamplePos = 0;
  return false;
}
