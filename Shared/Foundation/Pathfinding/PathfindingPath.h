#pragma once

#include "Foundation/Common.h"
#include "Foundation/Math/Intersection.h"

template <typename VecCompType>
struct PathFollowerState
{
  std::size_t m_PointIndex;
  VecCompType m_Progress;
  bool m_Forward;
};

template <typename VecCompType>
class PathfindingPath
{
public:
  using VecType = IntersectionVecType<VecCompType>;
  using CostType = VecCompType;

  PathfindingPath() :
    m_TotalLength(VecCompType(0))
  {

  }

  PathfindingPath(const PathfindingPath<VecCompType> & rhs) = default;
  PathfindingPath(PathfindingPath<VecCompType> && rhs) = default;

  PathfindingPath & operator =(const PathfindingPath<VecCompType> & rhs) = default;
  PathfindingPath & operator =(PathfindingPath<VecCompType> && rhs) = default;

  template <typename Visitor>
  static PathfindingPath<VecCompType> CreateFromPointVisitor(Visitor && visitor)
  {
    PathfindingPath<VecCompType> path;

    VecType v;
    while (visitor(v))
    {
      path.m_Points.emplace_back(Point{ v });
    }

    path.FinalizePoints();
    return path;
  }

  template <typename Visitor>
  void VisitPoints(Visitor && visitor)
  {
    for (auto & p : m_Points)
    {
      visitor(p.m_Position);
    }
  }

  template <typename Visitor>
  void VisitLines(Visitor && visitor)
  {
    for(std::size_t index = 0; index < m_Points.size() - 1; ++index)
    {
      visitor(m_Points[index].m_Position, m_Points[index + 1].m_Position);
    }
  }

public:

  template <typename PathFollowerState>
  void InitState(PathFollowerState & state, bool forward) const
  {
    if (forward)
    {
      state.m_PointIndex = 0;
      state.m_Progress = VecCompType(0);
      state.m_Forward = true;
    }
    else
    {
      state.m_PointIndex = m_Points.size() - 1;
      state.m_Progress = VecCompType(0);
      state.m_Forward = false;
    }
  }

  template <typename PathFollowerState>
  VecType GetPositionForState(PathFollowerState & state) const
  {
    if (state.m_Forward)
    {
      auto & p = m_Points[state.m_PointIndex];
      return p.m_Position + (p.m_ToNext * state.m_Progress);
    }
    else
    {
      auto & p = m_Points[state.m_PointIndex];
      return p.m_Position + (p.m_ToPrev * state.m_Progress);
    }
  }

  template <typename PathFollowerState>
  bool AdvanceOnPath(PathFollowerState & state, VecCompType move_dist, VecCompType & outp_remainder) const
  {
    if (state.m_Forward)
    {
      auto dist_to_next = m_Points[state.m_PointIndex].m_NextDist - state.m_Progress;
      if (dist_to_next > move_dist)
      {
        state.m_Progress += move_dist;
      }
      else
      {
        state.m_PointIndex++;
        
        move_dist -= dist_to_next;

        auto zero = VecCompType(0);
        while (move_dist > zero)
        {
          if (state.m_PointIndex >= (int)m_Points.size() - 1)
          {
            outp_remainder = move_dist;
            return true;
          }

          if (move_dist < m_Points[state.m_PointIndex].m_NextDist)
          {
            state.m_Progress = move_dist;
            return false;
          }

          state.m_PointIndex++;
          move_dist -= m_Points[state.m_PointIndex].m_NextDist;
        }

        state.m_Progress = zero;
      }
    }
    else
    {
      auto dist_to_next = m_Points[state.m_PointIndex].m_PrevDist - state.m_Progress;
      if (dist_to_next > move_dist)
      {
        state.m_Progress += move_dist;
      }
      else
      {
        state.m_PointIndex--;

        move_dist -= dist_to_next;

        auto zero = VecCompType(0);
        while (move_dist > zero)
        {
          if (state.m_PointIndex == 0)
          {
            outp_remainder = move_dist;
            return true;
          }

          if (move_dist < m_Points[state.m_PointIndex].m_PrevDist)
          {
            state.m_Progress = move_dist;
            return false;
          }

          state.m_PointIndex--;
          move_dist -= m_Points[state.m_PointIndex].m_PrevDist;
        }

        state.m_Progress = zero;
      }
    }


    return false;
  }

  template <typename PathFollowerState>
  VecType GetTangent(PathFollowerState & state) const
  {
    if (state.m_Forward)
    {
      return m_Points[state.m_PointIndex].m_ToNext;
    }
    else
    {
      return m_Points[state.m_PointIndex].m_ToPrev;
    }
  }

  VecCompType GetTotalLength() const
  {
    return m_TotalLength;
  }

private:

  void FinalizePoints()
  {
    ASSERT(m_Points.size() >= 2, "Pathfinding path must have at least 2 points");

    VecCompType zero = VecCompType(0);
    VecCompType total_length = zero;
    for (std::size_t index = 0; index < m_Points.size() - 1; ++index)
    {
      auto next_index = index + 1;
      auto dist = IntersectionVecFuncs<VecType>::Dist(m_Points[index].m_Position, m_Points[next_index].m_Position);

      auto offset = m_Points[next_index].m_Position - m_Points[index].m_Position;

      m_Points[index].m_NextDist = dist;
      m_Points[next_index].m_PrevDist = dist;

      if (dist == zero)
      {
        m_Points[index].m_ToNext = VecType(0, 1);
        m_Points[next_index].m_ToPrev = VecType(0, 1);
      }
      else
      {
        m_Points[index].m_ToNext = offset / dist;
        m_Points[next_index].m_ToPrev = IntersectionVecFuncs<VecType>::Reverse(m_Points[index].m_ToNext);
      }

      total_length += dist;
    }

    std::size_t index = m_Points.size() - 1;
    std::size_t next_index = 0;

    auto dist = IntersectionVecFuncs<VecType>::Dist(m_Points[index].m_Position, m_Points[next_index].m_Position);

    auto offset = m_Points[next_index].m_Position - m_Points[index].m_Position;

    m_Points[index].m_NextDist = dist;
    m_Points[next_index].m_PrevDist = dist;

    if (dist == zero)
    {
      m_Points[index].m_ToNext = VecType(0, 1);
      m_Points[next_index].m_ToPrev = VecType(0, 1);
    }
    else
    {
      m_Points[index].m_ToNext = offset / dist;
      m_Points[next_index].m_ToPrev = IntersectionVecFuncs<VecType>::Reverse(m_Points[index].m_ToNext);
    }

    m_TotalLength = total_length;
  }


  struct Point
  {
    VecType m_Position;
    VecType m_ToNext;
    VecType m_ToPrev;
    VecCompType m_NextDist;
    VecCompType m_PrevDist;
  };

  std::vector<Point> m_Points;
  VecCompType m_TotalLength;
};
