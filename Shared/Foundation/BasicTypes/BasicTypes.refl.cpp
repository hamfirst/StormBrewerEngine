
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

Vector2::Vector2(float x, float y) :
  x((int)x), y((int)y)
{

}

Vector2::Vector2(const RenderVec2 & v) :
  x((int)v.x), y((int)v.y)
{

}

Box Box::Offset(const Vector2 & offset) const
{
  Box b = *this;
  b.m_Start += offset;
  b.m_End += offset;
  return b;
}

Box Box::MirrorX() const
{
  return Box{ Vector2(-m_End.x, m_Start.y), Vector2(-m_Start.x, m_End.y) };
}

Box Box::FromFrameCenterAndSize(const Vector2 & frame_center, const Vector2 & frame_size)
{
  Box b;
  b.m_Start = frame_center - frame_size / 2;
  b.m_End = b.m_Start + frame_size - Vector2(1, 1);
  return b;
}

Box Box::FromBaselineAndOffset(const Box & baseline, const Vector2 & offset)
{
  Box b = baseline;
  b.m_Start += offset;
  b.m_End += offset;
  return b;
}

Box Box::FromPoint(const Vector2 & pos)
{
  return Box{ pos, pos };
}

Box Box::FromPoints(const Vector2 & a, const Vector2 & b)
{
  Box box;
  box.m_Start = MinVectorXY(a, b);
  box.m_End = MaxVectorXY(a, b);
  return box;
}

Vector2 Box::GetPoint(const Box & box, int point)
{
  switch (point)
  {
  case 0:
    return box.m_Start;
  case 1:
    return Vector2(box.m_Start.x, box.m_End.y + 1);
  case 2:
    return Vector2(box.m_End.x + 1, box.m_Start.y);
  case 3:
    return box.m_End + Vector2(1, 1);
  }

  return{};
}

void Box::SetPoint(Box & box, int point, const Vector2 & pos)
{
  switch (point)
  {
  case 0:
    box.m_Start = pos;
    break;
  case 1:
    box.m_Start.x = pos.x;
    box.m_End.y = pos.y - 1;
    break;
  case 2:
    box.m_End.x = pos.x - 1;
    box.m_Start.y = pos.y;
    break;
  case 3:
    box.m_End = pos - Vector2(1, 1);
  }
}

Line Box::GetEdge(const Box & box, int edge)
{
  switch (edge)
  {
  case 0:
    return Line{ box.m_Start, Vector2(box.m_End.x + 1, box.m_Start.y) };
  case 1:
    return Line{ box.m_Start, Vector2(box.m_Start.x, box.m_End.y + 1) };
  case 2:
    return Line{ Vector2(box.m_Start.x, box.m_End.y + 1), box.m_End + Vector2(1, 1) };
  case 3:
    return Line{ Vector2(box.m_End.x + 1, box.m_Start.y), box.m_End + Vector2(1, 1) };
  }

  return{};
}

void Box::SetEdge(Box & box, int edge, Line & line)
{
  switch (edge)
  {
  case 0:
    box.m_Start = line.m_Start;
    box.m_End.x = line.m_End.x - 1;
    break;
  case 1:
    box.m_Start = line.m_Start;
    box.m_End.y = line.m_End.y - 1;
    break;
  case 2:
    box.m_Start.x = line.m_Start.x;
    box.m_End = line.m_End - Vector2(1, 1);
    break;
  case 3:
    box.m_Start.y = line.m_Start.y;
    box.m_End = line.m_End - Vector2(1, 1);
    break;
  }
}

bool Box::OffsetEdge(Box & box, int edge, int offset)
{
  switch (edge)
  {
  case 0:
    if (offset >= 0)
    {
      box.m_Start.y -= offset;
      return true;
    }
    else
    {
      if (box.m_Start.y - offset > box.m_End.y)
      {
        box.m_Start.y = box.m_End.y;
        return false;
      }
      else
      {
        box.m_Start.y -= offset;
        return true;
      }
    }
    break;
  case 1:
    if (offset >= 0)
    {
      box.m_Start.x -= offset;
      return true;
    }
    else
    {
      if (box.m_Start.x - offset > box.m_End.x)
      {
        box.m_Start.x = box.m_End.x;
        return false;
      }
      else
      {
        box.m_Start.x -= offset;
        return true;
      }
    }
    break;
  case 2:
    if (offset >= 0)
    {
      box.m_End.y += offset;
      return true;
    }
    else
    {
      if (box.m_End.y + offset < box.m_Start.y)
      {
        box.m_End.y = box.m_Start.y;
        return false;
      }
      else
      {
        box.m_End.y += offset;
        return true;
      }
    }
    break;
  case 3:
    if (offset >= 0)
    {
      box.m_End.x += offset;
      return true;
    }
    else
    {
      if (box.m_End.x + offset < box.m_Start.x)
      {
        box.m_End.x = box.m_Start.x;
        return false;
      }
      else
      {
        box.m_End.x += offset;
        return true;
      }
    }
    break;
  }

  return true;
}

bool Box::IntersectsLine(const Box & b, const Line & l)
{
  if(l.m_Start.x < b.m_Start.x && l.m_End.x < b.m_Start.x)
  {
    return false;
  }

  if(l.m_Start.y < b.m_Start.y && l.m_End.y < b.m_Start.y)
  {
    return false;
  }

  if(l.m_Start.x > b.m_End.x && l.m_End.x > b.m_End.x)
  {
    return false;
  }

  if(l.m_Start.y > b.m_End.y && l.m_End.y > b.m_End.y)
  {
    return false;
  }

  auto dx = l.m_End.x - l.m_Start.x;
  auto dy = l.m_End.y - l.m_Start.y;

  auto n = Vector2(-dy, dx);

  auto p1 = SelectVectorXY(b.m_Start, b.m_End, 0x00) - l.m_Start;
  auto p2 = SelectVectorXY(b.m_Start, b.m_End, 0x01) - l.m_Start;
  auto p3 = SelectVectorXY(b.m_Start, b.m_End, 0x10) - l.m_Start;
  auto p4 = SelectVectorXY(b.m_Start, b.m_End, 0x11) - l.m_Start;

  auto d1 = DotVector2(p1, n);
  auto d2 = DotVector2(p2, n);
  auto d3 = DotVector2(p3, n);
  auto d4 = DotVector2(p4, n);

  auto dd1 = d1 * d2;
  auto dd2 = d2 * d3;
  auto dd3 = d3 * d4;

  if(dd1 < 0 || dd2 < 0 || dd3 < 0)
  {
    return true;
  }

  return false;
}
