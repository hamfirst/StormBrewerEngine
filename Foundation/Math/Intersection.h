#pragma once

#include <cmath>

template <typename VecType>
using VecComp = decltype(VecType::x);

template <typename VecType>
auto Dot(const VecType & a, const VecType & b)
{
  return a.x * b.x + a.y * b.y;
}

template <typename VecCompType>
auto Sqrt(const VecCompType & c)
{
  return sqrtf((float)c);
}

template <typename VecCompType>
auto Abs(const VecCompType & c)
{
  return abs(c);
}

template <typename VecType>
auto MagSquared(const VecType & v)
{
  return Dot(v, v);
}

template <typename VecType>
auto Mag(const VecType & v)
{
  return Sqrt(MagSquared(v));
}

template <typename VecType>
auto Dist(const VecType & a, const VecType & b)
{
  return Mag(b - a);
}

template <typename VecType>
auto GetPerpVec(const VecType & a)
{
  return VecType{ a.y, -a.x };
}

template <typename VecType>
auto LineToPointDistance(const VecType & a, const VecType & b, const VecType & p)
{
  auto line_offset_a = b - a;
  auto line_offset_b = a - b;

  auto line_len = MagSquared(line_offset_a);

  auto offset_a = p - a;
  auto mag_sqrd_a = MagSquared(offset_a);
  if (line_len < Dot(offset_a, line_offset_a))
  {
    return Dist(b, p);
  }

  auto offset_b = p - b;
  auto mag_sqrd_b = MagSquared(offset_b);
  if (line_len < Dot(offset_b, line_offset_b))
  {
    return Dist(a, p);
  }

  auto perp_vec = GetPerpVec(line_offset_a);
  return Abs(Dot(perp_vec, offset_a) / Mag(perp_vec));
}


