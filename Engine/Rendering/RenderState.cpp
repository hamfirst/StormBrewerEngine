
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

RenderVec2 RenderState::GetRenderScreenSize()
{
  return RenderVec2{ m_ScreenWidth, m_ScreenHeight };
}
