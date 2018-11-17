#pragma once

#include "Foundation/Common.h"
#include "Foundation/BasicTypes/BasicTypes.refl.h"

#include <sb/vector.h>

#include <utility>

template <typename NodeType>
class SpatialDatabaseGrid
{
public:
  template <typename Visitor>
  void VisitNode(uint32_t grid_id, Visitor && v, bool create_nodes = false)
  {
    auto node_itr = m_Nodes.find(grid_id);
    if (node_itr == m_Nodes.end())
    {
      if (create_nodes)
      {
        NodeType new_node;
        auto result = m_Nodes.emplace(std::make_pair(grid_id, std::move(new_node)));
        node_itr = result.first;
      }
      else
      {
        return;
      }
    }

    v(GetGridBoxForGridId(grid_id), node_itr->second);
  }

  template <typename Visitor>
  void VisitGrid(const Box & b, Visitor && v, bool create_nodes = false)
  {
    int start_x = GetGridModulo(b.m_Start.x);
    int start_y = GetGridModulo(b.m_Start.y);
    int end_x = GetGridModulo(b.m_End.x);
    int end_y = GetGridModulo(b.m_End.y);

    for (int y = start_y; y <= end_y; y++)
    {
      for (int x = start_x; x <= end_x; x++)
      {
        uint32_t grid_id = GetGridId(x, y);

        auto node_itr = m_Nodes.find(grid_id);
        if (node_itr == m_Nodes.end())
        {
          if (create_nodes)
          {
            NodeType new_node;
            auto result = m_Nodes.emplace(std::make_pair(grid_id, std::move(new_node)));
            node_itr = result.first;
          }
          else
          {
            continue;
          }
        }

        if (v(grid_id, node_itr->second) == false)
        {
          return;
        }
      }
    }
  }

  template <typename Visitor>
  void VisitGrid(const Box & b, Visitor && v) const
  {
    int start_x = GetGridModulo(b.m_Start.x);
    int start_y = GetGridModulo(b.m_Start.y);
    int end_x = GetGridModulo(b.m_End.x);
    int end_y = GetGridModulo(b.m_End.y);

    for (int y = start_y; y <= end_y; y++)
    {
      for (int x = start_x; x <= end_x; x++)
      {
        uint32_t grid_id = GetGridId(x, y);

        auto node_itr = m_Nodes.find(grid_id);
        if (node_itr == m_Nodes.end())
        {
          continue;
        }

        if (v(grid_id, node_itr->second) == false)
        {
          return;
        }
      }
    }
  }

  template <typename Visitor>
  void VisitGridIds(const Box & b, Visitor && v)
  {
    int start_x = GetGridModulo(b.m_Start.x);
    int start_y = GetGridModulo(b.m_Start.y);
    int end_x = GetGridModulo(b.m_End.x);
    int end_y = GetGridModulo(b.m_End.y);

    for (int y = start_y; y <= end_y; y++)
    {
      for (int x = start_x; x <= end_x; x++)
      {
        uint32_t grid_id = GetGridId(x, y);

        if (v(grid_id) == false)
        {
          return;
        }
      }
    }
  }

  template <typename Visitor>
  void VisitGridIds(const Box & b, Visitor && v) const
  {
    int start_x = GetGridModulo(b.m_Start.x);
    int start_y = GetGridModulo(b.m_Start.y);
    int end_x = GetGridModulo(b.m_End.x);
    int end_y = GetGridModulo(b.m_End.y);

    for (int y = start_y; y <= end_y; y++)
    {
      for (int x = start_x; x <= end_x; x++)
      {
        uint32_t grid_id = GetGridId(x, y);

        if (v(grid_id) == false)
        {
          return;
        }
      }
    }
  }

  template <typename Visitor>
  void VisitAll(Visitor && v)
  {
    for (auto & elem : m_Nodes)
    {
      v(elem.first, elem.second);
    }
  }

  template <typename Visitor>
  void VisitAll(Visitor && v) const
  {
    for (auto & elem : m_Nodes)
    {
      v(elem.first, elem.second);
    }
  }

  void RemoveGrid(uint32_t grid_id)
  {
    m_Nodes.erase(grid_id);
  }

  Box GetGridBoxForGridId(uint32_t grid_id)
  {
    int16_t x = (int16_t)grid_id;
    int16_t y = (int16_t)(grid_id >> 16);

    Box b;
    b.m_Start.x = (int)x * 1024;
    b.m_Start.y = (int)y * 1024;
    b.m_End.x = b.m_Start.x + 1023;
    b.m_End.y = b.m_Start.y + 1023;
    return b;
  }

  void Clear()
  {
    m_Nodes.clear();
  }

protected:
  static int GetGridModulo(int value)
  {
    return value >= 0 ? value / 1024 : (value + 1) / 1024 - 1;
  }

  static uint32_t GetGridId(int x, int y)
  {
    uint32_t grid_id = y & 0xFFFF;
    grid_id <<= 16;
    grid_id |= (x & 0xFFFF);
    return grid_id;
  }

private:
  std::unordered_map<uint32_t, NodeType> m_Nodes;
};


struct SpatialDatabaseNode
{
  std::vector<std::pair<std::size_t, Box>> m_Elements;
};

class SpatialDatabase : public SpatialDatabaseGrid<SpatialDatabaseNode>
{
public:

  void SetAllowUnique(bool allow);

  void Insert(const Box & b, uint32_t elem_id);
  void InsertBatch(const Box & b, const std::vector<std::pair<std::size_t, Box>> & new_elems);

  void Remove(const Box & b, uint32_t elem_id);
  void RemoveBatch(const Box & b, const std::vector<std::size_t> & elem_ids);

  void Query(const Box & b, std::vector<std::size_t> & outp_elem_ids) const;
  void QueryBoxes(const Box & b, std::vector<Box> & outp_boxes) const;
  bool QueryAny(const Box & b) const;
  bool QueryAny(const Box & b, std::size_t & outp_elem) const;

private:

  bool m_AllowUnique = false;

};
