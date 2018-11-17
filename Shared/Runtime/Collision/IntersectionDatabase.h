#pragma once

#include "Foundation/Math/Intersection.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"

template <typename VecCompType>
struct CollisionDatabaseData
{
  uint8_t m_CollisionMask = 0xFF;
};

template <typename VecCompType, typename CollisionData = CollisionDatabaseData<VecCompType>>
class IntersectionDatabase
{
public:

  using VecType = typename Intersection<VecCompType>::VecType;
  using Line = typename Intersection<VecCompType>::CollisionLine;
  using Result = IntersectionResult<VecCompType>;

  uint32_t AddLine(const Line & l, const CollisionData & data, bool check_start, bool check_end)
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();

    auto data_index = m_CollisionData.size();
    m_CollisionData.emplace_back(CollisionLineData{ l, data, check_start, check_end });

    m_SpatialDatabase.Insert(box, (uint32_t)data_index);
    return (uint32_t)data_index;
  }

  bool SweptPointTest(const Line & l, Result & out_result, CollisionData & out_collision_data, uint8_t collision_mask = 0xFF)
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();

    bool intersected = false;

    std::vector<std::size_t> work_list;
    m_SpatialDatabase.Query(box, work_list);

    for (auto index : work_list)
    {
      Result test_result;

      auto & collision_data = m_CollisionData[index];
      if ((collision_data.m_CollisionDataa.m_CollisionMask & collision_mask) == 0)
      {
        continue;
      }

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

  bool SweptCircleTest(const Line & l, const VecCompType & radius, Result & out_result, CollisionData & out_collision_data, uint8_t collision_mask = 0xFF) const
  {
    auto bounding_box = l.GetBoundingBox();
    auto box = bounding_box.ToNormalBox();
    
    auto radius_int = (int)IntersectionFuncs<VecCompType>::Ceil(radius);
    box.m_Start.x -= radius_int;
    box.m_Start.y -= radius_int;
    box.m_End.x += radius_int;
    box.m_End.y += radius_int;

    bool intersected = false;

    std::vector<std::size_t> work_list;
    m_SpatialDatabase.Query(box, work_list);
    for (auto index : work_list)
    {
      Result test_result;

      auto & collision_data = m_CollisionData[index];
      if ((collision_data.m_CollisionData.m_CollisionMask & collision_mask) == 0)
      {
        continue;
      }

      if (Intersection<VecCompType>::SweptCircleToLineTest(l, radius, collision_data.m_Line, collision_data.m_CheckStart, collision_data.m_CheckEnd, test_result))
      {
        if (intersected == false || test_result.m_T < out_result.m_T)
        {
          intersected = true;
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
  std::vector<CollisionLineData> m_CollisionData;
};

