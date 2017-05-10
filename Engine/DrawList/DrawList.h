#pragma once

#include <map>

#include "Engine/EngineCommon.h"

class DrawList
{
public:
  DrawList();
  ~DrawList();

  DrawList(const DrawList & rhs) = delete;
  DrawList(DrawList && rhs) = delete;

  DrawList & operator = (const DrawList & rhs) = delete;
  DrawList & operator = (DrawList && rhs) = delete;
 
  void Clear();

  void PushDraw(int layer_order, Delegate<void, const Box &, const RenderVec2 &> && cb);
  void Draw(const Box & viewport_bounds, const RenderVec2 & screen_center);

private:

  std::map<int, std::vector<Delegate<void, const Box &, const RenderVec2 &>>> m_DrawCallbacks;
};

