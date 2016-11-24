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

  RInt x, y;
};

struct Box
{
  Vector2 m_Start;
  Vector2 m_End;
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

  RFloat r, g, b, a;
};

