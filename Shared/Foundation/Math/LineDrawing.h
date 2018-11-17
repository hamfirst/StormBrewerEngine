#pragma once

#include "Foundation/Common.h"
#include "Foundation/BasicTypes/BasicTypes.refl.h"

template <typename Visitor>
bool VisitPointsAlongLine(const Vector2 & p1_v, const Vector2 & p2_v, Visitor && visitor)
{
  Vector2 p1 = p1_v;
  Vector2 p2 = p2_v;

  bool steep = abs(p2.y - p1.y) > abs(p2.x - p1.x);
  bool reverse = false;
  if (steep)
  {
    std::swap(p1.x, p1.y);
    std::swap(p2.x, p2.y);
    reverse = !reverse;
  }

  if (p1.x > p2.x)
  {
    std::swap(p1.x, p2.x);
    std::swap(p1.y, p2.y);
    reverse = !reverse;
  }

  int dX = (p2.x - p1.x);
  int dY = abs(p2.y - p1.y);
  int err = (dX / 2);
  int ystep = (p1.y < p2.y ? 1 : -1);
  int y = p1.y;

  for (int x = p1.x; x <= p2.x; ++x)
  {
    auto dest_x = x;
    auto dest_y = y;

    if (steep)
    {
      std::swap(dest_x, dest_y);
    }

    if (visitor(Vector2(dest_x, dest_y)) == false)
    {
      return false;
    }

    err = err - dY;
    if (err < 0)
    {
      y += ystep;
      err += dX;
    }
  }

  return true;
}

