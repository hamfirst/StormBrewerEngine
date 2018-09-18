#pragma once

#include "Foundation/Common.h"
#include "Foundation/Math/Intersection.h"

template <typename ValueType>
static inline auto WrapAngle(ValueType angle)
{
  auto two_pi = IntersectionFuncs<ValueType>::k2Pi;
  auto n_angle = angle / two_pi;
  return (n_angle - IntersectionFuncs<ValueType>::Floor(n_angle)) * two_pi;
}

template <typename ValueType>
static inline auto DiffAngle(ValueType a, ValueType b)
{
  auto two_pi = IntersectionFuncs<ValueType>::k2Pi;
  auto wa = WrapAngle(a);
  auto wb = WrapAngle(b);

  if (wa > wb)
  {
    auto d1 = wa - wb;
    auto d2 = wb + two_pi - wa;
    return d1 < d2 ? -d1 : d2;
  }
  else
  {
    auto d1 = wb - wa;
    auto d2 = wa + two_pi - wb;
    return d1 < d2 ? d1 : -d2;
  }
}

template <typename ValueType>
static inline auto OffsetAngle(ValueType a, ValueType b)
{
  auto two_pi = IntersectionFuncs<ValueType>::k2Pi;
  auto wa = WrapAngle(a);
  auto wb = WrapAngle(b);

  if (wa > wb)
  {
    return std::min(wa - wb, wb + two_pi - wa);
  }
  else
  {
    return std::min(wb - wa, wa + two_pi - wb);
  }
}

template <typename ValueType>
static inline auto BallisticFactor(ValueType v)
{
  auto one = ValueType(1);
  auto two = ValueType(2);

  auto f = v * two - one;
  return one - f * f;
}

template <typename ValueType>
auto AccelToward(ValueType cur_val, ValueType target_val, ValueType accel, ValueType drag)
{
  auto accel_dir = target_val > cur_val ? ValueType(1) : ValueType(-1);

  auto offset = target_val * cur_val < ValueType(0) ? target_val - cur_val : IntersectionFuncs<ValueType>::Abs(target_val) - IntersectionFuncs<ValueType>::Abs(cur_val);

  auto accel_val = offset < ValueType(0) ? drag : accel;
  accel_val = IntersectionFuncs<ValueType>::Min(IntersectionFuncs<ValueType>::Abs(offset), accel_val);

  return cur_val + accel_val * accel_dir;
}

template <typename VecType, typename VecCompType>
auto AccelToward(const VecType & cur_val, const VecType & target_val, VecCompType accel, VecCompType drag)
{
  auto result = VecType(AccelToward(cur_val.x, target_val.x, accel, drag),
                        AccelToward(cur_val.y, target_val.y, accel, drag));

  auto cur_speed = IntersectionVecFuncs<VecType>::Mag(cur_val);
  auto target_speed = IntersectionVecFuncs<VecType>::Mag(target_val);

  auto result_speed = IntersectionVecFuncs<VecType>::Mag(result);
  auto diff_speed = IntersectionVecFuncs<VecType>::Mag(cur_val - result);

  if (target_speed > cur_speed)
  {
    if (diff_speed > accel)
    {
      auto offset = result - cur_val;
      offset *= (accel / diff_speed);

      return cur_val + offset;
    }
  }
  else
  {
    if (diff_speed > drag)
    {
      auto offset = result - cur_val;
      offset *= (drag / diff_speed);

      return cur_val + offset;
    }
  }

  return result;
}

template <typename VecType>
auto ManhattanLength(const VecType & v)
{
  using VecCompType = VecComp<VecType>;
  return IntersectionFuncs<VecCompType>::Abs(v.x) + IntersectionFuncs<VecCompType>::Abs(v.y);
}

template <typename VecType>
auto ManhattanDist(const VecType & a, const VecType & b)
{
  auto diff = a - b;
  return ManhattanLength(diff);
}

template <typename VecType>
auto DistEstimate(const VecType & a, const VecType & b)
{
  using VecCompType = VecComp<VecType>;
  auto diff = a - b;

  auto dx = IntersectionFuncs<VecCompType>::Abs(diff.x);
  auto dy = IntersectionFuncs<VecCompType>::Abs(diff.y);

  auto zero = VecCompType(0);
  if (dx == zero && dy == zero)
  {
    return zero;
  }

  if (dx > dy)
  {
    return dx + dy / VecCompType(2);
  }
  else
  {
    return dy + dx / VecCompType(2);
  }
}

template <typename VecType>
bool IsDepenetrating(const VecType & p1, const VecType & v1, const VecType & p2, const VecType & v2)
{
  auto offset = p2 - p1;
  auto diff_v = v2 - v1;

  return IntersectionVecFuncs<VecType>::Dot(offset, diff_v) > VecComp<VecType>(0);
}

template <typename VecType>
VecType ClosestPointOnLineSeg(const VecType & p1, const VecType & p2, const VecType & q)
{
  using VecCompType = VecComp<VecType>;

  auto diff = p2 - p1;
  auto dist_sqrd = IntersectionVecFuncs<VecType>::MagSquared(diff);

  if (dist_sqrd == VecCompType(0))
  {
    return p1;
  }

  auto dist = IntersectionFuncs<VecCompType>::Sqrt(dist_sqrd);
  auto dir = diff / dist;

  auto dp1 = IntersectionVecFuncs<VecType>::Dot(dir, p1);
  auto dp2 = IntersectionVecFuncs<VecType>::Dot(dir, p2);
  auto dpq = IntersectionVecFuncs<VecType>::Dot(dir, q);

  if (dpq <= dp1)
  {
    return p1;
  }
  else if (dpq >= dp2)
  {
    return p2;
  }
  else
  {
    auto t_diff = dpq - dp1;
    return p1 + (dir * t_diff);
  }
}
