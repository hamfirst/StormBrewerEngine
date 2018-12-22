
#pragma once

#include "Foundation/Optional/Optional.h"
#include "Foundation/Script/ScriptClassRef.h"

#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

class UIManager;
class UIClickable;
class UITextInput;

class RenderState;
class RenderUtil;

class UIScriptInterface
{
public:

  UIScriptInterface(NotNullPtr<UIManager> ui_manager);

  void BeginRendering(NotNullPtr<RenderState> render_state, NullOptPtr<RenderUtil> render_util);
  void EndRendering();
  void SetActiveArea(const Box & active_area, bool clip);
  void ToggleFullscreen();

  void RenderTexture(int texture_id, int x, int y);
  void RenderTextureTint(int texture_id, int x, int y, float r, float g, float b, float a);
  void RenderTextureScale(int texture_id, int x, int y, float scale_x, float scale_y);
  void RenderTextureScaleTint(int texture_id, int x, int y, float scale_x, float scale_y, float r, float g, float b, float a);
  std::pair<int, int> GetTextureSize(int texture_id);

  void PlayAudio(int audio_id);
  void PlayAudioVolumePan(int audio_id, float volume, float pan);
  float GetAudioVolume();
  void SetAudioVolume(float volume);

  void PlayMusic(int music_id);
  void PlayMusicVolume(int music_id, float volume);
  void FadeToMusic(int music_id, float fade_out_time, float fade_in_time);
  void FadeToMusicVolume(int music_id, float volume, float fade_out_time, float fade_in_time);
  void FadeOutMusic(float fade_out_time);
  void StopMusic();
  float GetMusicVolume();
  void SetMusicVolume(float volume);

  void DrawText(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a, int mode);
  void DrawCenteredText(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a, int mode);
  void DrawTextScaled(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a, int mode, float scale);
  void DrawCenteredTextScaled(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a, int mode, float scale);
  std::pair<int, int> MeasureText(int font_id, const std::string & text);
  std::pair<int, int> MeasureTextScaled(int font_id, const std::string & text, float scale);

  void DrawTextInput(int font_id, ScriptClassRef<UITextInput> & text, int x, int y, float r, float g, float b, float a, int mode);
  void DrawCenteredTextInput(int font_id, ScriptClassRef<UITextInput> & text, int x, int y, float r, float g, float b, float a, int mode);
  void DrawTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, int x, int y, float r, float g, float b, float a, int mode, float scale);
  void DrawCenteredTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, int x, int y, float r, float g, float b, float a, int mode, float scale);
  std::pair<int, int> MeasureTextInput(int font_id, ScriptClassRef<UITextInput> & text);
  std::pair<int, int> MeasureTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, float scale);

  void DrawLine(int sx, int sy, int ex, int ey, float r, float g, float b, float a);
  void DrawLineThickness(int sx, int sy, int ex, int ey, float r, float g, float b, float a, float thickness);
  void DrawRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a);
  void DrawFilledRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a);
  void DrawEllipse(int sx, int sy, int width, int height, float r, float g, float b, float a, int segs);
  void DrawFilledEllipse(int sx, int sy, int width, int height, float r, float g, float b, float a, int segs);

  void FlushGeometry();
private:

  void RenderTextureInternal(int texture_id, int x, int y, float r, float g, float b, float a, float scale_x, float scale_y);
  void PlayAudioInternal(int audio_id, float volume, float pan);
  void PlayMusicInternal(int music_id, float volume, float fade_out_time, float fade_in_time);
  void DrawTextInternal(int font_id, czstr text, int x, int y, float r, float g, float b, float a, float scale, int mode);
  std::pair<int, int> MeasureTextInternal(int font_id, const std::string & text, float scale);
  void DrawTextInternal(int font_id, ScriptClassRef<UITextInput> & text, int x, int y, float r, float g, float b, float a, float scale, int mode);
  std::pair<int, int> MeasureTextInternal(int font_id, ScriptClassRef<UITextInput> & text, float scale);

private:

  NotNullPtr<UIManager> m_UIManager;
  NullOptPtr<RenderState> m_RenderState = nullptr;
  NullOptPtr<RenderUtil> m_RenderUtil = nullptr;
  Box m_ActiveArea;
  bool m_Clip;

  Optional<GeometryVertexBufferBuilder> m_GeometryBuffer;
};
