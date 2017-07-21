#include "AudioViewer.h"

#include <QStyle>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QBoxLayout>
#include <QGroupBox>


AudioViewer::AudioViewer(bool is_audio, const char * file_path, QWidget *parent) :
  QWidget(parent),
  m_IsAudio(is_audio),
  m_IsPaused(false),
  m_PlayButton(new QPushButton(this)),
  m_StopButton(new QPushButton(this)),
  m_PauseButton(new QPushButton(this)),
  m_VolumeSlider(new QSlider(this)),
  m_PanSlider(new QSlider(this))
{
  if (m_IsAudio)
  {
    m_AudioAsset = AudioAsset::Load(file_path);
  }
  else
  {
    m_MusicAsset = MusicAsset::Load(file_path);
  }
  

  m_PlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay, nullptr, m_PlayButton));
  m_PlayButton->setMinimumHeight(75);
  m_PlayButton->setMaximumHeight(100);
  connect(m_PlayButton, &QPushButton::clicked, this, &AudioViewer::play);

  m_StopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop, nullptr, m_StopButton));
  m_StopButton->setMinimumHeight(75);
  m_StopButton->setMaximumHeight(100);
  connect(m_StopButton, &QPushButton::clicked, this, &AudioViewer::stop);

  m_PauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause, nullptr, m_PauseButton));
  m_PauseButton->setMinimumHeight(75);
  m_PauseButton->setMaximumHeight(100);
  connect(m_PauseButton, &QPushButton::clicked, this, &AudioViewer::pause);

  m_VolumeSlider->setRange(0, 100);
  m_VolumeSlider->setValue(100);
  connect(m_VolumeSlider, &QSlider::valueChanged, this, &AudioViewer::changeVolume);

  m_PanSlider->setRange(0, 100);
  m_PanSlider->setValue(50);
  connect(m_PanSlider, &QSlider::valueChanged, this, &AudioViewer::changePan);

  QVBoxLayout * vlayout = new QVBoxLayout;
  QGroupBox * button_group_box = new QGroupBox;
  QGroupBox * slider_group_box = new QGroupBox;
  QHBoxLayout * button_layout = new QHBoxLayout;
  QHBoxLayout * slider_layout = new QHBoxLayout;
  QGroupBox * fill_group = new QGroupBox;


  button_layout->addWidget(m_PlayButton);
  button_layout->addWidget(m_StopButton);
  button_layout->addWidget(m_PauseButton);
  button_group_box->setLayout(button_layout);

  QGroupBox * volume_group = new QGroupBox("Volume");
  volume_group->setMaximumSize(200, 500);
  QHBoxLayout * volume_layout = new QHBoxLayout();
  volume_layout->addWidget(m_VolumeSlider);
  volume_group->setLayout(volume_layout);

  QGroupBox * pan_group = new QGroupBox("Pan");
  pan_group->setMaximumSize(200, 500);
  QHBoxLayout * pan_layout = new QHBoxLayout();
  pan_layout->addWidget(m_PanSlider);
  pan_group->setLayout(pan_layout);

  slider_layout->addWidget(volume_group);
  slider_layout->addWidget(pan_group);
  slider_group_box->setLayout(slider_layout);

  vlayout->addWidget(button_group_box, 0);
  vlayout->addWidget(slider_group_box, 0);
  vlayout->addWidget(fill_group, 0);

  setLayout(vlayout);
}

AudioViewer::~AudioViewer()
{
}

void AudioViewer::play(bool)
{
  float volume = m_VolumeSlider->value() / 100.0f;
  float pan = m_PanSlider->value() / 100.0f - 0.5f;

  if (m_IsAudio)
  {
    if (m_AudioAsset.Resolve()->IsLoaded())
    {
      m_AudioHandle = g_AudioManager.PlayAudio(m_AudioAsset, VolumeCategory::kSoundEffects, volume, pan);
    }
  }
  else
  {
    if (m_MusicAsset.Resolve()->IsLoaded())
    {
      m_MusicHandle = g_AudioManager.PlayMusic(m_MusicAsset, VolumeCategory::kMusic, volume, pan);
    }
  }

  m_IsPaused = false;
}

void AudioViewer::stop(bool)
{
  if (m_IsAudio)
  {
    g_AudioManager.StopAudio(*m_AudioHandle);
  }
  else
  {
    g_AudioManager.StopMusic(*m_MusicHandle);
  }
}

void AudioViewer::pause(bool)
{
  m_IsPaused = !m_IsPaused;
  if (m_IsAudio)
  {
    g_AudioManager.SetAudioPaused(*m_AudioHandle, m_IsPaused);
  }
  else
  {
    g_AudioManager.SetMusicPaused(*m_MusicHandle, m_IsPaused);
  }
}

void AudioViewer::changeVolume(int vol_val)
{
  float volume = vol_val / 100.0f;
  if (m_IsAudio)
  {
    g_AudioManager.SetAudioVolume(*m_AudioHandle, volume);
  }
  else
  {
    g_AudioManager.SetMusicVolume(*m_MusicHandle, volume);
  }
}

void AudioViewer::changePan(int pan_val)
{
  float pan = pan_val / 100.0f - 50.0f;
  if (m_IsAudio)
  {
    g_AudioManager.SetAudioPan(*m_AudioHandle, pan);
  }
  else
  {
    g_AudioManager.SetMusicPan(*m_MusicHandle, pan);
  }
}