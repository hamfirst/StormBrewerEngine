#pragma once

enum class RenderingBlendMode
{
  kAlpha,
  kAdditive,
};

void BootstrapContext();

class RenderState
{
public:
  void InitRenderState(int screen_width, int screen_height);

  void EnableBlendMode(RenderingBlendMode mode = RenderingBlendMode::kAlpha);
  void DisableBlendMode();

  int GetScreenWidth();
  int GetScreenHeight();

  Vector2 GetScreenSize();
  void SetScreenSize(Vector2 screen_size);

  RenderVec2 GetRenderScreenSize();

private:
  int m_ScreenWidth = 1;
  int m_ScreenHeight = 1;

  bool m_BlendEnabled = false;
  RenderingBlendMode m_BlendMode = RenderingBlendMode::kAlpha;
};


