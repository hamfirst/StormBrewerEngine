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

  void EnableBlendMode(RenderingBlendMode mode = RenderingBlendMode::kAlpha);
  void DisableBlendMode();
  void SyncBlendMode();

  void EnableScissorRect(const Box & box);
  void DisableScissorRect();

  int GetScreenWidth();
  int GetScreenHeight();

  Vector2 GetScreenSize();
  void SetScreenSize(Vector2 screen_size);

  RenderVec2 GetRenderScreenSize();

private:
  int m_ScreenWidth = 1;
  int m_ScreenHeight = 1;

  bool m_BlendEnabled = false;
  bool m_ScissorEnabled = false;
  RenderingBlendMode m_BlendMode = RenderingBlendMode::kAlpha;
};


