
#include "Foundation/Common.h"
#include "Foundation/BasicTypes/BasicTypes.refl.meta.h"

#include <StormData/StormDataJson.h>

Vector2::Vector2() :
  x(0), y(0)
{

}

Vector2::Vector2(int x, int y) :
  x(x), y(y)
{

}

Vector2::Vector2(const RenderVec2 & v) :
  x((int)v.x), y((int)v.y)
{

}

Box Box::FromFrameCenterAndSize(const Vector2 & frame_center, const Vector2 & frame_size)
{
  Box b;
  b.m_Start = frame_center - frame_size / 2;
  b.m_End = b.m_Start + frame_size - Vector2(1, 1);
  return b;
}

Box Box::FromPoint(const Vector2 & pos)
{
  return Box { pos, pos };
}

Box Box::FromPoints(const Vector2 & a, const Vector2 & b)
{
  Box box;
  box.m_Start = MinVectorXY(a, b);
  box.m_End = MaxVectorXY(a, b);
  return box;
}
