
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetBundle.h"

#include "ProjectSettings/ProjectColors.h"


#include <gl3w/gl3w.h>

static const char * kQuadVertexShader = SHADER_LITERAL(

  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform vec2 u_ScreenSize;
  uniform vec2 u_StartPos;
  uniform vec2 u_EndPos;

  void main()
  {
    vec2 position = mix(u_StartPos, u_EndPos, a_Position);
    position /= u_ScreenSize;
    position *= 2.0;

    gl_Position = vec4(position, 0, 1);
    v_TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
    v_Color = a_Color;
  }
);

static const char * kQuadFragmentShader = SHADER_LITERAL(
  uniform vec4 u_Color;

  void main()
  {
    gl_FragColor = u_Color;
  }
);

static const char * kQuadTextureFragmentShader = SHADER_LITERAL(

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform vec4 u_Color;

  void main()
  {
    vec4 color = texture2D(u_Texture, v_TexCoord);
    gl_FragColor = color * u_Color;
  }
);

RenderUtil::RenderUtil() :
  m_QuadVertexBuffer(false),
  m_ScratchVertexBuffer(true)
{

}

void RenderUtil::LoadShaders()
{
  Shader vert_shader;
  vert_shader.LoadShader(kQuadVertexShader, ShaderType::kVertexShader);

  Shader quad_shader;
  quad_shader.LoadShader(kQuadFragmentShader, ShaderType::kFragmentShader);

  Shader quad_texture_shader;
  quad_texture_shader.LoadShader(kQuadTextureFragmentShader, ShaderType::kFragmentShader);

  m_QuadShader.CreateProgram(vert_shader, quad_shader);
  m_QuadTextureShader.CreateProgram(vert_shader, quad_texture_shader);

  QuadVertexBufferBuilder builder;
  QuadVertexBuilderInfo quad;
  quad.m_Position.m_Start = Vector2(0, 0);
  quad.m_Position.m_End = Vector2(1, 1);
  quad.m_TexCoords.m_Start = Vector2(0, 0);
  quad.m_TexCoords.m_End = Vector2(1, 1);
  quad.m_TextureSize = Vector2(1, 1);
  quad.m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);

  builder.AddQuad(quad);
  builder.FillVertexBuffer(m_QuadVertexBuffer);

  uint32_t default_pixel = 0xFFFFFFFF;
  PixelBuffer default_pixel_buffer((uint8_t *)&default_pixel, 1, 1);
  m_DefaultTexture.SetTextureData(default_pixel_buffer, TextureType::kRGBA);
}

void RenderUtil::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::Clear(const Color & color)
{
  SetClearColor(color);
  Clear();
}

void RenderUtil::SetDefaultClearColor()
{
  glClearColor(PROJECT_CLEAR_COLOR);
}

void RenderUtil::SetClearColor(const Color & color)
{
  auto c = (RenderVec4)color;
  glClearColor(c.r, c.g, c.b, c.a);
}

void RenderUtil::CleanupShaders()
{
  m_QuadVertexBuffer.Destroy();

  m_QuadShader.Destroy();
  m_QuadTextureShader.Destroy();
}

void RenderUtil::DrawQuad(const Box & box, const Color & color, const RenderVec2 & screen_size, RenderState & render_state)
{
  render_state.BindShader(m_QuadShader);
  render_state.BindVertexBuffer(m_QuadVertexBuffer);

  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), screen_size);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), (RenderVec2)box.m_Start);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), (RenderVec2)(box.m_End + Vector2(1, 1)));
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);

  render_state.Draw();
}

void RenderUtil::DrawTexturedQuad(const Box & box, const Color & color, const Texture & texture, const RenderVec2 & screen_size, RenderState & render_state)
{
  render_state.BindShader(m_QuadTextureShader);
  render_state.BindVertexBuffer(m_QuadVertexBuffer);
  render_state.BindTexture(texture);

  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), screen_size);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), (RenderVec2)box.m_Start);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), (RenderVec2)box.m_End);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  
  render_state.Draw();
}

void RenderUtil::DrawTexturedQuad(const Vector2 & start, const Color & color, const Texture & texture, const RenderVec2 & screen_size, RenderState & render_state)
{
  render_state.BindShader(m_QuadTextureShader);
  render_state.BindVertexBuffer(m_QuadVertexBuffer);
  render_state.BindTexture(texture);

  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), screen_size);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), (RenderVec2)start);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), (RenderVec2)(start + texture.GetSize()));
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);
  m_QuadTextureShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  render_state.Draw();
}

const Texture & RenderUtil::GetDefaultTexture() const
{
  return m_DefaultTexture;
}

VertexBuffer & RenderUtil::GetScratchBuffer()
{
  return m_ScratchVertexBuffer;
}

void DrawAssetBundleTexture(Any & load_data, Vector2 pos, RenderState & render_state, RenderUtil & render_util)
{
  auto load_link = load_data.Get<TextureAsset::LoadCallbackLink>();
  if (load_link == nullptr)
  {
    return;
  }

  auto texture = load_link->Get();
  if (texture == nullptr || texture->IsLoaded() == false)
  {
    return;
  }

  render_util.DrawTexturedQuad(pos, Color(255, 255, 255, 255), texture->GetTexture(), render_state.GetScreenSize(), render_state);
}

NullOptPtr<TextureAsset> GetAssetBundleTexture(Any & load_data)
{
  auto load_link = load_data.Get<TextureAsset::LoadCallbackLink>();
  if (load_link == nullptr)
  {
    return nullptr;
  }

  auto texture = load_link->Get();
  if (texture == nullptr || texture->IsLoaded() == false)
  {
    return nullptr;
  }

  return texture;
}
