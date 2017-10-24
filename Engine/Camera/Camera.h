#pragma once

#include "Foundation/Common.h"

class GameContainer;
class EngineState;
class RenderState;
class RenderUtil;
class ShaderProgram;

class Camera
{
public:
  Camera(const Vector2 & game_resolution = {}, const Vector2 & screen_resolution = {}, const RenderVec2 & initial_position = {});

  void SetGameResolution(const RenderVec2 & resolution);
  void SetScreenResolution(const RenderVec2 & resolution);
  void SetPosition(const RenderVec2 & position);

  void BootstrapShader(const ShaderProgram & shader);

  const RenderVec2 & GetGameResolution() const;
  const RenderVec2 & GetScreenResolution() const;
  const RenderVec2 & GetPosition() const;

  RenderVec2 TransformFromScreenSpaceToClipSpace(const RenderVec2 & pos);
  RenderVec2 TransformFromScreenSpaceToWorldSpace(const RenderVec2 & pos);
  RenderVec2 TransformFromClipSpaceToWorldSpace(const RenderVec2 & pos);

  void Draw(GameContainer & game_container, NotNullPtr<EngineState> engine_state, RenderState & render_state, RenderUtil & render_util);
  void DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Color & color);
  void DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Vector2 & offset, const Color & color);

private:
  RenderVec2 m_ScreenResolution;
  RenderVec2 m_GameResolution;
  RenderVec2 m_Position;
};
