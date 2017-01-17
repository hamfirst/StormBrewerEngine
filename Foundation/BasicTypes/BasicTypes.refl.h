#pragma once

#include <StormData/StormDataTypes.h>

#include "Foundation/Math/Math.h"

struct Vector2
{
  Vector2() = default;

  Vector2(int x, int y) : x(x), y(y) { }
  Vector2(const RenderVec2 & v) : x((int)v.x), y((int)v.y) { }

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

  Vector2 operator * (int rhs) const
  {
    return Vector2(x * rhs, y * rhs);
  }

  Vector2 operator * (float rhs) const
  {
    return Vector2((int)(x * rhs), (int)(y * rhs));
  }

  Vector2 & operator *= (const Vector2 & rhs)
  {
    x *= rhs.x; y *= rhs.y;
    return *this;
  }

  Vector2 operator *= (int rhs)
  {
    x *= rhs; y *= rhs;
    return *this;
  }

  Vector2 operator *= (float rhs)
  {
    x *= rhs; y *= rhs;
    return *this;
  }

  Vector2 operator / (const Vector2 & rhs) const
  {
    return Vector2(x / rhs.x, y / rhs.y);
  }

  Vector2 operator / (int factor) const
  {
    return Vector2(x / factor, y / factor);
  }

  Vector2 & operator /= (const Vector2 & rhs)
  {
    x /= rhs.x; y /= rhs.y;
    return *this;
  }

  Vector2 operator /= (int factor)
  {
    x /= factor; y /= factor;
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

  STORM_REFL;
  RInt x, y;
};

struct Box
{
  STORM_REFL;
  Vector2 m_Start;
  Vector2 m_End;

  Vector2 Size() const
  {
    return m_End - m_Start;
  }

  Vector2 Center() const
  {
    auto size = Size();
    return m_Start + size / 2;
  }
};

struct Color
{
  Color() = default;
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
  Color(int r, int g, int b, int a) : r((float)r / 255.0f), g((float)g / 255.0f), b((float)b / 255.0f), a((float)a / 255.0f) { }

  operator RenderVec4() const
  {
    return RenderVec4{ r.AsFloat(), g.AsFloat(), b.AsFloat(), a.AsFloat() };
  }

  STORM_REFL;
  RFloat r, g, b, a;
};

