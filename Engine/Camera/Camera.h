#pragma once

#include "Foundation/Common.h"

class RuntimeState;
class RenderState;
class RenderUtil;

class Camera
{
public:
  Camera(const RenderVec2 & resolution, const RenderVec2 & initial_position = {});

  void SetResolution(const RenderVec2 & resolution);
  void SetPosition(const RenderVec2 & position);

  const RenderVec2 & GetResolution();
  const RenderVec2 & GetPosition();

  void Draw(NotNullPtr<RuntimeState> runtime_state, RenderState & render_state);
  void DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Color & color);
  void DebugDraw(RenderState & render_state, RenderUtil & render_util, const Box & box, const Vector2 & offset, const Color & color);

  void DebugDrawCollision(NotNullPtr<RuntimeState> runtime_state, std::size_t collision_layer, RenderState & render_state, RenderUtil & render_util, const Color & color);

private:
  RenderVec2 m_Resolution;
  RenderVec2 m_Position;
};
