
#pragma once

class UIManager;
class RenderState;
class RenderUtil;

class UIScriptInterface
{
public:

  UIScriptInterface(NotNullPtr<UIManager> ui_manager);

  void BeginRendering(NotNullPtr<RenderState> render_state, NullOptPtr<RenderUtil> render_util);
  void EndRendering();
  void SetActiveArea(const Box & active_area);

  void RenderTexture(int texture_id, int x, int y);
  void RenderTextureTint(int texture_id, int x, int y, float r, float g, float b, float a);
  void RenderTextureScale(int texture_id, int x, int y, float scale_x, float scale_y);
  void RenderTextureScaleTint(int texture_id, int x, int y, float scale_x, float scale_y, float r, float g, float b, float a);

  void PlayAudio(int audio_id);
  void PlayAudioVolumePan(int audio_id, float volume, float pan);

  void PlayMusic(int music_id);
  void PlayMusicVolume(int music_id, float volume);
  void FadeToMusic(int music_id, float fade_out_time, float fade_in_time);
  void FadeToMusicVolume(int music_id, float volume, float fade_out_time, float fade_in_time);
  void FadeOutMusic(float fade_out_time);
  void StopMusic();

  void DrawText(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a);
private:

  void RenderTextureInternal(int texture_id, int x, int y, float r, float g, float b, float a, float scale_x, float scale_y);
  void PlayAudioInternal(int audio_id, float volume, float pan);
  void PlayMusicInternal(int music_id, float volume, float fade_out_time, float fade_in_time);
  void DrawTextInternal(int font_id, czstr text, int x, int y, float r, float g, float b, float a, float scale);

private:

  NotNullPtr<UIManager> m_UIManager;
  NullOptPtr<RenderState> m_RenderState = nullptr;
  NullOptPtr<RenderUtil> m_RenderUtil = nullptr;
  Box m_ActiveArea;
};
