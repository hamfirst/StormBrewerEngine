#pragma once

#include "Engine/Asset/MusicAsset.h"
#include "Engine/Asset/AssetReference.h"

#include "Foundation/Optional/Optional.h"

#include <ogg/ogg.h>
#include <vorbis/codec.h>

class MusicSpec
{
public:

  MusicSpec(const AssetReference<MusicAsset> & audio_ref, float volume, float pan);
  ~MusicSpec();

  MusicSpec(const MusicSpec & rhs) = default;
  MusicSpec(MusicSpec && rhs) = default;

  MusicSpec & operator = (const MusicSpec & rhs) = default;
  MusicSpec & operator = (MusicSpec && rhs) = default;

private:

  bool LoadFile();
  bool FillBuffer(void * data, std::size_t length);
  bool Decode();

private:

  friend class AudioManager;

  AssetReference<MusicAsset> m_AudioAsset;

  float m_Volume;
  float m_Pan;
  bool m_Paused = false;

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
  std::size_t m_SamplePos = 0;
};

