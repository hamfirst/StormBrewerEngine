#pragma once

#include "Data\DataCommon.h"

struct Vector2
{
  Vector2() = default;
  Vector2(int x, int y) : x(x), y(y) { }

  operator RenderVec2() const
  {
    return RenderVec2{ x.AsFloat(), y.AsFloat() };
  }

  Vector2 operator + (const Vector2 & rhs) const
  {
    return Vector2(x + rhs.x, y + rhs.y);
  }

  Vector2 & operator += (const Vector2 & rhs)
  {
    x += rhs.x; y += rhs.y;
    return *this;
  }

  Vector2 operator - (const Vector2 & rhs) const
  {
    return Vector2(x - rhs.x, y - rhs.y);
  }

  Vector2 & operator -= (const Vector2 & rhs)
  {
    x -= rhs.x; y -= rhs.y;
    return *this;
  }

  Vector2 operator * (const Vector2 & rhs) const
  {
    return Vector2(x * rhs.x, y * rhs.y);
  }

  Vector2 & operator *= (const Vector2 & rhs)
  {
    x *= rhs.x; y *= rhs.y;
    return *this;
  }

  Vector2 operator / (const Vector2 & rhs) const
  {
    return Vector2(x / rhs.x, y / rhs.y);
  }

  Vector2 & operator /= (const Vector2 & rhs)
  {
    x /= rhs.x; y /= rhs.y;
    return *this;
  }

  Vector2 operator % (const Vector2 & rhs) const
  {
    return Vector2(x % rhs.x, y % rhs.y);
  }

  Vector2 & operator %= (const Vector2 & rhs)
  {
    x %= rhs.x; y %= rhs.y;
    return *this;
  }

  REFL_MEMBERS
  (
    (x, RInt),
    (y, RInt)
  )
};

struct Box
{
  REFL_MEMBERS
  (
    (m_Start, Vector2),
    (m_End, Vector2)
  )
};

struct Color
{
  operator RenderVec4()
  {
    return RenderVec4{ r.AsFloat(), g.AsFloat(), b.AsFloat(), a.AsFloat() };
  }

  REFL_MEMBERS
  (
    (r, RFloat),
    (g, RFloat),
    (b, RFloat),
    (a, RFloat)
  )
};

