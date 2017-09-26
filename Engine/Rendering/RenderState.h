#pragma once

#include "Engine/EngineCommon.h"

enum class RenderingBlendMode
{
  kAlpha,
  kAdditive,
};

void BootstrapContext();

class ENGINE_EXPORT RenderState
{
public:
  void InitRenderState(int screen_width, int screen_height);

  void SetFramePct(float frame_pct);
  float GetFramePct() const;

  void EnableBlendMode(RenderingBlendMode mode = RenderingBlendMode::kAlpha);
  void DisableBlendMode();
  void SyncBlendMode();

  void EnableScissorRect(const Box & box);
  void DisableScissorRect();

  int GetScreenWidth();
  int GetScreenHeight();

  Vector2 GetScreenSize();
  void SetScreenSize(Vector2 screen_size);

  int GetRenderWidth();
  int GetRenderHeight();

  Vector2 GetRenderSize();
  void SetRenderSize(Vector2 render_size);

  RenderVec2 ScreenPixelsToRenderPixels(const RenderVec2 & screen_pixels);
  RenderVec2 RenderPixelsToScreenPixels(const RenderVec2 & render_pixels);

private:
  int m_ScreenWidth = 1;
  int m_ScreenHeight = 1;

  int m_RenderWidth = 1;
  int m_RenderHeight = 1;

  bool m_BlendEnabled = false;
  bool m_ScissorEnabled = false;
  RenderingBlendMode m_BlendMode = RenderingBlendMode::kAlpha;

  float m_FramePct = 0;
};


