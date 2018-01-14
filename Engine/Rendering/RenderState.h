#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/RenderSettings.h"
#include "Engine/Rendering/VertexAttrib.h"
#include "Engine/Rendering/RenderTarget.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/ShaderProgram.h"

enum class RenderingBlendMode
{
  kAlpha,
  kAdditive,
};

void BootstrapContext();

class ShaderProgram;
class VertexBuffer;
class VertexArray;
class Texture;
class TextureAsset;
class Window;

class ENGINE_EXPORT RenderState
{
public:
  void InitRenderState(int screen_width, int screen_height);

  void BeginFrame(const Window & window);
  void FinalizeFrame(const Window & window);

  void BindShader(const ShaderProgram & shader);
  void BindVertexBuffer(VertexBuffer & buffer);
  void BindTexture(const Texture & texture, int texture_slot = 0);
  void BindTexture(const TextureAsset & texture, int texture_slot = 0);
  void BindRenderTarget(const RenderTarget & rt);
  void BindRenderTargetTexture(const RenderTarget & rt, int texture_slot = 0, int color_buffer_index = 0);
  void BindDefaultRenderTarget(const Window & window);
  void Draw(int index_start = 0, int index_end = -1) const;

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

#ifdef USE_RENDER_TARGET
  void BindBuiltInRenderTarget(int render_target_index);
  void BindBuiltInRenderTargetTexture(int render_target_index, int texture_stage);

  void BindBuiltInHalfResRenderTarget(int render_target_index);
  void BindBuiltInHalfResRenderTargetTexture(int render_target_index, int texture_stage);

  void Transfer(ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target = nullptr);
  void TransferHalfRes(ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target = nullptr);
  void TransferToDefault(const Window & window, ShaderProgram & shader, NullOptPtr<RenderTarget> source_render_target = nullptr);
#endif

private:
  int m_ScreenWidth = 1;
  int m_ScreenHeight = 1;

  int m_RenderWidth = 1;
  int m_RenderHeight = 1;

  bool m_BlendEnabled = false;
  bool m_ScissorEnabled = false;
  RenderingBlendMode m_BlendMode = RenderingBlendMode::kAlpha;

  float m_FramePct = 0;

  NullOptPtr<const ShaderProgram> m_BoundShader = nullptr;
  int m_BoundShaderName = 0;

  NullOptPtr<const VertexBuffer> m_BoundVertexBuffer = nullptr;
  int m_BoundVertexBufferName = 0;

  NullOptPtr<const Texture> m_BoundTexture = nullptr;
  int m_BoundTextureName = 0;

  NullOptPtr<const RenderTarget> m_BoundRenderTarget = nullptr;
  int m_BoundRenderTargetName = 0;

#ifdef USE_RENDER_TARGET
  RenderTarget m_RenderTarget[2];
  RenderTarget m_HalfRenderTarget[2];
  VertexBuffer m_TransferVertexBuffer;
  ShaderProgram m_DefaultTransferShader;
  ShaderProgram m_BlurTransferShader;
#endif

#ifndef USE_VERTEX_ARRAY
  friend class VertexArray;
  bool m_VertexAttribEnabled[kMaxVertexAttribs] = {};
#endif
};


