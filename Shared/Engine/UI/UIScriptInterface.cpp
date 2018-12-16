
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIScriptInterface.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "UIScriptLoader.h"


UIScriptInterface::UIScriptInterface(NotNullPtr<UIManager> ui_manager) :
  m_UIManager(ui_manager)
{

}

void UIScriptInterface::BeginRendering(NotNullPtr<RenderState> render_state, NullOptPtr<RenderUtil> render_util)
{
  m_RenderState = render_state;
  m_RenderUtil = render_util;
}

void UIScriptInterface::EndRendering()
{
  m_RenderState = nullptr;
  m_RenderUtil = nullptr;
}

void UIScriptInterface::SetActiveArea(const Box & active_area)
{
  m_ActiveArea = active_area;
}

void UIScriptInterface::RenderTexture(int texture_id, int x, int y)
{
  RenderTextureInternal(texture_id, x, y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void UIScriptInterface::RenderTextureTint(int texture_id, int x, int y, float r, float g, float b, float a)
{
  RenderTextureInternal(texture_id, x, y, r, g, b, a, 1.0f, 1.0f);
}

void UIScriptInterface::RenderTextureScale(int texture_id, int x, int y, float scale_x, float scale_y)
{
  RenderTextureInternal(texture_id, x, y, 1.0f, 1.0f, 1.0f, 1.0f, scale_x, scale_y);
}

void UIScriptInterface::RenderTextureScaleTint(int texture_id, int x, int y, float scale_x, float scale_y, float r, float g, float b, float a)
{
  RenderTextureInternal(texture_id, x, y, r, g, b, a, scale_x, scale_y);
}

void UIScriptInterface::PlayAudio(int audio_id)
{
  PlayAudioInternal(audio_id, 1.0f, 1.0f);
}

void UIScriptInterface::PlayAudioVolumePan(int audio_id, float volume, float pan)
{
  PlayAudioInternal(audio_id, volume, pan);
}

void UIScriptInterface::PlayMusic(int music_id)
{
  PlayMusicInternal(music_id, 1.0f, 0.0f, 0.0f);
}

void UIScriptInterface::PlayMusicVolume(int music_id, float volume)
{
  PlayMusicInternal(music_id, volume, 0.0f, 0.0f);
}

void UIScriptInterface::FadeToMusic(int music_id, float fade_out_time, float fade_in_time)
{
  PlayMusicInternal(music_id, 1.0f, fade_out_time, fade_in_time);
}

void UIScriptInterface::FadeToMusicVolume(int music_id, float volume, float fade_out_time, float fade_in_time)
{
  PlayMusicInternal(music_id, volume, fade_out_time, fade_in_time);
}

void UIScriptInterface::FadeOutMusic(float fade_out_time)
{
  g_MusicManager.FadeOut(fade_out_time);
}

void UIScriptInterface::StopMusic()
{
  g_MusicManager.StopAll();
}

void UIScriptInterface::DrawText(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a)
{
  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, 1.0f);
}

void UIScriptInterface::DrawTextScaled(int font_id, const std::string & text, int x, int y, float r, float g, float b, float a, float scale)
{
  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, scale);
}

std::pair<int, int> UIScriptInterface::MeasureText(int font_id, const std::string & text)
{
  return MeasureTextInternal(font_id, text, 1.0f);
}

std::pair<int, int> UIScriptInterface::MeasureTextScaled(int font_id, const std::string & text, float scale)
{
  return MeasureTextInternal(font_id, text, scale);
}

void UIScriptInterface::RenderTextureInternal(int texture_id, int x, int y, float r, float g, float b, float a, float scale_x, float scale_y)
{
  if(m_RenderState == nullptr)
  {
    return;
  }

  if((texture_id & UIScriptLoader::kIdMask) != UIScriptLoader::kTextureId)
  {
    return;
  }

  auto & texture_ref = m_UIManager->m_ScriptLoader->m_TextureAssets[texture_id & UIScriptLoader::kIndexMask];
  auto texture = texture_ref.Resolve();
  if(texture == nullptr || texture->IsLoaded() == false)
  {
    return;
  }

  QuadVertexBufferBuilder buffer_builder;

  QuadVertexBuilderInfo quad;
  quad.m_Position = Box::FromFrameCenterAndSize(Vector2(x, y), texture->GetSize());
  quad.m_Color = Color(r, g, b, a);
  quad.m_TexCoords = Box::FromPoints(Vector2{}, texture->GetSize());
  quad.m_TextureSize = texture->GetSize();
  buffer_builder.AddQuad(quad);

  auto & vertex_buffer = m_RenderUtil->GetScratchBuffer();
  buffer_builder.FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->BindShader(shader);

  RenderVec4 screen_bounds;
  screen_bounds.x = (float)m_ActiveArea.m_Start.x / (float)m_RenderState->GetRenderWidth();
  screen_bounds.y = (float)m_ActiveArea.m_Start.y / (float)m_RenderState->GetRenderHeight();
  screen_bounds.w = (float)m_ActiveArea.m_End.x / (float)m_RenderState->GetRenderWidth();
  screen_bounds.z = (float)m_ActiveArea.m_End.y / (float)m_RenderState->GetRenderHeight();

  screen_bounds -= RenderVec4{ 0.5f, 0.5f, 0.5f, 0.5f };
  screen_bounds *= 2.0f;

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_ActiveArea.m_Start });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ scale_x, 0, 0, scale_y });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);

  m_RenderState->BindTexture(*texture);
  m_RenderState->BindVertexBuffer(vertex_buffer);
  m_RenderState->Draw();
}


void UIScriptInterface::DrawLine(int sx, int sy, int ex, int ey, float r, float g, float b, float a)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->Line(Vector2f(sx, sy), Vector2f(ex, ey), 1.0f, Color(r, g, b, a));
}

void UIScriptInterface::DrawLineThickness(int sx, int sy, int ex, int ey, float r, float g, float b, float a, float thickness)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->Line(Vector2f(sx, sy), Vector2f(ex, ey), thickness, Color(r, g, b, a));
}

void UIScriptInterface::DrawRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->Rectangle(Box::FromStartAndWidthHeight(sx, sy, width, height), 1.0f, Color(r, g, b, a));
}

void UIScriptInterface::DrawFilledRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->FilledRectangle(Box::FromStartAndWidthHeight(sx, sy, width, height), Color(r, g, b, a));
}

void UIScriptInterface::DrawEllipse(int sx, int sy, int width, int height, float r, float g, float b, float a, int segs)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  auto box = Box::FromStartAndWidthHeight(sx, sy, width, height);
  auto size = Vector2f(box.Size());
  auto start = Vector2f(box.m_Start);
  auto end = Vector2f(box.m_End);
  auto center = (start + end) * 0.5f;

  m_GeometryBuffer->Ellipse(center, size.x * 0.5f, size.y * 0.5f, 1.0f, Color(r, g, b, a), segs);
}

void UIScriptInterface::DrawFilledEllipse(int sx, int sy, int width, int height, float r, float g, float b, float a, int segs)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  auto box = Box::FromStartAndWidthHeight(sx, sy, width, height);
  auto size = Vector2f(box.Size());
  auto start = Vector2f(box.m_Start);
  auto end = Vector2f(box.m_End);
  auto center = (start + end) * 0.5f;

  m_GeometryBuffer->FilledEllipse(center, size.x * 0.5f, size.y * 0.5f, Color(r, g, b, a), segs);
}

void UIScriptInterface::FlushGeometry()
{
  if(!m_GeometryBuffer)
  {
    return;
  }

  auto & vertex_buffer = m_RenderUtil->GetScratchBuffer();
  m_GeometryBuffer->FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->BindShader(shader);

  RenderVec4 screen_bounds;
  screen_bounds.x = (float)m_ActiveArea.m_Start.x / (float)m_RenderState->GetRenderWidth();
  screen_bounds.y = (float)m_ActiveArea.m_Start.y / (float)m_RenderState->GetRenderHeight();
  screen_bounds.w = (float)m_ActiveArea.m_End.x / (float)m_RenderState->GetRenderWidth();
  screen_bounds.z = (float)m_ActiveArea.m_End.y / (float)m_RenderState->GetRenderHeight();

  screen_bounds -= RenderVec4{ 0.5f, 0.5f, 0.5f, 0.5f };
  screen_bounds *= 2.0f;

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_ActiveArea.m_Start });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);

  m_RenderState->BindTexture(m_RenderUtil->GetDefaultTexture());
  m_RenderState->BindVertexBuffer(vertex_buffer);
  m_RenderState->Draw();

  m_GeometryBuffer.Clear();
}

void UIScriptInterface::PlayAudioInternal(int audio_id, float volume, float pan)
{
  if((audio_id & UIScriptLoader::kIdMask) != UIScriptLoader::kAudioId)
  {
    return;
  }

  auto & audio_ref = m_UIManager->m_ScriptLoader->m_AudioAssets[audio_id & UIScriptLoader::kIndexMask];
  auto audio = audio_ref.Resolve();
  if(audio == nullptr || audio->IsLoaded() == false)
  {
    return;
  }

  g_AudioManager.PlayAudio(audio_ref, VolumeCategory::kUI, volume, pan, false);
}

void UIScriptInterface::PlayMusicInternal(int music_id, float volume, float fade_out_time, float fade_in_time)
{
  if((music_id & UIScriptLoader::kIdMask) != UIScriptLoader::kAudioId)
  {
    return;
  }

  auto & music_ref = m_UIManager->m_ScriptLoader->m_MusicAssets[music_id & UIScriptLoader::kIndexMask];
  auto music = music_ref.Resolve();
  if(music == nullptr || music->IsLoaded() == false)
  {
    return;
  }

  if(fade_in_time == 0.0f && fade_out_time == 0.0f)
  {
    g_MusicManager.CutTo(music, volume);
  }
  else
  {
    g_MusicManager.FadeTo(music, volume, fade_out_time, fade_in_time);
  }
}

void UIScriptInterface::DrawTextInternal(int font_id, czstr text, int x, int y, float r, float g, float b, float a, float scale)
{
  g_TextManager.RenderText(text, font_id, scale, *m_RenderState);
}

std::pair<int, int> UIScriptInterface::MeasureTextInternal(int font_id, const std::string & text, float scale)
{
  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return std::make_pair(0, 0);
  }

  auto box = g_TextManager.GetTextSize(text, font_id & UIScriptLoader::kIndexMask, scale);
  auto size = box.m_End;

  return std::make_pair(size.x, size.y);
}
