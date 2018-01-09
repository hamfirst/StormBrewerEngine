#pragma once

#include "Engine/EngineCommon.h"

class ENGINE_EXPORT RenderTarget
{
public:
  RenderTarget();
  RenderTarget(const RenderTarget & rhs) = delete;
  RenderTarget(RenderTarget && rhs) noexcept;
  ~RenderTarget();

  RenderTarget & operator = (RenderTarget & rhs) = delete;
  RenderTarget & operator = (RenderTarget && rhs) noexcept;

  void Move(RenderTarget && rhs) noexcept;
  void Destroy();

  void CreateRenderTarget(int width, int height, bool hdr, int depth_size = 0, int stencil_size = 0);
  int GetLoadError() const { return m_LoadError; }

  void SetLinearFilter();
  void SetPixelPerfectFilter();

  int GetWidth() const { return m_Width; }
  int GetHeight() const { return m_Height; }

protected:

  void BindAsRenderTarget() const;
  void BindAsTexture(int texture_stage) const;

private:

  friend class RenderState;

  unsigned int m_FrameBufferName;
  unsigned int m_TextureName;
  unsigned int m_DepthBufferName;
  unsigned int m_LoadError;

  unsigned int m_Width;
  unsigned int m_Height;
  bool m_Hdr;
  bool m_LinearFilter;
  int m_DepthSize;
  int m_StencilSize;
};
