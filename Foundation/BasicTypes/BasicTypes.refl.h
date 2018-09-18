#pragma once

#include <StormData/StormData.h>
#include <StormData/StormDataTypes.h>

#include "Foundation/Math/Math.h"

struct Vector2
{
  STORM_REFL;
  Vector2();
  Vector2(const Vector2 & rhs) = default;
  Vector2(Vector2 && rhs) = default;
  Vector2(int x, int y);
  Vector2(float x, float y);
  Vector2(const RenderVec2 & v);

  Vector2 & operator = (Vector2 && rhs) = default;
  Vector2 & operator = (const Vector2 & rhs) = default;

  operator RenderVec2() const
  {
    return RenderVec2{ (float)x, (float)y };
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
    x = (int)(x * rhs); y = (int)(y * rhs);
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

  Vector2 operator - () const
  {
    return Vector2(-x, -y);
  }

  bool operator == (const Vector2 & rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  bool operator != (const Vector2 & rhs) const
  {
    return x != rhs.x || y != rhs.y;
  }

  int x, y;
};

struct Line
{
  STORM_REFL;
  Vector2 m_Start;
  Vector2 m_End;
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

  bool operator == (const Box & rhs) const
  {
    return m_Start == rhs.m_Start && m_End == rhs.m_End;
  }

  Box Offset(const Vector2 & offset) const;
  Box MirrorX() const;

  static Box FromFrameCenterAndSize(const Vector2 & frame_center, const Vector2 & frame_size);
  static Box FromBaselineAndOffset(const Box & baseline, const Vector2 & offset);
  static Box FromPoint(const Vector2 & pos);
  static Box FromPoints(const Vector2 & a, const Vector2 & b);

  static Vector2 GetPoint(const Box & box, int point);
  static void SetPoint(Box & box, int point, const Vector2 & pos);

  static Line GetEdge(const Box & box, int edge);
  static void SetEdge(Box & box, int edge, Line & line);
  static bool OffsetEdge(Box & box, int edge, int offset);
};

struct Color
{
  Color() = default;
  Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) { }
  Color(int r, int g, int b, int a = 255) : r((float)r / 255.0f), g((float)g / 255.0f), b((float)b / 255.0f), a((float)a / 255.0f) { }

  operator RenderVec4() const
  {
    return RenderVec4{ (float)r, (float)g, (float)b, (float)a };
  }

  STORM_REFL;
  float r, g, b, a;
};

