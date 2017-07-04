#pragma once

#include "Foundation/Math/Intersection.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"

template <typename VecCompType, typename CollisionData>
class CollisionDatabase
{
public:

  using VecType = Intersection<VecCompType>::VecType;
  using Line = Intersection<VecCompType>::CollisionLine;
  using Result = IntersectionResult<VecType>;

  uint32_t AddLine(const Line & l, const CollisionData & data, bool check_start, bool check_end)
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();

    auto data_index = m_CollisionData.size();
    m_CollisionData.emplace_back(CollisionLineData{ l, data, check_start, check_end });

    m_SpatialDatabase.Insert(box, data_index);
    return data_index;
  }

  bool SweptPointTest(const Line & l, Result & out_result, CollisionData & out_collision_data)
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();

    bool intersected = false;

    m_WorkList.clear();
    m_SpatialDatabase.Query(box, m_WorkList);
    for (auto index : m_WorkList)
    {
      Result test_result;

      auto & collision_data = m_CollisionData[index];
      if (Intersection<VecCompType>::SweptPointToLineTest(l, collision_data.m_Line, test_result))
      {
        if (intersected == false || test_result.m_T < out_result.m_T)
        {
          out_result = test_result;
          out_collision_data = collision_data.m_CollisionData;
        }
      }
    }

    return intersected;
  }

  bool SweptCircleTest(const Line & l, const VecCompType & radius, Result & out_result, CollisionData & out_collision_data)
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();

    bool intersected = false;

    m_WorkList.clear();
    m_SpatialDatabase.Query(box, m_WorkList);
    for (auto index : m_WorkList)
    {
      Result test_result;

      auto & collision_data = m_CollisionData[index];
      if (Intersection<VecCompType>::SweptCircleToLineTest(l, radius, collision_data.m_Line, collision_data.m_CheckStart, collision.m_CheckEnd, test_result))
      {
        if (intersected == false || test_result.m_T < out_result.m_T)
        {
          out_result = test_result;
          out_collision_data = collision_data.m_CollisionData;
        }
      }
    }

    return intersected;
  }

  void Clear()
  {
    m_SpatialDatabase.Clear();
    m_CollisionData.clear();
  }

private:

  struct CollisionLineData
  {
    Line m_Line;
    CollisionData m_CollisionData;
    bool m_CheckStart;
    bool m_CheckEnd;
  };

  SpatialDatabase m_SpatialDatabase;
  std::vector<std::pair<CollisionData, Line>> m_CollisionData;
  std::vector<std::size_t> m_WorkList;
};

