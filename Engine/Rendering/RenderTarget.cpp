
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderTarget.h"
#include "Engine/Rendering/RenderErrorMacros.h"

#include <gl3w/gl3w.h>

RenderTarget::RenderTarget()
{
  m_DepthBufferName = 0;
  m_FrameBufferName = 0;
  m_LoadError = 0;
  m_NumColorBuffers = 0;
  m_Width = 0;
  m_Height = 0;

  std::fill(&m_TextureName[0], &m_TextureName[kMaxColorBuffers], 0);
}

RenderTarget::RenderTarget(RenderTarget && rhs) noexcept
{
  Move(std::move(rhs));
}

RenderTarget::~RenderTarget()
{
  Destroy();
}

RenderTarget & RenderTarget::operator = (RenderTarget && rhs) noexcept
{
  Destroy();
  Move(std::move(rhs));
  return *this;
}

void RenderTarget::Move(RenderTarget && rhs) noexcept
{
  m_DepthBufferName = rhs.m_DepthBufferName;
  m_FrameBufferName = rhs.m_FrameBufferName;
  m_LoadError = rhs.m_LoadError;
  m_Width = rhs.m_Width;
  m_Height = rhs.m_Height;

  rhs.m_DepthBufferName = 0;
  rhs.m_FrameBufferName = 0;
  rhs.m_LoadError = 0;
  rhs.m_Width = 0;
  rhs.m_Height = 0;

  std::copy(&rhs.m_TextureName[0], &rhs.m_TextureName[kMaxColorBuffers], m_TextureName);
  std::fill(&rhs.m_TextureName[0], &rhs.m_TextureName[kMaxColorBuffers], 0);
}

void RenderTarget::Destroy()
{
  if (m_FrameBufferName != 0)
  {
    glDeleteFramebuffers(1, &m_FrameBufferName);
    m_FrameBufferName = 0;
  }

  if (m_NumColorBuffers != 0)
  {
    glDeleteTextures(m_NumColorBuffers, &m_TextureName[0]);
    std::fill(&m_TextureName[0], &m_TextureName[kMaxColorBuffers], 0);
  }
  
  if (m_DepthBufferName != 0)
  {
    glDeleteRenderbuffers(1, &m_DepthBufferName);
    m_DepthBufferName = 0;
  }

  m_LoadError = 0;
  m_Width = 0;
  m_Height = 0;
}


void RenderTarget::BindAsRenderTarget() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferName); CHECK_GL_RENDER_ERROR;
  glViewport(0, 0, m_Width, m_Height); CHECK_GL_RENDER_ERROR;
}

void RenderTarget::BindAsTexture(int texture_stage, int color_buffer_index) const
{
  glActiveTexture(GL_TEXTURE0 + texture_stage); CHECK_GL_RENDER_ERROR;
  glBindTexture(GL_TEXTURE_2D, m_TextureName[color_buffer_index]); CHECK_GL_RENDER_ERROR;
}

void RenderTarget::CreateRenderTarget(int width, int height, bool hdr, int depth_size, int stencil_size, int num_color_buffers)
{
  if (width == m_Width && height == m_Height && hdr == m_Hdr && depth_size == m_DepthSize && stencil_size == m_StencilSize)
  {
    return;
  }

  Destroy();

  glGenFramebuffers(1, &m_FrameBufferName); CHECK_GL_LOAD_ERROR;
  auto fb_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteFramebuffers(1, &m_FrameBufferName); m_FrameBufferName = 0; } });

  glGenTextures(num_color_buffers, &m_TextureName[0]); CHECK_GL_LOAD_ERROR;
  auto texture_destroy_on_error = gsl::finally([&] { 
    if (m_LoadError != 0) { glDeleteTextures(num_color_buffers, &m_TextureName[0]); std::fill(&m_TextureName[0], &m_TextureName[num_color_buffers], 0); } });

  for (int index = 0; index < num_color_buffers; ++index)
  {
    glBindTexture(GL_TEXTURE_2D, m_TextureName[index]); CHECK_GL_LOAD_ERROR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, hdr ? GL_FLOAT : GL_UNSIGNED_BYTE, nullptr); CHECK_GL_LOAD_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferName);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, m_TextureName[index], 0); CHECK_GL_LOAD_ERROR;
  }

  if (depth_size > 0 || stencil_size > 0)
  {
    GLenum depth_mode;
    switch (depth_size)
    {
    case 0:
      if (stencil_size != 8)
      {
        m_LoadError = GL_INVALID_VALUE;
        return;
      }

      depth_mode = GL_STENCIL_INDEX8;
      break;
    case 16:
      if (stencil_size != 0)
      {
        m_LoadError = GL_INVALID_VALUE;
        return;
      }

      depth_mode = GL_DEPTH_COMPONENT16;
      break;
    case 24:
      switch (stencil_size)
      {
      case 0:
        depth_mode = GL_DEPTH_COMPONENT24;
        break;
      case 8:
        depth_mode = GL_DEPTH24_STENCIL8;
        break;
      default:
        m_LoadError = GL_INVALID_VALUE;
        return;
      }
      break;
    default:
      m_LoadError = GL_INVALID_VALUE;
      return;
    }

    glGenRenderbuffers(1, &m_DepthBufferName); CHECK_GL_LOAD_ERROR;
    auto db_destroy_on_error = gsl::finally([&] { if (m_LoadError != 0) { glDeleteRenderbuffers(1, &m_DepthBufferName); m_DepthBufferName = 0; } });

    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferName); CHECK_GL_LOAD_ERROR;
    glRenderbufferStorage(GL_RENDERBUFFER, depth_mode, width, height); CHECK_GL_LOAD_ERROR;

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferName); CHECK_GL_LOAD_ERROR;
  }

  ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Invalid render target state");
  glBindFramebuffer(GL_FRAMEBUFFER, 0); CHECK_GL_LOAD_ERROR;

  m_Width = width;
  m_Height = height;

  m_Hdr = hdr;
  m_LinearFilter = false;
  m_DepthSize = depth_size;
  m_StencilSize = stencil_size;
}

void RenderTarget::SetLinearFilter()
{
  if (m_LinearFilter == false)
  {
    for (int index = 0; index < m_NumColorBuffers; ++index)
    {
      glBindTexture(GL_TEXTURE_2D, m_TextureName[index]); CHECK_GL_RENDER_ERROR;
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECK_GL_RENDER_ERROR;
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CHECK_GL_RENDER_ERROR;
      m_LinearFilter = true;
    }
  }
}

void RenderTarget::SetPixelPerfectFilter()
{
  if (m_LinearFilter == true)
  {
    for (int index = 0; index < m_NumColorBuffers; ++index)
    {
      glBindTexture(GL_TEXTURE_2D, m_TextureName[index]); CHECK_GL_RENDER_ERROR;
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); CHECK_GL_RENDER_ERROR;
      m_LinearFilter = false;
    }
  }
}