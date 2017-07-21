
#include "Engine/EngineCommon.h"

#include "RenderState.h"
#include "RenderErrorMacros.h"

#include <gl3w/gl3w.h>

void BootstrapContext()
{
  glPixelStorei(GL_PACK_ALIGNMENT, 1); CHECK_GL_RENDER_ERROR;
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); CHECK_GL_RENDER_ERROR;
}

void RenderState::InitRenderState(int screen_width, int screen_height)
{
  glDisable(GL_BLEND); CHECK_GL_RENDER_ERROR;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECK_GL_RENDER_ERROR;
  glBlendEquation(GL_FUNC_ADD); CHECK_GL_RENDER_ERROR;

  BootstrapContext();

  m_BlendEnabled = false;
  m_BlendMode = RenderingBlendMode::kAlpha;

  m_ScreenWidth = screen_width;
  m_ScreenHeight = screen_height;
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
  m_ScreenWidth = screen_size.x;
  m_ScreenHeight = screen_size.y;
}

int RenderState::GetRenderWidth()
{
  return m_RenderWidth;
}

int RenderState::GetRenderHeight()
{
  return m_RenderHeight;
}

Vector2 RenderState::GetRenderSize()
{
  return Vector2(m_RenderWidth, m_RenderHeight);
}

void RenderState::SetRenderSize(Vector2 render_size)
{
  m_RenderWidth = render_size.x;
  m_RenderHeight = render_size.y;
}

RenderVec2 RenderState::ScreenPixelsToRenderPixels(const RenderVec2 & screen_pixels)
{
  auto half_screen = RenderVec2{ m_ScreenWidth, m_ScreenHeight } * 0.5f;
  auto half_render = RenderVec2{ m_RenderWidth, m_RenderHeight } * 0.5f;
  auto clip_space = (screen_pixels - half_screen) / half_screen;
  return (clip_space * half_render) + half_render;
}

RenderVec2 RenderState::RenderPixelsToScreenPixels(const RenderVec2 & render_pixels)
{
  auto half_screen = RenderVec2{ m_ScreenWidth, m_ScreenHeight } *0.5f;
  auto half_render = RenderVec2{ m_RenderWidth, m_RenderHeight } *0.5f;
  auto clip_space = (render_pixels - half_render) / half_render;
  return (clip_space * half_screen) + half_screen;
}
