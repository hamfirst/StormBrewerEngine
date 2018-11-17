#pragma once

#include "Foundation/BasicTypes/BasicTypes.refl.h"

#include <cmath>

template <typename StorageType, StorageType NumBits, StorageType FractionalBits>
class NetFixedPoint;

template <typename VecType>
using VecComp = decltype(VecType::x);

template <typename VecCompType>
class IntersectionFuncs
{
public:
  static constexpr VecCompType k2Pi = VecCompType(6.28318530718);

  static auto Sqrt(const VecCompType & c)
  {
    return sqrtf((float)c);
  }

  static auto Abs(const VecCompType & c)
  {
    return abs(c);
  }

  static auto Min(const VecCompType & a, const VecCompType & b)
  {
    return min(a, b);
  }

  static auto Max(const VecCompType & a, const VecCompType & b)
  {
    return max(a, b);
  }

  static auto Floor(const VecCompType & a)
  {
    return floorf(a);
  }

  static auto Ceil(const VecCompType & a)
  {
    return ceilf(a);
  }

  static auto Reciprocal(const VecCompType & c)
  {
    return VecCompType(1) / c;
  }

  static auto Inverse(const VecCompType & c)
  {
    return -c;
  }

  static auto NextHighest(const VecCompType & c)
  {
    return nextafterf(c, c + 1.0f);
  }

  static auto NextLowest(const VecCompType & c)
  {
    return nextafterf(c, c - 1.0f);
  }
};

template <typename StorageType, StorageType NumBits, StorageType FractionalBits>
class IntersectionFuncs<NetFixedPoint<StorageType, NumBits, FractionalBits>>
{
public:
  static NetFixedPoint<StorageType, NumBits, FractionalBits> k2Pi;

  static auto Sqrt(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return c.Sqrt();
  }

  static auto Abs(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return c.Abs();
  }

  static auto Min(const NetFixedPoint<StorageType, NumBits, FractionalBits> & a, const NetFixedPoint<StorageType, NumBits, FractionalBits> & b)
  {
    return a.Min(b);
  }

  static auto Max(const NetFixedPoint<StorageType, NumBits, FractionalBits> & a, const NetFixedPoint<StorageType, NumBits, FractionalBits> & b)
  {
    return a.Max(b);
  }

  static auto Floor(const NetFixedPoint<StorageType, NumBits, FractionalBits> & a)
  {
    return a.Floor();
  }

  static auto Ceil(const NetFixedPoint<StorageType, NumBits, FractionalBits> & a)
  {
    return a.Ceil();
  }

  static auto Reciprocal(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return NetFixedPoint<StorageType, NumBits, FractionalBits>(1) / c;
  }

  static auto Inverse(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return c.Invert();
  }

  static auto NextHighest(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return c - NetFixedPoint<StorageType, NumBits, FractionalBits>::Epsilon();
  }

  static auto NextLowest(const NetFixedPoint<StorageType, NumBits, FractionalBits> & c)
  {
    return c - NetFixedPoint<StorageType, NumBits, FractionalBits>::Epsilon();
  }
};

template <typename StorageType, StorageType NumBits, StorageType FractionalBits>
NetFixedPoint<StorageType, NumBits, FractionalBits> IntersectionFuncs<NetFixedPoint<StorageType, NumBits, FractionalBits>>::k2Pi = 
  NetFixedPoint<StorageType, NumBits, FractionalBits>("6.28318530718");

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
    return VecType{ a.y, IntersectionFuncs<VecCompType>::Inverse(a.x) };
  }

  static auto Reverse(const VecType & a)
  {
    return VecType{ IntersectionFuncs<VecCompType>::Inverse(a.x), IntersectionFuncs<VecCompType>::Inverse(a.y) };
  }

  static auto Normalize(const VecType & v, const VecType & default_val = VecType(VecCompType(1), VecCompType(0)))
  {
    auto mag = Mag(v);
    if (mag == VecCompType(0))
    {
      return default_val;
    }

    return v / mag;
  }

  static auto NormalizeInPlace(VecType & v, const VecType & default_val = VecType(VecCompType(1), VecCompType(0)))
  {
    auto mag = Mag(v);
    if (mag == VecCompType(0))
    {
      v = default_val;
      return mag;
    }

    v /= mag;
    return mag;
  }
};

template <typename VecCompType>
struct IntersectionVecType
{
  VecCompType x;
  VecCompType y;

  using VecType = IntersectionVecType<VecCompType>;

  IntersectionVecType() = default;

  template <typename VecInitType>
  IntersectionVecType(VecInitType ix, VecInitType iy) : x(ix), y(iy) { }
  IntersectionVecType(Vector2 & v) : x(v.x), y(v.y) { }

  IntersectionVecType(const VecType & rhs) = default;
  IntersectionVecType(VecType && rhs) = default;

  VecType & operator = (const VecType & rhs) = default;
  VecType & operator = (VecType && rhs) = default;

  void SetZero()
  {
    x = VecCompType(0);
    y = VecCompType(0);
  }

  operator Vector2() const
  {
    return Vector2((int)IntersectionFuncs<VecCompType>::Floor(x), (int)IntersectionFuncs<VecCompType>::Floor(y));
  }

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

template <typename VecCompType>
struct IntersectionResult
{
  using VecType = IntersectionVecType<VecCompType>;
  bool m_Intersected = false;

  VecCompType m_T;
  VecType m_HitPos;
  VecType m_HitNormal;
};

template <typename VecCompType>
class Intersection
{
public:
  using VecType = IntersectionVecType<VecCompType>;

  struct CollisionBoundingBox
  {
    VecType m_Start;
    VecType m_End;

    Box ToNormalBox() const
    {
      Box b;
      b.m_Start.x = IntersectionFuncs<VecCompType>::Floor(m_Start.x);
      b.m_Start.y = IntersectionFuncs<VecCompType>::Floor(m_Start.y);

      b.m_End.x = IntersectionFuncs<VecCompType>::Ceil(m_End.x);
      b.m_End.y = IntersectionFuncs<VecCompType>::Ceil(m_End.y);
      return b;
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

    template <typename VectorType, typename VectorCompType>
    CollisionCircle(const VectorType & center, VectorCompType radius, VectorCompType radius_squared)
    {
      m_Center.x = center.x;
      m_Center.y = center.y;

      m_Radius = radius;
      m_RadiusSquared = radius_squared;
    }

    CollisionBoundingBox GetBoundingBox() const
    {
      CollisionBoundingBox box;
      box.m_Start.x = m_Center.x - m_Radius;
      box.m_Start.y = m_Center.y - m_Radius;
      box.m_End.x = m_Center.x + m_Radius;
      box.m_End.y = m_Center.y + m_Radius;
      return box;
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
      m_Offset = m_End - m_Start;

      m_Length = IntersectionVecFuncs<VecType>::Mag(m_Offset);
      if (m_Length == VecCompType(0))
      {
        m_Dir.x = VecCompType(1);
        m_Dir.y = VecCompType(0);
      }
      else
      {
        m_Dir = m_Offset / m_Length;
      }

      m_Normal = IntersectionVecFuncs<VecType>::GetPerpVec(m_Dir);

      m_StartD = IntersectionVecFuncs<VecType>::Dot(m_Start, m_Dir);
      m_EndD = IntersectionVecFuncs<VecType>::Dot(m_End, m_Dir);
      m_NormalD = IntersectionVecFuncs<VecType>::Dot(m_Start, m_Normal);
    }

    CollisionBoundingBox GetBoundingBox() const
    {
      CollisionBoundingBox box;
      box.m_Start.x = IntersectionFuncs<VecCompType>::Min(m_Start.x, m_End.x);
      box.m_Start.y = IntersectionFuncs<VecCompType>::Min(m_Start.y, m_End.y);
      box.m_End.x = IntersectionFuncs<VecCompType>::Max(m_Start.x, m_End.x);
      box.m_End.y = IntersectionFuncs<VecCompType>::Max(m_Start.y, m_End.y);
      return box;
    }
  };

  static bool SweptPointToLineTest(const CollisionLine & sweep, const CollisionLine & line, IntersectionResult<VecCompType> & result)
  {
    const VecCompType zero = VecCompType(0);

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

    if (((d1 - line.m_StartD) < zero && (d2 - line.m_StartD) < zero) ||
        ((d1 - line.m_EndD) > zero && (d2 - line.m_EndD) > zero))
    {
      return false;
    }

    auto denom = (other_normal_start_d - other_normal_end_d);
    if (denom == zero)
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
          result.m_T = (d1 - line.m_EndD) / sweep.m_Length;
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

    auto hit_pos_offset = result.m_T * sweep.m_Length;
    result.m_HitPos = sweep.m_Start + (sweep.m_Dir * hit_pos_offset);
    return true;
  }

  static bool SweptPointToCircleTest(const CollisionLine & sweep, const CollisionCircle & circle, IntersectionResult<VecCompType> & result, bool alllow_depen = false)
  {
    auto offset = sweep.m_Start - circle.m_Center;

    const VecCompType zero = VecCompType(0);
    const VecCompType one = VecCompType(1);

    auto start_dist_sqrd = IntersectionVecFuncs<VecType>::MagSquared(offset);
    if (start_dist_sqrd <= circle.m_RadiusSquared)
    {
      if (alllow_depen == false)
      {
        result.m_Intersected = true;
        result.m_T = zero;
        result.m_HitNormal = (start_dist_sqrd == zero ? IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir) :
          offset * IntersectionFuncs<VecCompType>::Reciprocal(IntersectionFuncs<VecCompType>::Sqrt(start_dist_sqrd)));
        result.m_HitPos = sweep.m_Start;
        return true;
      }
      else
      {
        if (IntersectionVecFuncs<VecType>::Dot(sweep.m_Dir, offset) <= zero)
        {
          result.m_Intersected = true;
          result.m_T = zero;
          result.m_HitNormal = (start_dist_sqrd == zero ? IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir) :
            offset * IntersectionFuncs<VecCompType>::Reciprocal(IntersectionFuncs<VecCompType>::Sqrt(start_dist_sqrd)));
          result.m_HitPos = sweep.m_Start;
          return true;
        }
        else
        {
          return false;
        }
      }
    }

    if (sweep.m_Length == zero)
    {
      return false;
    }

    auto dist_from_line_start = IntersectionVecFuncs<VecType>::Dot(sweep.m_Dir, offset);
    if (dist_from_line_start > zero)
    {
      return false;
    }

    auto perp_offset = IntersectionFuncs<VecCompType>::Abs(IntersectionVecFuncs<VecType>::Dot(offset, sweep.m_Normal));
    if (perp_offset > circle.m_Radius)
    {
      return false;
    }

    auto circle_size_sqrd = circle.m_RadiusSquared - (perp_offset * perp_offset);
    if (circle_size_sqrd < zero)
    {
      return false;
    }

    auto circle_size = IntersectionFuncs<VecCompType>::Sqrt(circle_size_sqrd);
    auto travel_dist = IntersectionFuncs<VecCompType>::Inverse(dist_from_line_start) - circle_size;

    if (sweep.m_Length < travel_dist)
    {
      return false;
    }

    auto t = travel_dist / sweep.m_Length;

    result.m_Intersected = true;
    result.m_T = t;
    result.m_HitPos = sweep.m_Start + sweep.m_Dir * (sweep.m_Length * t);
    result.m_HitNormal = (result.m_HitPos - circle.m_Center) / circle.m_Radius;
    return true;
  }

  static bool SweptCircleToLineTest(const CollisionLine & sweep, VecCompType radius, const CollisionLine & line, bool check_start, bool check_end, IntersectionResult<VecCompType> & result)
  {
    auto start_normal_d = IntersectionVecFuncs<VecType>::Dot(line.m_Normal, sweep.m_Start);
    if (IntersectionFuncs<VecCompType>::Abs(start_normal_d - line.m_NormalD) < radius)
    {
      auto start_d = IntersectionVecFuncs<VecType>::Dot(line.m_Dir, sweep.m_Start);
      
      if (start_d >= line.m_StartD && start_d <= line.m_EndD)
      {
        result.m_Intersected = true;
        result.m_T = VecCompType(0);
        result.m_HitPos = sweep.m_Start;
        result.m_HitNormal = IntersectionVecFuncs<VecType>::Reverse(sweep.m_Dir);
        return true;
      }
    }

    auto moved_line = line;
    if (start_normal_d > line.m_NormalD)
    {
      moved_line.m_Start += line.m_Normal * radius;
      moved_line.m_End += line.m_Normal * radius;
      moved_line.m_NormalD += radius;
    }
    else
    {
      moved_line.m_Start -= line.m_Normal * radius;
      moved_line.m_End -= line.m_Normal * radius;
      moved_line.m_NormalD -= radius;
    }

    IntersectionResult<VecCompType> test_result;
    SweptPointToLineTest(sweep, moved_line, test_result);

    auto radius_squared = radius * radius;

    if (check_start)
    {
      IntersectionResult<VecCompType> circle_result;
      auto test_circle = CollisionCircle(line.m_Start, radius, radius_squared);
      SweptPointToCircleTest(sweep, test_circle, circle_result);

      if (circle_result.m_Intersected)
      {
        if (test_result.m_Intersected == false || circle_result.m_T < test_result.m_T)
        {
          test_result = circle_result;
        }
      }
    }

    if (check_end)
    {
      IntersectionResult<VecCompType> circle_result;
      auto test_circle = CollisionCircle(line.m_End, radius, radius_squared);
      SweptPointToCircleTest(sweep, test_circle, circle_result);

      if (circle_result.m_Intersected)
      {
        if (test_result.m_Intersected == false || circle_result.m_T < test_result.m_T)
        {
          test_result = circle_result;
        }
      }
    }

    if (test_result.m_Intersected)
    {
      result = test_result;
      return true;
    }

    return false;
  }

  static bool SweptCircleToSweptCircleTest(const CollisionLine & sweep1, const CollisionLine & sweep2, VecCompType radius, IntersectionResult<VecCompType> & result)
  {
    const auto zero = VecCompType(0);
    const auto one = VecCompType(1);
    const auto two = VecCompType(2);
    const auto four = VecCompType(4);

    if (radius == zero)
    {
      return false;
    }

    auto p1 = sweep1.m_Start;
    auto p2 = sweep2.m_Start;
    auto v1 = sweep1.m_Offset;
    auto v2 = sweep2.m_Offset;

    auto dpx = p1.x - p2.x;
    auto dpy = p1.y - p2.y;
    auto dvx = v1.x - v2.x;
    auto dvy = v1.y - v2.y;

    auto a = dvx * dvx + dvy * dvy;

    if (a == zero)
    {
      return false;
    }

    auto b = dpx * dvx + dpy * dvy;
    b *= 2;

    auto c = dpx * dpx + dpy * dpy - radius * radius;

    auto b_sqrd = b * b;
    auto four_ac = four * a * c;

    if (b_sqrd < four_ac)
    {
      return false;
    }

    auto sqrt_four_ac = IntersectionFuncs<VecCompType>::Sqrt(b_sqrd - four_ac);
    auto neg_b = IntersectionFuncs<VecCompType>::Inverse(b);

    auto num = neg_b - sqrt_four_ac;
    if (num < 0)
    {
      num = neg_b + sqrt_four_ac;

      if (num < 0)
      {
        return false;
      }
    }

    auto denom = a * two;
    auto t = num / denom;

    if (t > one)
    {
      return false;
    }

    auto p1_final = p1 + sweep1.m_Dir * (t * sweep1.m_Length);
    auto p2_final = p2 + sweep2.m_Dir * (t * sweep2.m_Length);

    auto final_offset = p2_final - p1_final;
    auto final_offset_len = IntersectionVecFuncs<VecType>::Mag(final_offset);

    if (final_offset_len == zero)
    {
      return false;
    }

    result.m_Intersected = true;
    result.m_T = t;
    result.m_HitNormal = final_offset / final_offset_len;
    result.m_HitPos = (p1_final + p2_final) / two;
    return true;
  }

  static bool CollisionBoxOverlaps(const CollisionBoundingBox & b1, const CollisionBoundingBox & b2)
  {
    return 
      !((b1.m_Start.x > b2.m_End.x) |
        (b1.m_Start.y > b2.m_End.y) |
        (b1.m_End.x < b2.m_Start.x) |
        (b1.m_End.y < b2.m_Start.y));
  }
};

template <typename VecType>
auto LineToPointDistance(const VecType & a, const VecType & b, const VecType & p)
{
  using LengthType = decltype(IntersectionVecFuncs<VecType>::Dist(a, b));

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

  return IntersectionFuncs<LengthType>::Abs(offset);
}

template <typename VecType>
bool LineBoxIntersection(const VecType & line_start, const VecType & line_end, const VecType & box_start, const VecType & box_end)
{
  // These are not needed if you've already done the box -> box intersection test

  //if (line_start.x < box_start.x && line_end.x < box_start.x)
  //{
  //  return false;
  //}

  //if (line_start.y < box_start.y && line_end.y < box_start.y)
  //{
  //  return false;
  //}

  //if (line_start.x > box_end.x && line_end.x > box_end.x)
  //{
  //  return false;
  //}

  //if (line_start.y > box_end.y && line_end.y > box_end.y)
  //{
  //  return false;
  //}

  int dx = line_end.x - line_start.x;
  int dy = line_start.y - line_end.y;

  int dx1 = box_start.x - line_start.x;
  int dy1 = box_start.y - line_start.y;
  int dx2 = box_end.x - line_start.x;
  int dy2 = box_end.y - line_start.y;

  int v1 = dy * dx1 + dx * dy1;
  int v2 = dy * dx1 + dx * dy2;
  int v3 = dy * dx2 + dx * dy2;
  int v4 = dy * dx2 + dx * dy1;

  if ((v1 * v2 <= 0) |
    (v2 * v3 <= 0) |
    (v3 * v4 <= 0))
  {
    return true;
  }

  return false;
}
