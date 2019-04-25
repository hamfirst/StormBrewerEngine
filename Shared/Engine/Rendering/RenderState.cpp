
#include "Engine/EngineCommon.h"

#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderErrorMacros.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Rendering/ShaderLiteral.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/Rendering.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Text/TextManager.h"
#include "Engine/Window/Window.h"
#include "Engine/Shader/ShaderManager.h"

#include "ProjectSettings/ProjectColors.h"

#include <gl3w/gl3w.h>


static const char * kDefaultTransferVertexShader = SHADER_LITERAL(
  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  void main()
  {
    gl_Position = vec4(a_Position, 0, 1);
    v_TexCoord = a_TexCoord;
    v_TexCoord.y = 1.0 - v_TexCoord.y;

    v_Color = a_Color;
  }
);

static const char * kDefaultTransferFragmentShader = SHADER_LITERAL(

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform vec4 u_Color;

  void main()
  {
    vec4 color = texture2D(u_Texture, v_TexCoord) * v_Color * u_Color;
    gl_FragColor = color;
  }
);

static const char * kBlurFragmentShader = SHADER_LITERAL(

  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform float u_Resolution;
  uniform float u_Radius;
  uniform vec2 u_Direction;

  void main() 
  {
    vec4 sum = vec4(0.0);

    vec2 tc = v_TexCoord;

    float blur = u_Radius / u_Resolution;

    float hstep = u_Direction.x;
    float vstep = u_Direction.y;

    sum += texture2D(u_Texture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
    sum += texture2D(u_Texture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(u_Texture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(u_Texture, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;

    sum += texture2D(u_Texture, vec2(tc.x, tc.y)) * 0.2270270270;

    sum += texture2D(u_Texture, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;
    sum += texture2D(u_Texture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
    sum += texture2D(u_Texture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
    sum += texture2D(u_Texture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;

    gl_FragColor = v_Color * vec4(sum.rgb, 1.0);
  }
);


void BootstrapContext()
{
  glPixelStorei(GL_PACK_ALIGNMENT, 1); CHECK_GL_RENDER_ERROR;
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); CHECK_GL_RENDER_ERROR;
  
  glDisable(GL_DEPTH_TEST); CHECK_GL_RENDER_ERROR;
  glDisable(GL_CULL_FACE); CHECK_GL_RENDER_ERROR;
}

RenderState::RenderState() : 
  m_ScratchVertexBuffer(true)
{

}

RenderState::~RenderState()
{
  Release();
}

void RenderState::InitRenderState(int screen_width, int screen_height)
{
  glEnable(GL_BLEND); CHECK_GL_RENDER_ERROR;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECK_GL_RENDER_ERROR;
  glBlendEquation(GL_FUNC_ADD); CHECK_GL_RENDER_ERROR;
  glViewport(0, 0, screen_width, screen_height);

  BootstrapContext();

  m_BlendEnabled = true;
  m_BlendMode = RenderingBlendMode::kNone;

  m_ScreenWidth = screen_width;
  m_ScreenHeight = screen_height;

#ifdef USE_RENDER_TARGET
  QuadVertexBuilderInfo quad;
  quad.m_Position = Box::FromPoints(Vector2(-1, -1), Vector2(1, 1));
  quad.m_TexCoords = Box::FromPoints(Vector2(0, 0), Vector2(1, 1));
  quad.m_TextureSize = Vector2(1, 1);
  quad.m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);

  QuadVertexBufferBuilder builder;
  builder.AddQuad(quad);
  m_TransferVertexBuffer = builder.CreateVertexBuffer();

  m_DefaultTransferShader = MakeQuickShaderProgram(kDefaultTransferVertexShader, kDefaultTransferFragmentShader);
  m_BlurTransferShader = MakeQuickShaderProgram(kDefaultTransferVertexShader, kBlurFragmentShader);
#endif

#ifdef REQUIRE_VERTEX_ARRAY_IN_CONTEXT
  glGenVertexArrays(1, &m_VertexArrayName); CHECK_GL_RENDER_ERROR;
#endif

  uint32_t default_pixel = 0xFFFFFFFF;
  PixelBuffer default_pixel_buffer((uint8_t *)&default_pixel, 1, 1);
  m_DefaultTexture.SetTextureData(default_pixel_buffer, TextureType::kRGBA);
}

void RenderState::MakeCurrent()
{
#ifdef REQUIRE_VERTEX_ARRAY_IN_CONTEXT
  glBindVertexArray(m_VertexArrayName); CHECK_GL_RENDER_ERROR;
#endif
}

void RenderState::ResetState()
{
  m_BlendEnabled = false;
  m_ScissorEnabled = false;
  m_BlendMode = RenderingBlendMode::kNone;

  m_BoundShader = nullptr;
  m_BoundShaderName = 0;

  m_BoundVertexBuffer = nullptr;
  m_BoundVertexBufferName = 0;

  m_BoundTexture = nullptr;
  m_BoundTextureName = 0;

  m_BoundRenderTarget = nullptr;
  m_BoundRenderTargetName = 0;

#ifndef USE_VERTEX_ARRAY
  for(int index = 0; index < kMaxVertexAttribs; ++index)
  {
    m_VertexAttribEnabled[index] = {};
  }
#endif
}

void RenderState::BeginFrame(const Window & window)
{
#ifdef USE_RENDER_TARGET

#ifdef USE_HDR
  bool hdr = true;
#else
  bool hdr = false;
#endif

  m_RenderTarget[0].CreateRenderTarget(m_RenderWidth, m_RenderHeight, hdr);
  m_RenderTarget[1].CreateRenderTarget(m_RenderWidth, m_RenderHeight, hdr);

  m_HalfRenderTarget[0].CreateRenderTarget(m_RenderWidth / 2, m_RenderHeight / 2, hdr);
  m_HalfRenderTarget[1].CreateRenderTarget(m_RenderWidth / 2, m_RenderHeight / 2, hdr);

  BindBuiltInRenderTarget(0);
#endif
}

void RenderState::FinalizeFrame(const Window & window)
{
#ifdef USE_RENDER_TARGET
  m_RenderTarget[0].SetPixelPerfectFilter();
  m_RenderTarget[1].SetPixelPerfectFilter();

  BindShader(m_DefaultTransferShader);
  m_DefaultTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(1.0f, 1.0f, 1.0f, 1.0f));
  TransferToDefault(window, m_DefaultTransferShader);

#ifdef USE_HDR

  m_RenderTarget[0].SetLinearFilter();
  m_RenderTarget[1].SetLinearFilter();

  BindShader(m_BlurTransferShader);
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Radius"), 2.5f);
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(1.0f, 0.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderWidth);
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  Transfer(m_BlurTransferShader, &m_RenderTarget[0]);

  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(0.0f, 1.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderHeight);
  Transfer(m_BlurTransferShader);

  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(1.0f, 0.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderWidth);
  Transfer(m_BlurTransferShader);

  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(0.0f, 1.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderHeight);
  Transfer(m_BlurTransferShader);

  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(1.0f, 0.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderWidth);
  Transfer(m_BlurTransferShader);

  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Direction"), Vector2f(0.0f, 1.0f));
  m_BlurTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Resolution"), (float)m_RenderHeight);
  Transfer(m_BlurTransferShader);

  BindShader(m_DefaultTransferShader);
  m_DefaultTransferShader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(1.0f, 1.0f, 1.0f, 0.5f));
  TransferToDefault(m_DefaultTransferShader);
#endif

#endif
}

void RenderState::Release()
{
#ifdef REQUIRE_VERTEX_ARRAY_IN_CONTEXT

  // Having this (for some reason) breaks QT
//   if(m_VertexArrayName != 0)
//   {
//     glDeleteVertexArrays(1, &m_VertexArrayName); CHECK_GL_RENDER_ERROR;
//     m_VertexArrayName = 0;
//   }
#endif
}

void RenderState::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderState::Clear(const Color & color)
{
  SetClearColor(color);
  Clear();
}

void RenderState::SetDefaultClearColor()
{
  glClearColor(PROJECT_CLEAR_COLOR);
}

void RenderState::SetClearColor(const Color & color)
{
  auto c = (RenderVec4)color;
  glClearColor(c.r, c.g, c.b, c.a);
}

void RenderState::BindShader(const ShaderProgram & shader)
{
  if (m_BoundShader != &shader || m_BoundShaderName != shader.m_ProgramName)
  {
    m_BoundShader = &shader;
    m_BoundShaderName = shader.m_ProgramName;
    shader.Bind();
  }
}

void RenderState::BindVertexBuffer(VertexBuffer & buffer)
{
  if (m_BoundVertexBuffer != &buffer || m_BoundVertexBufferName != buffer.m_VertexBufferName ||
      buffer.m_VertexArray.m_BoundShader != m_BoundShader || buffer.IsDirty())
  {
    m_BoundVertexBuffer = &buffer;
    m_BoundVertexBufferName = buffer.m_VertexBufferName;
    buffer.Sync(*this, *m_BoundShader);
  }
}

void RenderState::BindTexture(const Texture & texture, int texture_slot)
{
  //if (m_BoundTexture != &texture || m_BoundTextureName != texture.m_TextureName)
  {
    m_BoundTexture = &texture;
    m_BoundTextureName = texture.m_TextureName;
    texture.BindTexture(texture_slot);
  }
}

void RenderState::BindTexture(const TextureAsset & texture, int texture_slot)
{
  BindTexture(texture.GetTexture(), texture_slot);
}

void RenderState::BindRenderTarget(const RenderTarget & rt)
{
  if (m_BoundRenderTarget != &rt || m_BoundRenderTargetName != rt.m_FrameBufferName)
  {
    m_BoundRenderTarget = &rt;
    m_BoundRenderTargetName = rt.m_FrameBufferName;
    rt.BindAsRenderTarget();
  }
}

void RenderState::BindRenderTargetTexture(const RenderTarget & rt, int texture_slot, int color_buffer_index)
{
  //if (m_BoundTexture != nullptr || m_BoundTextureName != rt.m_TextureName)
  {
    m_BoundTexture = nullptr;
    m_BoundTextureName = rt.m_TextureName[color_buffer_index];
    rt.BindAsTexture(texture_slot, color_buffer_index);
  }
}

void RenderState::BindDefaultRenderTarget(const Window & window)
{
  if (m_BoundRenderTarget != nullptr || m_BoundRenderTargetName != 0)
  {
    m_BoundRenderTarget = nullptr;
    m_BoundRenderTargetName = 0;
    window.BindDefaultRenderTarget();
  }
}

void RenderState::Draw(int index_start, int index_end) const
{
  if(m_BoundVertexBuffer->IsEmpty() || index_start == index_end)
  {
    return;
  }

  ASSERT(m_BoundVertexBuffer->m_VertexArray.m_BoundShader == m_BoundShader, "Invalid shader binding");
  m_BoundVertexBuffer->Draw(index_start, index_end);
}

void RenderState::SetFramePct(float frame_pct)
{
  m_FramePct = frame_pct;
}

float RenderState::GetFramePct() const
{
  return m_FramePct;
}

void RenderState::EnableBlendMode(RenderingBlendMode mode)
{
  if (m_BlendEnabled == false)
  {
    glEnable(GL_BLEND); CHECK_GL_RENDER_ERROR;
    m_BlendEnabled = true;
  }

  if (m_BlendMode != mode)
  {
    switch (mode)
    {
    case RenderingBlendMode::kNone:
      break;
    case RenderingBlendMode::kAlpha:
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECK_GL_RENDER_ERROR;
      break;
    case RenderingBlendMode::kAdditive:
      glBlendFunc(GL_SRC_ALPHA, GL_ONE); CHECK_GL_RENDER_ERROR;
      break;
    }

    m_BlendMode = mode;
  }
}

void RenderState::SyncBlendMode()
{
  if (m_BlendEnabled == false)
  {
    glDisable(GL_BLEND); CHECK_GL_RENDER_ERROR;
  }
  else
  {
    glEnable(GL_BLEND); CHECK_GL_RENDER_ERROR;
  }
}

void RenderState::DisableBlendMode()
{
  if (m_BlendEnabled == true)
  {
    glDisable(GL_BLEND); CHECK_GL_RENDER_ERROR;
    m_BlendEnabled = false;
  }
}

void RenderState::EnableScissorRect(const Box & box)
{
  if (m_ScissorEnabled == false)
  {
    glEnable(GL_SCISSOR_TEST);
    m_ScissorEnabled = true;
  }

  glScissor(box.m_Start.x, box.m_Start.y, box.m_End.x - box.m_Start.x, box.m_End.y - box.m_Start.y);
}

void RenderState::DisableScissorRect()
{
  if (m_ScissorEnabled)
  {
    glDisable(GL_SCISSOR_TEST);
    m_ScissorEnabled = false;
  }
}

int RenderState::GetScreenWidth()
{
  return m_ScreenWidth;
}

int RenderState::GetScreenHeight()
{
  return m_ScreenHeight;
}

Vector2 RenderState::GetScreenSize()
{
  return Vector2(m_ScreenWidth, m_ScreenHeight);
}

void RenderState::SetScreenSize(Vector2 screen_size)
{
  if (screen_size.x != m_ScreenWidth || screen_size.y != m_ScreenHeight)
  {
    glViewport(0, 0, screen_size.x, screen_size.y);
    m_ScreenWidth = screen_size.x;
    m_ScreenHeight = screen_size.y;
  }
}

float RenderState::GetRenderWidth()
{
  return m_RenderWidth;
}

float RenderState::GetRenderHeight()
{
  return m_RenderHeight;
}

RenderVec2 RenderState::GetRenderSize()
{
  return RenderVec2(m_RenderWidth, m_RenderHeight);
}

RenderVec4 RenderState::GetFullRenderDimensions()
{
  return RenderVec4(m_RenderWidth, m_RenderHeight, m_ScreenWidth, m_ScreenHeight);
}

void RenderState::SetRenderSize(RenderVec2 render_size)
{
  m_RenderWidth = render_size.x;
  m_RenderHeight = render_size.y;
}

RenderVec2 RenderState::ScreenPixelsToRenderPixels(const RenderVec2 & screen_pixels)
{
  auto half_screen = RenderVec2{ m_ScreenWidth, m_ScreenHeight } * 0.5f;
  auto half_render = RenderVec2{ m_RenderWidth, m_RenderHeight } * 0.5f;
  auto clip_space = (screen_pixels - half_screen) / half_screen;
  return (clip_space * half_render);
}

RenderVec2 RenderState::RenderPixelsToScreenPixels(const RenderVec2 & render_pixels)
{
  auto half_screen = RenderVec2{ m_ScreenWidth, m_ScreenHeight } *0.5f;
  auto half_render = RenderVec2{ m_RenderWidth, m_RenderHeight } *0.5f;
  auto clip_space = (render_pixels) / half_render;
  return (clip_space * half_screen) + half_screen;
}

RenderVec4 RenderState::ComputeScreenBounds(const Optional<Box> & active_area)
{
  RenderVec4 screen_bounds;

  if(active_area)
  {
    auto & box = active_area.Value();
    auto screen = Box::FromFrameCenterAndSize({}, GetRenderSize());

    RenderVec2 screen_start = screen.m_Start;
    RenderVec2 screen_size = GetRenderSize();

    RenderVec2 box_start = box.m_Start;
    RenderVec2 box_end = box.m_End;

    auto offset_start = (box_start - screen_start) / screen_size;
    auto offset_end = (box_end - screen_start) / screen_size;

    auto coord_start = offset_start * 2.0f - RenderVec2{1, 1};
    auto coord_end = offset_end * 2.0f - RenderVec2{1, 1};

    screen_bounds.x = coord_start.x;
    screen_bounds.y = coord_start.y;
    screen_bounds.z = coord_end.x;
    screen_bounds.w = coord_end.y;
  }
  else
  {
    screen_bounds = { -1, -1, 1, 1 };
  }

  return screen_bounds;
}

const Texture & RenderState::GetDefaultTexture() const
{
  return m_DefaultTexture;
}

VertexBuffer & RenderState::GetScratchBuffer()
{
  return m_ScratchVertexBuffer;
}

void RenderState::DrawDebugQuad(const Box & b, const Color & c, bool screen_space)
{
  DrawDebugTexturedQuad(b, c, GetDefaultTexture(), screen_space);
}

void RenderState::DrawDebugTexturedQuad(const Box & b, const Color & c, const Texture & texture, bool screen_space)
{
  QuadVertexBufferBuilder builder;
  QuadVertexBuilderInfo quad;
  quad.m_Position = b;
  quad.m_TexCoords = Box::FromStartAndWidthHeight(Vector2(0, 0), Vector2(1, 1));
  quad.m_TextureSize = Vector2(1, 1);
  quad.m_Color = c;
  builder.AddQuad(quad);

  builder.FillVertexBuffer(m_ScratchVertexBuffer);

  auto & shader = screen_space ? g_ShaderManager.GetDefaultScreenSpaceShader() : g_ShaderManager.GetDefaultWorldSpaceShader();
  BindShader(shader);
  BindTexture(texture);
  BindVertexBuffer(m_ScratchVertexBuffer);

  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), GetFullRenderDimensions());
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), RenderVec2{ 0, 0 });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1.0f, 0, 0, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), RenderVec4{ 1.0f, 1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Bounds"), RenderVec4{ -1.0f, -1.0f, 1.0f, 1.0f });
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ColorMatrix"), Mat4f());

  Draw();
}

#ifdef USE_RENDER_TARGET

void RenderState::BindBuiltInRenderTarget(int render_target_index)
{
  BindRenderTarget(m_RenderTarget[render_target_index]);
}

void RenderState::BindBuiltInRenderTargetTexture(int render_target_index, int texture_stage)
{
  BindRenderTargetTexture(m_RenderTarget[render_target_index], texture_stage);
}

void RenderState::BindBuiltInHalfResRenderTarget(int render_target_index)
{
  BindRenderTarget(m_HalfRenderTarget[render_target_index]);
}

void RenderState::BindBuiltInHalfResRenderTargetTexture(int render_target_index, int texture_stage)
{
  BindRenderTargetTexture(m_HalfRenderTarget[render_target_index], texture_stage);
}

void RenderState::Transfer(ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target)
{
  auto prev_render_target = source_render_target ? source_render_target : m_BoundRenderTarget;
  if (prev_render_target == &m_RenderTarget[0])
  {
    BindRenderTarget(m_RenderTarget[1]);
  }
  else
  {
    BindRenderTarget(m_RenderTarget[0]);
  }

  BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  BindRenderTargetTexture(*prev_render_target, 0);
  BindVertexBuffer(m_TransferVertexBuffer);
  Draw();
}

void RenderState::TransferHalfRes(ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target)
{
  auto prev_render_target = source_render_target ? source_render_target : m_BoundRenderTarget;
  if (prev_render_target == &m_HalfRenderTarget[0])
  {
    BindRenderTarget(m_HalfRenderTarget[1]);
  }
  else
  {
    BindRenderTarget(m_HalfRenderTarget[0]);
  }

  BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  BindRenderTargetTexture(*prev_render_target, 0);
  BindVertexBuffer(m_TransferVertexBuffer);
  Draw();
}

void RenderState::TransferToDefault(const Window & window, ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target)
{
  auto prev_render_target = source_render_target ? source_render_target : m_BoundRenderTarget;
  BindDefaultRenderTarget(window);

  BindShader(shader);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  BindRenderTargetTexture(*prev_render_target, 0);
  BindVertexBuffer(m_TransferVertexBuffer);
  Draw();
}

#endif