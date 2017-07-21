
#include "Foundation/Common.h"
#include "Foundation/SpatialDatabase/SpatialDatabase.h"


void SpatialDatabase::SetAllowUnique(bool allow)
{
  m_AllowUnique = allow;
}

void SpatialDatabase::Insert(const Box & b, uint32_t elem_id)
{
  VisitGrid(b, [&](uint32_t grid_id, SpatialDatabaseNode & node)
  {
    if (m_AllowUnique == false)
    {
      for (auto & elem : node.m_Elements)
      {
        if (elem.first == elem_id)
        {
          return true;
        }
      }
    }

    node.m_Elements.emplace_back(std::make_pair(elem_id, b));
    return true;
  }, true);
}

void SpatialDatabase::InsertBatch(const Box & b, const std::vector<std::pair<std::size_t, Box>> & new_elems)
{
  VisitGrid(b, [&](uint32_t grid_id, SpatialDatabaseNode & node)
  {
    for (auto & elem : new_elems)
    {
      auto grid_box = GetGridBoxForGridId(grid_id);
      if (BoxIntersect(grid_box, elem.second) == false)
      {
        continue;
      }


      bool found = false;

      if (m_AllowUnique == false)
      {
        for (auto & check_elem : node.m_Elements)
        {
          if (check_elem.first == elem.first)
          {
            found = true;
            break;
          }
        }
      }

      if (found == false)
      {
        node.m_Elements.emplace_back(elem);
      }
    }

    return true;
  }, true);
}

void SpatialDatabase::Remove(const Box & b, uint32_t elem_id)
{
  VisitGrid(b, [&](uint32_t grid_id, SpatialDatabaseNode & node)
  {
    for (std::size_t index = 0, end = node.m_Elements.size(); index < end; ++index)
    {
      if (node.m_Elements[index].first == elem_id)
      {
        vremove_index_quick(node.m_Elements, index);
        return true;
      }
    }

    return true;
  }, false);
}

void SpatialDatabase::RemoveBatch(const Box & b, const std::vector<std::size_t> & elem_ids)
{
  VisitGrid(b, [&](uint32_t grid_id, SpatialDatabaseNode & node)
  {
    std::size_t index = 0;
    while (index < node.m_Elements.size())
    {
      bool add = 1;
      for (auto & check_elem : elem_ids)
      {
        if (node.m_Elements[index].first == check_elem)
        {
          vremove_index_quick(node.m_Elements, index);
          add = 0;
          break;
        }
      }

      index += add;
    }

    return true;
  }, false);
}

void SpatialDatabase::Query(const Box & b, std::vector<std::size_t> & outp_elem_ids) const
{
  VisitGrid(b, [&](uint32_t grid_id, const SpatialDatabaseNode & node)
  {
    for (auto & elem : node.m_Elements)
    {
      if (BoxIntersect(b, elem.second))
      {
        if (vfind(outp_elem_ids, elem.first) == false)
        {
          outp_elem_ids.emplace_back(elem.first);
        }
      }
    }

    return true;
  });
}

bool SpatialDatabase::QueryAny(const Box & b) const
{
  bool found = false;
  VisitGrid(b, [&](uint32_t grid_id, const SpatialDatabaseNode & node)
  {
    for (auto & elem : node.m_Elements)
    {
      if (BoxIntersect(b, elem.second))
      {
        found = true;
      }
    }

    return true;
  });

  return found;
}

bool SpatialDatabase::QueryAny(const Box & b, std::size_t & outp_elem) const
{
  bool found = false;
  VisitGrid(b, [&](uint32_t grid_id, const SpatialDatabaseNode & node)
  {
    for (auto & elem : node.m_Elements)
    {
      if (BoxIntersect(b, elem.second))
      {
        outp_elem = elem.first;
        found = true;
      }
    }

    return true;
  });

  return found;
}
