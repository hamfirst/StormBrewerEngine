#pragma once

#include <cmath>

template <typename VecType>
using VecComp = decltype(VecType::x);

template <typename VecCompType>
class IntersectionFuncs
{
public:

  using LengthType = float;

  static auto Sqrt(const VecCompType & c)
  {
    return sqrtf((float)c);
  }

  static auto Abs(const VecCompType & c)
  {
    return abs(c);
  }

  static auto Inverse(const VecCompType & c)
  {
    return 1.0 / c;
  }
};


template <typename VecType>
using LengthType = typename IntersectionFuncs<VecType>::LengthType;

template <typename VecType>
class IntersectionVecFuncs
{
public:
  using VecCompType = VecComp<VecType>;

  static auto Dot(const VecType & a, const VecType & b)
  {
    return a.x * b.x + a.y * b.y;
  }

  static auto MagSquared(const VecType & v)
  {
    return Dot(v, v);
  }

  static auto Mag(const VecType & v)
  {
    return IntersectionFuncs<VecCompType>::Sqrt(MagSquared(v));
  }

  static auto Dist(const VecType & a, const VecType & b)
  {
    return Mag(b - a);
  }

  static auto GetPerpVec(const VecType & a)
  {
    return VecType{ a.y, -a.x };
  }

  static auto Reverse(VecType & a)
  {
    return VecType{ -a.y, -a.x };
  }
};

template <typename VecType>
struct IntersectionResult
{
  bool m_Intersected = false;

  LengthType<VecType> m_T;
  VecType m_HitPos;
  VecType m_HitNormal;
};

template <typename VecCompType>
class Intersection
{
public:
  struct VecType
  {
    VecCompType x;
    VecCompType y;

    VecType() = default;
    VecType(VecCompType ix, VecCompType iy) : x(ix), y(iy) { }
    VecType(const VecType & rhs) = default;
    VecType(VecType && rhs) = default;

    VecType & operator = (const VecType & rhs) = default;
    VecType & operator = (VecType && rhs) = default;

    VecType operator + (const VecType & rhs) const
    {
      return VecType(x + rhs.x, y + rhs.y);
    }

    VecType & operator += (const VecType & rhs)
    {
      x += rhs.x; y += rhs.y;
      return *this;
    }

    VecType operator - (const VecType & rhs) const
    {
      return VecType(x - rhs.x, y - rhs.y);
    }

    VecType & operator -= (const VecType & rhs)
    {
      x -= rhs.x; y -= rhs.y;
      return *this;
    }

    VecType operator * (const VecType & rhs) const
    {
      return VecType(x * rhs.x, y * rhs.y);
    }

    VecType operator * (VecCompType rhs) const
    {
      return VecType(x * rhs, y * rhs);
    }

    VecType & operator *= (const VecType & rhs)
    {
      x *= rhs.x; y *= rhs.y;
      return *this;
    }

    VecType operator *= (VecCompType rhs)
    {
      x *= rhs; y *= rhs;
      return *this;
    }

    VecType operator / (const VecType & rhs) const
    {
      return VecType(x / rhs.x, y / rhs.y);
    }

    VecType operator / (VecCompType factor) const
    {
      return VecType(x / factor, y / factor);
    }

    VecType & operator /= (const VecType & rhs)
    {
      x /= rhs.x; y /= rhs.y;
      return *this;
    }

    VecType operator /= (VecCompType factor)
    {
      x /= factor; y /= factor;
      return *this;
    }

    bool operator == (const VecType & rhs) const
    {
      return x == rhs.x && y == rhs.y;
    }

    bool operator != (const VecType & rhs) const
    {
      return x != rhs.x || y != rhs.y;
    }
  };

  struct CollisionCircle
  {
    VecType m_Center;
    VecCompType m_Radius;
    VecCompType m_RadiusSquared;

    template <typename VectorType, typename VectorCompType>
    CollisionCircle(const VectorType & center, VectorCompType radius)
    {
      m_Center.x = center.x;
      m_Center.y = center.y;

      m_Radius = radius;
      m_RadiusSquared = m_Radius * m_Radius;
    }
  };

  struct CollisionLine
  {
    VecType m_Start;
    VecType m_End;
    VecType m_Offset;

    VecType m_Normal;
    VecType m_Dir;
    VecCompType m_Length;

    VecCompType m_StartD;
    VecCompType m_EndD;
    VecCompType m_NormalD;

    template <typename VectorType>
    CollisionLine(const VectorType & a, const VectorType & b)
    {
      m_Start.x = a.x;
      m_Start.y = a.y;
      m_End.x = b.x;
      m_End.y = b.y;
      m_Offset = b - a;

      m_Length = IntersectionVecFuncs<VecType>::Mag(m_Offset);
      m_Dir = m_Offset / m_Length;
      m_Normal = IntersectionVecFuncs<VecType>::GetPerpVec(m_Dir);

      m_StartD = IntersectionVecFuncs<VecType>::Dot(m_Start, m_Dir);
      m_EndD = IntersectionVecFuncs<VecType>::Dot(m_End, m_Dir);
      m_NormalD = IntersectionVecFuncs<VecType>::Dot(m_Start, m_Normal);
    }
  };

  bool SweptPointToLineTest(const CollisionLine & sweep, const CollisionLine & line, IntersectionResult & result)
  {
    VecCompType zero = VecCompType(0);

    auto other_normal_start_d = IntersectionVecFuncs<VecType>::Dot(line.m_Normal, sweep.m_Start) - line.m_NormalD;
    auto other_normal_end_d = IntersectionVecFuncs<VecType>::Dot(line.m_Normal, sweep.m_End) - line.m_NormalD;

    if (other_normal_start_d * other_normal_end_d > zero)
    {
      return false;
    }

    auto this_normal_start_d = IntersectionVecFuncs<VecType>::Dot(sweep.m_Normal, line.m_Start) - sweep.m_NormalD;
    auto this_normal_end_d = IntersectionVecFuncs<VecType>::Dot(sweep.m_Normal, line.m_End) - sweep.m_NormalD;

    if (this_normal_start_d * this_normal_end_d > zero)
    {
      return false;
    }

    auto d1 = IntersectionVecFuncs<VecType>::Dot(line.m_Dir, sweep.m_Start);
    auto d2 = IntersectionVecFuncs<VecType>::Dot(line.m_Dir, sweep.m_End);

    if (((d1 - line.m_StartD) < 0 && (d2 - line.m_StartD) < zero) ||
        ((d2 - line.m_EndD) > 0 && (d2 - line.m_EndD) > zero))
    {
      return false;
    }

    auto denom = (other_normal_start_d - other_normal_end_d);
    if (denom == 0)
    {
      if ((d1 > line.m_StartD) && (d1 < line.m_EndD))
      {
        // Is the start of the swept point inside the other line
        result.m_Intersected = true;
        result.m_T = zero;
        result.m_HitPos = sweep.m_Start;
        result.m_HitNormal = IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir);
        return true;
      }
      else if ((d2 > line.m_StartD) && (d2 < line.m_EndD))
      {
        // Is the end of the swept point inside the other line
        result.m_Intersected = true;

        if (d2 < line.m_StartD)
        {
          result.m_T = (line.m_StartD - d1) / sweep.m_Length;
          result.m_HitPos = line.m_Start;
        }
        else
        {
          result.m_T = (d1 - line.m_End) / sweep.m_Length;
          result.m_HitPos = line.m_End;
        }

        result.m_HitNormal = IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir);
        return true;
      }

      return false;
    }

    result.m_Intersected = true;
    result.m_T = other_normal_start_d / denom;
    result.m_HitNormal = line.m_Normal;
    result.m_HitPos = sweep.m_Start + sweep.m_Dir * (result.m_T * sweep.m_Length);
    return true;
  }

  bool SweptPointToCircleTest(const CollisionLine & sweep, const CollisionCircle & circle, IntersectionResult & result)
  {
    auto offset = sweep.m_Start - circle.m_Center;

    const VecCompType zero = VecCompType(0);
    const VecCompType one = VecCompType(1);

    auto start_dist_sqrd = IntersectionVecFuncs<VecType>::MagSquared(offset);
    if (start_dist_sqrd <= circle.m_RadiusSquared)
    {
      result.m_Intersected = true;
      result.m_T = zero;
      result.m_HitNormal = start_dist_sqrd == 0 ? IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir) : 
        offset * IntersectionFuncs<VecCompType>::Inverse(IntersectionFuncs<VecCompType>::Sqrt(start_dist_sqrd));
      result.m_HitPos = sweep.m_Start;
      return true;
    }

    auto dist_from_line_start = IntersectionVecFuncs<VecType>::Dot(sweep.m_Dir, offset);
    if (dist_from_line_start < zero)
    {
      return false;
    }

    auto perp_offset = IntersectionFuncs<VecCompType>::Abs(IntersectionVecFuncs<VecType>::Dot(offset, sweep.m_Normal));
    if (perp_offset > circle.m_Radius)
    {
      return false;
    }

    auto circle_d = IntersectionVecFuncs<VecType>::Dot(circle.m_Center, sweep.m_Dir);
    if (circle_d >= sweep.m_EndD - circle.m_Radius)
    {
      return false;
    }

    auto dist_from_offset = IntersectionFuncs<VecCompType>::Sqrt(circle.m_RadiusSquared - perp_offset * perp_offset);

    auto t = (dist_from_line_start - dist_from_offset) / sweep.m_Length;
    if (t >= one)
    {
      return false;
    }

    result.m_Intersected = true;
    result.m_T = t;
    result.m_HitPos = sweep.m_Start + sweep.m_Dir * (sweep.m_Length * t);
    result.m_HitNormal = (result.m_HitPos - circle.m_Center) / circle.m_Radius;
    return true;
  }
};

template <typename VecType>
auto LineToPointDistance(const VecType & a, const VecType & b, const VecType & p)
{
  auto line_offset_a = b - a;
  auto line_offset_b = a - b;

  auto line_len = IntersectionVecFuncs<VecType>::MagSquared(line_offset_a);

  auto offset_a = p - a;
  auto mag_sqrd_a = IntersectionVecFuncs<VecType>::MagSquared(offset_a);
  if (line_len < IntersectionVecFuncs<VecType>::Dot(offset_a, line_offset_a))
  {
    return IntersectionVecFuncs<VecType>::Dist(b, p);
  }

  auto offset_b = p - b;
  auto mag_sqrd_b = IntersectionVecFuncs<VecType>::MagSquared(offset_b);
  if (line_len < IntersectionVecFuncs<VecType>::Dot(offset_b, line_offset_b))
  {
    return IntersectionVecFuncs<VecType>::Dist(a, p);
  }

  auto perp_vec = IntersectionVecFuncs<VecType>::GetPerpVec(line_offset_a);
  auto offset = IntersectionVecFuncs<VecType>::Dot(perp_vec, offset_a) / IntersectionVecFuncs<VecType>::Mag(perp_vec);

  return IntersectionFuncs<LengthType<VecType>>::Abs(offset);
}


