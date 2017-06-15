#pragma once

#include "Foundation/Common.h"

class AnimationState
{
public:
  int m_AnimIndex = -1;
  int m_AnimFrame = 0;
  int m_AnimDelay = 0;
  int m_FrameWidth = 0;
  int m_FrameHeight = 0;
};

struct EntityRenderState : public AnimationState
{
  RenderVec4 m_Matrix = RenderVec4(1, 0, 0, 1);
  RenderVec4 m_Color = RenderVec4(1, 1, 1, 1);
  bool m_Draw = true;
};
