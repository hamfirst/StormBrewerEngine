#pragma once

#include "Foundation/Optional/Optional.h"
#include "Foundation/BasicTypes/BasicTypes.refl.h"


inline Vector2 SelectVectorXY(const Vector2 & v1, const Vector2 & v2, uint32_t mask)
{
  return Vector2( (mask & 0b01) ? v1.x : v2.x, (mask & 0b10) ? v1.y : v2.y );
}

inline Vector2 MaxVectorXY(const Vector2 & v1, const Vector2 & v2)
{
  return Vector2(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}

inline Vector2 MinVectorXY(const Vector2 & v1, const Vector2 & v2)
{
  return Vector2(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}

inline RenderVec2 SelectVectorXY(const RenderVec2 & v1, const RenderVec2 & v2, uint32_t mask)
{
  return RenderVec2{ (mask & 0b01) ? v1.x : v2.x, (mask & 0b10) ? v1.y : v2.y };
}

inline RenderVec2 MaxVectorXY(const RenderVec2 & v1, const RenderVec2 & v2)
{
  return RenderVec2{ std::max(v1.x, v2.x), std::max(v1.y, v2.y) };
}

inline RenderVec2 MinVectorXY(const RenderVec2 & v1, const RenderVec2 & v2)
{
  return RenderVec2{ std::min(v1.x, v2.x), std::min(v1.y, v2.y) };
}

inline int DotVector2(const Vector2 & a, const Vector2 & b)
{
  return a.x * b.x + a.y + b.y;
}

inline bool BoxIntersect(const Box & b1, const Box & b2)
{
  return !(
    (b1.m_Start.x > b2.m_End.x) |
    (b1.m_Start.y > b2.m_End.y) |
    (b1.m_End.x < b2.m_Start.x) |
    (b1.m_End.y < b2.m_Start.y));
}

inline bool PointInBox(const Box & b, const Vector2 & p)
{
  return !(
    (b.m_Start.x > p.x) |
    (b.m_Start.y > p.y) |
    (b.m_End.x < p.x) |
    (b.m_End.y < p.y));
}

inline Optional<Box> ClipBox(const Box & box, const Box & bounds)
{
  if (!BoxIntersect(box, bounds))
  {
    return Optional<Box>();
  }

  Box result;
  result.m_Start = MaxVectorXY(box.m_Start, bounds.m_Start);
  result.m_End = MinVectorXY(box.m_End, bounds.m_End);
  return result;
}

inline Box MakeBoxFromStartAndSize(const Vector2 & start, const Vector2 & size)
{
  return Box{ start, start + size };
}

inline void BoxUnionInPlace(Box & a, const Box & b)
{
  a.m_Start.x = std::min(a.m_Start.x, b.m_Start.x);
  a.m_Start.y = std::min(a.m_Start.y, b.m_Start.y);
  a.m_End.x = std::max(a.m_End.x, b.m_End.x);
  a.m_End.y = std::max(a.m_End.y, b.m_End.y);
}

inline Box BoxUnion(const Box & a, const Box & b)
{
  Box r = a;
  BoxUnionInPlace(r, b);
  return r;
}

inline Color LerpColor(const Color & a, const Color & b, float val)
{
  auto one_minus_v = 1.0f - val;
  return Color(
    a.r * one_minus_v + b.r * val,
    a.g * one_minus_v + b.g * val,
    a.b * one_minus_v + b.b * val,
    a.a * one_minus_v + b.a * val);
}
