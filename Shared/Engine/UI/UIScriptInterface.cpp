
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIScriptInterface.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/UI/UIClickable.refl.h"
#include "Engine/UI/UITextInput.refl.h"
#include "Engine/UI/UIScriptLoader.h"
#include "Engine/UI/UITextureBinding.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Text/TextWrap.h"
#include "Engine/Audio/AudioManager.h"
#include "Engine/Audio/MusicManager.h"
#include "Engine/Sprite/SpriteEngineData.h"
#include "Engine/Window/Window.h"
#include "Engine/Atlas/AtlasEngineData.h"

#include "Runtime/Animation/AnimationState.h"



UIScriptInterface::UIScriptInterface(NotNullPtr<UIManager> ui_manager) :
  m_UIManager(ui_manager)
{

}

void UIScriptInterface::BeginRendering(NotNullPtr<RenderState> render_state)
{
  m_RenderState = render_state;
}

void UIScriptInterface::EndRendering()
{
  m_RenderState = nullptr;
}

void UIScriptInterface::SetDrawArea(const Box & draw_area, const Box & active_area, bool clip)
{
  m_DrawArea = draw_area;
  m_ActiveArea = active_area;
  m_Clip = clip;
}

void UIScriptInterface::ToggleFullscreen()
{
  auto & window = m_UIManager->m_ContainerWindow;
  window.SetFullscreen(!window.IsFullScreen());
}

std::tuple<int, int, bool> UIScriptInterface::GetMousePos()
{
  auto & window = m_UIManager->m_ContainerWindow;
  auto input_state = window.GetInputState();

  auto pointer_state = input_state->GetPointerState();

  return std::make_tuple(pointer_state.m_Pos.x, pointer_state.m_Pos.y, pointer_state.m_InFocus);
}

void UIScriptInterface::DrawTexture(int texture_id, int x, int y)
{
  DrawTextureInternal(texture_id, x, y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}

void UIScriptInterface::DrawTextureTint(int texture_id, int x, int y, float r, float g, float b, float a)
{
  DrawTextureInternal(texture_id, x, y, r, g, b, a, 1.0f, 1.0f);
}

void UIScriptInterface::DrawTextureScale(int texture_id, int x, int y, float scale_x, float scale_y)
{
  DrawTextureInternal(texture_id, x, y, 1.0f, 1.0f, 1.0f, 1.0f, scale_x, scale_y);
}

void UIScriptInterface::DrawTextureScaleTint(int texture_id, int x, int y, float scale_x, float scale_y, float r, float g, float b, float a)
{
  DrawTextureInternal(texture_id, x, y, r, g, b, a, scale_x, scale_y);
}

std::pair<int, int> UIScriptInterface::GetTextureSize(int texture_id)
{
  if((texture_id & UIScriptLoader::kIdMask) != UIScriptLoader::kTextureId &&
     (texture_id & UIScriptLoader::kIdMask) != UIScriptLoader::kBoundTexture)
  {
    return std::make_pair(0, 0);
  }

  const Texture * texture = nullptr;
  if((texture_id & UIScriptLoader::kIdMask) == UIScriptLoader::kTextureId)
  {
    auto & texture_ref = m_UIManager->m_ScriptLoader->m_TextureAssets[texture_id & UIScriptLoader::kIndexMask];
    auto texture_asset = texture_ref.Resolve();

    if(texture_asset != nullptr && texture_asset->IsLoaded())
    {
      texture = &texture_asset->GetTexture();
    }
  }
  else
  {
    auto itr = m_UIManager->m_Textures.find(texture_id & UIScriptLoader::kIndexMask);
    if(itr != m_UIManager->m_Textures.end())
    {
      texture = itr->second->m_TextureFetch();
    }
  }

  if(texture == nullptr)
  {
    return std::make_pair(0, 0);
  }

  auto size = texture->GetSize();
  return std::make_pair(size.x, size.y);
}

void UIScriptInterface::PlayAudio(int audio_id)
{
  PlayAudioInternal(audio_id, 1.0f, 0.0f);
}

void UIScriptInterface::PlayAudioVolumePan(int audio_id, float volume, float pan)
{
  PlayAudioInternal(audio_id, volume, pan);
}

float UIScriptInterface::GetAudioVolume()
{
  return g_AudioManager.GetVolumeForCategory(VolumeCategory::kSoundEffects);
}

void UIScriptInterface::SetAudioVolume(float volume)
{
  g_AudioManager.SetVolumeCategory(VolumeCategory::kSoundEffects, volume);
  g_AudioManager.SetVolumeCategory(VolumeCategory::kUI, volume);
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

float UIScriptInterface::GetMusicVolume()
{
  return g_AudioManager.GetVolumeForCategory(VolumeCategory::kMusic);
}

void UIScriptInterface::SetMusicVolume(float volume)
{
  g_AudioManager.SetVolumeCategory(VolumeCategory::kMusic, volume);
}

void UIScriptInterface::DrawText(int font_id, const std::string & text, float x, float y, float r, float g, float b, float a, int mode)
{
  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, 1.0f, mode);
}

void UIScriptInterface::DrawCenteredText(int font_id, const std::string & text, float x, float y, float r, float g, float b, float a, int mode)
{
  auto text_size = MeasureTextInternal(font_id, text, 1.0f);
  x -= text_size.first / 2;
  y -= text_size.second / 2;

  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, 1.0f, mode);
}

void UIScriptInterface::DrawTextScaled(int font_id, const std::string & text, float x, float y, float r, float g, float b, float a, int mode, float scale)
{
  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, scale, mode);
}

void UIScriptInterface::DrawCenteredTextScaled(int font_id, const std::string & text, float x, float y, float r, float g, float b, float a, int mode, float scale)
{
  auto text_size = MeasureTextInternal(font_id, text, scale);
  x -= text_size.first / 2;
  y -= text_size.second / 2;

  DrawTextInternal(font_id, text.c_str(), x, y, r, g, b, a, scale, mode);
}

std::pair<int, int> UIScriptInterface::MeasureText(int font_id, const std::string & text)
{
  return MeasureTextInternal(font_id, text, 1.0f);
}

std::pair<int, int> UIScriptInterface::MeasureTextScaled(int font_id, const std::string & text, float scale)
{
  return MeasureTextInternal(font_id, text, scale);
}

void UIScriptInterface::DrawTextInput(int font_id, ScriptClassRef<UITextInput> & text, float x, float y, float r, float g, float b, float a, int mode)
{
  DrawTextInternal(font_id, text, x, y, r, g, b, a, 1.0f, mode);
}

void UIScriptInterface::DrawCenteredTextInput(int font_id, ScriptClassRef<UITextInput> & text, float x, float y, float r, float g, float b, float a, int mode)
{
  auto text_size = MeasureTextInternal(font_id, text, 1.0f);
  x -= text_size.first / 2;
  y -= text_size.second / 2;

  DrawTextInternal(font_id, text, x, y, r, g, b, a, 1.0f, mode);
}

void UIScriptInterface::DrawTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, float x, float y, float r, float g, float b, float a, int mode, float scale)
{
  DrawTextInternal(font_id, text, x, y, r, g, b, a, scale, mode);
}

void UIScriptInterface::DrawCenteredTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, float x, float y, float r, float g, float b, float a, int mode, float scale)
{
  auto text_size = MeasureTextInternal(font_id, text, scale);
  x -= text_size.first / 2;
  y -= text_size.second / 2;

  DrawTextInternal(font_id, text, x, y, r, g, b, a, scale, mode);
}

std::pair<int, int> UIScriptInterface::MeasureTextInput(int font_id, ScriptClassRef<UITextInput> & text)
{
  return MeasureTextInternal(font_id, text, 1.0f);
}

std::pair<int, int> UIScriptInterface::MeasureTextInputScaled(int font_id, ScriptClassRef<UITextInput> & text, float scale)
{
  return MeasureTextInternal(font_id, text, scale);
}

float UIScriptInterface::GetLineHeight(int font_id)
{
  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return 0;
  }

  return g_TextManager.GetLineHeight(font_id & UIScriptLoader::kIndexMask, 1.0);
}

std::pair<std::string, int> UIScriptInterface::WrapText(int font_id, const std::string & text, int width)
{
  return WrapTextInternal(font_id, text, width, 1.0f);
}

std::pair<std::string, int> UIScriptInterface::WrapTextScaled(int font_id, const std::string & text, int width, float scale)
{
  return WrapTextInternal(font_id, text, width, scale);
}

void UIScriptInterface::ClearCurrentTextInput()
{
  m_UIManager->m_ContainerWindow.ClearAllTextInputContext();
}

void UIScriptInterface::DrawSprite(int sprite_id, int x, int y, bool flip_x, bool flip_y, int anim_index, int anim_frame, float alpha)
{
  if((sprite_id & UIScriptLoader::kIdMask) != UIScriptLoader::kSpriteId)
  {
    return;
  }

  auto & sprite = m_UIManager->m_ScriptLoader->m_SpriteAssets[sprite_id & UIScriptLoader::kIndexMask];
  auto engine_data = sprite->GetEngineData<SpriteEngineData>();

  if(engine_data == nullptr)
  {
    return;
  }

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->EnableBlendMode();
  m_RenderState->BindShader(shader);

  RenderVec4 screen_bounds;
  if(m_Clip)
  {
    screen_bounds = m_RenderState->ComputeScreenBounds(m_ActiveArea);
  }
  else
  {
    screen_bounds = RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f };
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState->GetFullRenderDimensions());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  engine_data->RenderSprite(sprite, *m_RenderState, anim_index, anim_frame, 0,
          RenderVec2{ m_DrawArea.m_Start } + Vector2f{x, y}, { 1, 0, 0, 1 }, Color(1.0f, 1.0f, 1.0f, alpha), shader);
}

int UIScriptInterface::GetAnimationIndex(int sprite_id, const std::string & animation_name)
{
  if((sprite_id & UIScriptLoader::kIdMask) != UIScriptLoader::kSpriteId)
  {
    return -1;
  }

  auto & sprite = m_UIManager->m_ScriptLoader->m_SpriteAssets[sprite_id & UIScriptLoader::kIndexMask];
  return sprite->GetAnimationIndex(crc32(animation_name));
}

std::tuple<int, int> UIScriptInterface::GetSpriteSize(int sprite_id, int anim_index, int anim_frame)
{
  if((sprite_id & UIScriptLoader::kIdMask) != UIScriptLoader::kSpriteId)
  {
    return std::make_tuple(0, 0);
  }

  auto & sprite = m_UIManager->m_ScriptLoader->m_SpriteAssets[sprite_id & UIScriptLoader::kIndexMask];

  AnimationState state;
  sprite->SyncFrameData(anim_index, anim_frame, 0, state);
  return std::make_tuple(state.m_FrameWidth, state.m_FrameHeight);
}

void UIScriptInterface::DrawAtlas(int atlas_id, std::string & elem_name, int x, int y, int width, int height)
{
  if((atlas_id & UIScriptLoader::kIdMask) != UIScriptLoader::kAtlasId)
  {
    return;
  }

  auto & atlas = m_UIManager->m_ScriptLoader->m_AtlasAssets[atlas_id & UIScriptLoader::kIndexMask];
  auto engine_data = atlas->GetEngineData<AtlasEngineData>();

  if(engine_data == nullptr)
  {
    return;
  }

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->BindShader(shader);

  engine_data->SetupRender(*m_RenderState, elem_name.c_str(), Box::FromStartAndWidthHeight(x, y, width, height), Color(1.0f, 1.0f, 1.0f, 1.0f));

  RenderVec4 screen_bounds;
  if(m_Clip)
  {
    screen_bounds = m_RenderState->ComputeScreenBounds(m_ActiveArea);
  }
  else
  {
    screen_bounds = RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f };
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState->GetFullRenderDimensions());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_DrawArea.m_Start });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  m_RenderState->Draw();
}

std::tuple<int, int, int> UIScriptInterface::FrameAdvance(int sprite_id, std::string & anim_name, int anim_index, int anim_frame, int anim_delay, bool loop)
{
  if((sprite_id & UIScriptLoader::kIdMask) != UIScriptLoader::kSpriteId)
  {
    return {};
  }

  auto & sprite = m_UIManager->m_ScriptLoader->m_SpriteAssets[sprite_id & UIScriptLoader::kIndexMask];

  AnimationState anim_state;
  anim_state.m_AnimIndex = anim_index;
  anim_state.m_AnimFrame = anim_frame;
  anim_state.m_AnimDelay = anim_delay;

  sprite->FrameAdvance(crc32(anim_name), anim_state, loop);
  return std::make_tuple(anim_state.m_AnimIndex, anim_state.m_AnimFrame, anim_state.m_AnimDelay);
}

void UIScriptInterface::DrawTextureInternal(int texture_id, int x, int y, float r, float g, float b, float a, float scale_x, float scale_y)
{
  if(m_RenderState == nullptr)
  {
    return;
  }

  if((texture_id & UIScriptLoader::kIdMask) != UIScriptLoader::kTextureId &&
     (texture_id & UIScriptLoader::kIdMask) != UIScriptLoader::kBoundTexture)
  {
    return;
  }

  const Texture * texture = nullptr;
  if((texture_id & UIScriptLoader::kIdMask) == UIScriptLoader::kTextureId)
  {
    auto & texture_ref = m_UIManager->m_ScriptLoader->m_TextureAssets[texture_id & UIScriptLoader::kIndexMask];
    auto texture_asset = texture_ref.Resolve();

    if(texture_asset != nullptr && texture_asset->IsLoaded())
    {
      texture = &texture_asset->GetTexture();
    }
  }
  else
  {
    auto itr = m_UIManager->m_Textures.find(texture_id & UIScriptLoader::kIndexMask);
    if(itr != m_UIManager->m_Textures.end())
    {
      texture = itr->second->m_TextureFetch();
    }
  }

  QuadVertexBufferBuilder buffer_builder;

  int size_x = (int)roundf(texture->GetWidth() * scale_x);
  int size_y = (int)roundf(texture->GetHeight() * scale_y);

  QuadVertexBuilderInfo quad;
  quad.m_Position = Box::FromStartAndWidthHeight(Vector2(x, y), Vector2(size_x, size_y));
  quad.m_Color = Color(r, g, b, a);
  quad.m_TexCoords = Box::FromPoints(Vector2{}, texture->GetSize());
  quad.m_TextureSize = texture->GetSize();
  buffer_builder.AddQuad(quad);

  auto & vertex_buffer = m_RenderState->GetScratchBuffer();
  buffer_builder.FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->BindShader(shader);

  RenderVec4 screen_bounds;
  if(m_Clip)
  {
    screen_bounds = m_RenderState->ComputeScreenBounds(m_ActiveArea);
  }
  else
  {
    screen_bounds = RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f };
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState->GetFullRenderDimensions());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_DrawArea.m_Start });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0, 0, 0, 1.0 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

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

  m_GeometryBuffer->Line(Vector2f(sx, sy), Vector2f(ex, ey), 1.0f, Color(r, g, b, a), 0.5f);
}

void UIScriptInterface::DrawLineThickness(int sx, int sy, int ex, int ey, float r, float g, float b, float a, float thickness)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  auto offset = Vector2f(0.5f, 0.5f);
  m_GeometryBuffer->Line(Vector2f(sx, sy) + offset, Vector2f(ex, ey) + offset, thickness, Color(r, g, b, a), 0.5f);
}

void UIScriptInterface::DrawRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->Rectangle(Box::FromStartAndWidthHeight(sx, sy, width, height), 1.0f, Color(r, g, b, a), 0.5f);
}

void UIScriptInterface::DrawFilledRectangle(int sx, int sy, int width, int height, float r, float g, float b, float a)
{
  if(!m_GeometryBuffer)
  {
    m_GeometryBuffer.Emplace();
  }

  m_GeometryBuffer->FilledRectangle(Box::FromStartAndWidthHeight(sx, sy, width, height), Color(r, g, b, a), 0.5f);
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

  m_GeometryBuffer->Ellipse(center, size.x * 0.5f, size.y * 0.5f, 1.0f, Color(r, g, b, a), segs, 0.5f);
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

  m_GeometryBuffer->FilledEllipse(center, size.x * 0.5f, size.y * 0.5f, Color(r, g, b, a), segs, 0.5f);
}

void UIScriptInterface::FlushGeometry()
{
  if(!m_GeometryBuffer)
  {
    return;
  }

  auto & vertex_buffer = m_RenderState->GetScratchBuffer();
  m_GeometryBuffer->FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultScreenSpaceShader();
  m_RenderState->BindShader(shader);

  RenderVec4 screen_bounds;
  if(m_Clip)
  {
    screen_bounds = m_RenderState->ComputeScreenBounds(m_ActiveArea);
  }
  else
  {
    screen_bounds = RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f };
  }

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), m_RenderState->GetFullRenderDimensions());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ m_DrawArea.m_Start });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), screen_bounds);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  m_RenderState->BindTexture(m_RenderState->GetDefaultTexture());
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

void UIScriptInterface::DrawTextInternal(int font_id, czstr text, float x, float y, float r, float g, float b, float a, float scale, int mode)
{
  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return;
  }

  g_TextManager.SetTextPos(Vector2(x, y) + m_DrawArea.m_Start);
  g_TextManager.SetPrimaryColor(Color(r, g, b, a));
  g_TextManager.SetTextMode(static_cast<TextRenderMode>(mode));

  if(m_Clip)
  {
    g_TextManager.SetTextBounds(m_ActiveArea);
  }
  else
  {
    g_TextManager.ClearTextBounds();
  }

  g_TextManager.RenderText(text, font_id & UIScriptLoader::kIndexMask, scale, *m_RenderState);
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

void UIScriptInterface::DrawTextInternal(int font_id, ScriptClassRef<UITextInput> & text, float x, float y, float r, float g, float b, float a, float scale, int mode)
{
  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return;
  }

  g_TextManager.SetTextPos(Vector2(x, y) + m_DrawArea.m_Start);
  g_TextManager.SetPrimaryColor(Color(r, g, b, a));
  g_TextManager.SetTextMode(static_cast<TextRenderMode>(mode));
  g_TextManager.SetTextBounds(m_ActiveArea);
  g_TextManager.RenderInputText(text->m_TextInput, font_id & UIScriptLoader::kIndexMask, scale, *m_RenderState, "");
}

std::pair<int, int> UIScriptInterface::MeasureTextInternal(int font_id, ScriptClassRef<UITextInput> & text, float scale)
{
  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return std::make_pair(0, 0);
  }

  auto box = g_TextManager.GetTextSize(text->m_TextInput, font_id & UIScriptLoader::kIndexMask, scale);
  auto size = box.m_End;

  return std::make_pair(size.x, size.y);
}

std::pair<std::string, int> UIScriptInterface::WrapTextInternal(int font_id, const std::string & text, int width, float scale)
{
  std::string out;

  if((font_id & UIScriptLoader::kIdMask) != UIScriptLoader::kFontId)
  {
    return std::make_pair(out, 0);
  }

  auto visitor = [&](const std::string_view & str)
  {
    if(!out.empty())
    {
      out += '\n';
    }

    out += str;
  };

  auto height = VisitTextWrapPoints(visitor, text, font_id & UIScriptLoader::kIndexMask, scale, width);
  return std::make_pair(std::move(out), height);
}
