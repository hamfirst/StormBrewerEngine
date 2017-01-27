#pragma once

#include "Engine\EngineCommon.h"

enum class VertexBufferType
{
  kPoints,
  kLines,
  kTriangles,
  kInvalid,
};

struct VertexInfo
{
  RenderVec2 m_Position;
  RenderVec2 m_TexCoord;
  RenderVec4 m_Color;
};

