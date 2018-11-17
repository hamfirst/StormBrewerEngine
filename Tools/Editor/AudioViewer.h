#pragma once

#include <QWidget>

#include "Engine/EngineCommon.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Asset/AudioAsset.h"
#include "Engine/Asset/MusicAsset.h"

class QPushButton;
class QSlider;

class AudioViewer : public QWidget
{
  Q_OBJECT

public:
  AudioViewer(bool is_audio, const char * file_path, QWidget *parent = nullptr);
  ~AudioViewer();

public slots:

  void play(bool);
  void stop(bool);
  void pause(bool);
  void changeVolume(int vol_val);
  void changePan(int pan_val);

private:
  QPushButton * m_PlayButton;
  QPushButton * m_StopButton;
  QPushButton * m_PauseButton;
  QSlider * m_VolumeSlider;
  QSlider * m_PanSlider;

  bool m_IsAudio;
  bool m_IsPaused;
  Optional<AudioHandle> m_AudioHandle;
  Optional<MusicHandle> m_MusicHandle;

  AssetReference<AudioAsset> m_AudioAsset;
  AssetReference<MusicAsset> m_MusicAsset;
};
