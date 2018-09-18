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
  int m_LowerEdge = 0;
};

struct EntityRenderState : public AnimationState
{
  RenderVec4 m_Matrix = RenderVec4(1.0f, 0.0f, 0.0f, 1.0f);
  Color m_Color = Color(1.0f, 1.0f, 1.0f, 1.0f);
  uint32_t m_SkinNameHash = 0;
  bool m_Draw = true;
};
