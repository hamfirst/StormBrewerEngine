
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Rendering/ShaderLiteral.h"

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
    position -= vec2(0.5, 0.5);
    position *= 2.0;

    gl_Position = vec4(position, 0, 1);
    v_TexCoord = a_TexCoord;
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
  builder.FillVertexBuffer(m_VertexBuffer);

  m_QuadVertexArray.CreateDefaultBinding(m_QuadShader, m_VertexBuffer);
  m_QuadTextureVertexArray.CreateDefaultBinding(m_QuadTextureShader, m_VertexBuffer);
}

void RenderUtil::CleanupShaders()
{
  m_QuadVertexArray.Destroy();
  m_QuadTextureVertexArray.Destroy();

  m_VertexBuffer.Destroy();

  m_QuadShader.Destroy();
  m_QuadTextureShader.Destroy();
}

void RenderUtil::DrawQuad(const Box & box, const Color & color, RenderState & render_state, bool alpha_blend)
{
  m_QuadShader.Bind();
  m_QuadVertexArray.Bind();

  if (alpha_blend)
  {
    render_state.EnableBlendMode();
  }

  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_state.GetRenderScreenSize());
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), (RenderVec2)box.m_Start);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), (RenderVec2)box.m_End);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);

  m_VertexBuffer.Draw();

  if (alpha_blend)
  {
    render_state.DisableBlendMode();
  }

  m_QuadShader.Unbind();
  m_QuadVertexArray.Unbind();
}

void RenderUtil::DrawTexturedQuad(const Box & box, const Color & color, const Texture & texture, RenderState & render_state, bool alpha_blend)
{
  m_QuadTextureShader.Bind();
  m_QuadTextureVertexArray.Bind();

  texture.BindTexture(0);

  if (alpha_blend)
  {
    render_state.EnableBlendMode();
  }

  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_state.GetRenderScreenSize());
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_StartPos"), (RenderVec2)box.m_Start);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_EndPos"), (RenderVec2)box.m_End);
  m_QuadShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), color);

  m_VertexBuffer.Draw();

  if (alpha_blend)
  {
    render_state.DisableBlendMode();
  }

  m_QuadTextureShader.Unbind();
  m_QuadTextureVertexArray.Unbind();
}
